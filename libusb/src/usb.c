#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

struct libusb_context*              m_context;

int vid = 0x18d1;
int pid = 0x2d05;
/*char* serial = "015d14fec05fea0e";*/
char* serial = "0123456789abcdef";

int m_endPointIn = 0;
int m_endPointOut = 0;

bool getEndpoint(struct libusb_device* device, int inter_num)
{
    struct libusb_config_descriptor *m_config = NULL;
    int j, k;
    bool ret = false;

    if (0 != libusb_get_active_config_descriptor(device, &m_config)) {
        return false;
    }

    if (m_config->bNumInterfaces <= inter_num) {
        goto Ret;
    }

    for (j = 0; j < m_config->interface[inter_num].num_altsetting; j++) {
        if (m_config->interface[inter_num].altsetting[j].bNumEndpoints != 2) {
            continue;
        }

        m_endPointIn = 0;
        m_endPointOut = 0;

        for (k = 0; k < m_config->interface[inter_num].altsetting[j].bNumEndpoints; k++) {
            uint8_t attr = m_config->interface[inter_num].altsetting[j].endpoint[k].bmAttributes;
            uint8_t addr = m_config->interface[inter_num].altsetting[j].endpoint[k].bEndpointAddress;
            if (((attr & LIBUSB_TRANSFER_TYPE_MASK) == LIBUSB_TRANSFER_TYPE_BULK)) {
                if (addr & LIBUSB_ENDPOINT_IN) {
                    m_endPointIn = addr;
                }
                else {
                    m_endPointOut = addr;
                }
            }
            if (m_endPointIn != 0 && m_endPointOut != 0) {
                ret = true;
                break;
            }
        }
    }

Ret:
    libusb_free_config_descriptor(m_config);
    if (!ret) {
        m_endPointIn = 0;
        m_endPointOut = 0;
    }

    return ret;
}

libusb_device_handle* getTargetDevice()
{
    struct libusb_device_handle *handle = NULL;
    struct libusb_device **device_list = NULL;
    ssize_t len = libusb_get_device_list(m_context, &device_list);

    int i = 0;

    printf(" vid = %.2x, pid = %.2x\n", vid, pid);
    for (i = 0; i < len; i++) {
        struct libusb_device* device = device_list[i];
        struct libusb_device_descriptor desc;

        if (0 == libusb_get_device_descriptor(device, &desc)) {
            printf("[%d]vid = %.2x, pid = %.2x\n",i,  desc.idVendor, desc.idProduct);
            if (desc.idVendor != vid || desc.idProduct != pid) {
                continue;
            }
        }

        if (0 != libusb_open(device, &handle)) {
            printf("libusb open failed.\n");
            continue;
        }

        char serialNum[256] = { 0 };
        if (libusb_get_string_descriptor_ascii(handle, \
                    desc.iSerialNumber, \
                    serialNum, \
                    sizeof(serialNum)) < 0) {
            libusb_close(handle);
            continue;
        }

        printf("device serial number is %s \n", serialNum);
            
#if 0
        if (true || (strlen(serial) == 0 && strlen(serialNum) == 0)
                || !strcmp(serial, serialNum)) {
            result = handle;
            break;
        }
        else {
            libusb_close(handle);
            printf("getTargetDevice source[%s], target[%s]\n", serial, serialNum);
            continue;
        }
#endif
    }
    libusb_free_device_list(device_list, 1);

    return handle;

}

int main()
{
    libusb_init(&m_context);

    libusb_device_handle *m_handler = getTargetDevice();

    if (m_handler) {
        getEndpoint(libusb_get_device(m_handler), 0);
        printf("in is %d\n, out is %d\n", m_endPointIn, m_endPointOut);
    }
    else 
    {
        printf("get target device failed.\n");
        return 0;
    }

    // find out if kernel driver is attached
    if (libusb_kernel_driver_active(m_handler, 0) == 1) {
        // ignore return value?
        libusb_detach_kernel_driver(m_handler, 0);
    }

    // interface 0 is for accessory?
    libusb_claim_interface(m_handler, 0);


    /*libusb_transfer* m_transferOut = libusb_alloc_transfer(0);*/
    /*libusb_transfer* m_transferIn = libusb_alloc_transfer(0);*/

    while (1)
    {
        char buffer[512];
        int transferred = 0;
        memset(buffer, 0, sizeof(buffer));
        printf("start read bulk .... \n");
        int ret = libusb_bulk_transfer(m_handler, m_endPointIn, buffer, sizeof(buffer), &transferred, 0);
        printf("ret = %d, transferred is %d\n",ret, transferred);
        if (ret < 0)
        {
            break;
        }
    }

    return 0;
}
