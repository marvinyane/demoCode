#include <stdio.h>
#include <memory.h>


typedef unsigned char macaddr_t[6];

typedef struct
{
    char mac[6];
}macaddr;

void wifiMacClone(macaddr_t* dest, macaddr_t* src)
{
    memcpy(dest, src, sizeof(macaddr_t));
}

int wifiMacComp(const void* mac1, const void* mac2)
{
    return memcmp(mac1, mac2, sizeof(macaddr_t));
}

void wifiMacDump(macaddr_t* mac)
{
    int i = 0;

    for(; i <  sizeof(macaddr_t); i++)
    {
        printf("%.2X ", mac[i]);
    }

    printf("\n");
}


int main()
{
    macaddr_t mac1 = {0x01, 0x03, 0x54, 0x43, 0xfd, 0x87};
    
    macaddr mac2;

    wifiMacClone((macaddr_t*)mac2.mac, &mac1);

    int ret = wifiMacComp((macaddr_t*)mac2.mac, &mac1);

    printf("%d \n", ret);

    wifiMacDump(&mac1);
    wifiMacDump(mac2.mac);

    return 0;
}
