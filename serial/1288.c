#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include <stdbool.h>
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/


#define FALSE  0
#define TRUE   1

#define SERIAL_PORT "/dev/ttyUSB0"

#define DEBUG(fmt, arg...)    printf(fmt, ##arg)

int instParity = 2;
int instStopBits = 1;
int instDataBits = 8;
int instFlowControl = 1;

/**
*@brief  设置串口通信速率
*@param  fd     类型 int  打开串口的文件句柄
*@param  speed  类型 int  串口速度
*@return  void
*/

static void set_speed(int fd, int speed)
{
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);

    tcflush(fd, TCIOFLUSH);
    switch (speed)
    {
    case 9600:
        cfsetispeed(&Opt, B9600);
        cfsetospeed(&Opt, B9600);
        break;
    case 921600:
        cfsetispeed(&Opt, B921600);
        cfsetospeed(&Opt, B921600);
        break;
    default:
        break;
    }
    status = tcsetattr(fd, TCSANOW, &Opt);
    if (status != 0)
    {
        perror("tcsetattr fd");
        return;
    }
    tcflush(fd, TCIOFLUSH);
}
/**
*@brief   设置串口数据位，停止位和效验位
*@param  fd     类型  int  打开的串口文件句柄
*@param  databits 类型  int 数据位   取值 为 7 或者8
*@param  stopbits 类型  int 停止位   取值为 1 或者2
*@param  parity  类型  int  效验类型 取值为N,E,O,,S
*/
static int set_Parity(int fd, int databits, int stopbits, int parity)
{
    struct termios options;
    if (tcgetattr(fd, &options)  !=  0)
    {
        perror("SetupSerial 1");
        return (FALSE);
    }
    options.c_cflag &= ~CSIZE;
    options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    options.c_oflag  &= ~OPOST;   /*Output*/

    switch (databits) /*设置数据位数*/
    {
    case 7:
        options.c_cflag |= CS7;
        break;
    case 8:
        options.c_cflag |= CS8;
        break;
    default:
        DEBUG("Unsupported data size/n");
        return (FALSE);
    }
    switch (parity)
    {
    case 'n':
    case 'N':
        options.c_cflag &= ~PARENB;   /* Clear parity enable */
        options.c_iflag &= ~INPCK;     /* Enable parity checking */
        break;
    case 'o':
    case 'O':
        options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
        options.c_iflag |= INPCK;             /* Disnable parity checking */
        break;
    case 'e':
    case 'E':
        options.c_cflag |= PARENB;     /* Enable parity */
        options.c_cflag &= ~PARODD;   /* 转换为偶效验*/
        options.c_iflag |= INPCK;       /* Disnable parity checking */
        break;
    case 'S':
    case 's':  /*as no parity*/
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        break;
    default:
        DEBUG("Unsupported parity/n");
        return (FALSE);
    }
    /* 设置停止位*/
    switch (stopbits)
    {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        DEBUG( "Unsupported stop bits/n");
        return (FALSE);
    }
    /* Set input parity option */
    if (parity != 'n')
    {
        options.c_iflag |= INPCK;
    }

    tcflush(fd, TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* define the minimum bytes data to be readed*/
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("SetupSerial 3");
        return (FALSE);
    }
    return (TRUE);
}
static bool uartDeviceConfigure(int fd, speed_t speed)
{
    struct termios options;

    if (tcgetattr(fd, &options) != 0)
    {
        perror("uartDeviceConfigure: tcgetattr failed");
        return FALSE;
    }

    if ((cfsetispeed(&options, speed) != 0) ||
        (cfsetospeed(&options, speed) != 0))
    {
        perror("uartDeviceConfigure: set baud rate failed");
        return FALSE;
    }

    options.c_cflag |= (CLOCAL | CREAD);

    if (instParity == 0)
    {
        options.c_cflag &= ~PARENB;
    }
    else if (instParity == 1)
    {
        options.c_cflag |= PARENB;
        options.c_cflag |= PARODD;
    }
    else if (instParity == 2)
    {
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
    }
    else
    {
        return FALSE;
    }

    if (instStopBits == 2)
    {
        options.c_cflag |= CSTOPB;
    }
    else if (instStopBits == 1)
    {
        options.c_cflag &= ~CSTOPB;
    }
    else
    {
        return FALSE;
    }

    if (instDataBits == 8)
    {
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
    }
    else if (instDataBits == 7)
    {
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS7;
    }
    else
    {
        return FALSE;
    }
#if 0
    if (instFlowControl)
    {
        options.c_cflag |= CRTSCTS;
    }
    else
    {
        options.c_cflag |= CRTSCTS | CLOCAL;
    }
#endif
    options.c_lflag &= ~(ICANON | IEXTEN | ISIG | ECHO);
    options.c_oflag &= ~OPOST;
    options.c_iflag &= ~(ICRNL | INPCK | ISTRIP | IXON | BRKINT);

    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("uartDeviceConfigure: tcsetattr failed");
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************
代码说明：使用串口一测试的，发送的数据是字符，
但是没有发送字符串结束符号，所以接收到后，后面加上了结束符号
**********************************************************************/

/*********************************************************************/
static int OpenDev(char *Dev)
{
    int fd = open(Dev, O_RDWR | O_NOCTTY );
    if (-1 == fd)
    {
        perror("Can't Open Serial Port");
        return -1;
    }
    else
    {
        return fd;
    }
}

void writeInitCmdToDevice(char* info, int size)
{
    int i = 0;
    int fd = 0;
    int nwrite = 0;
    char buf[256];

    fd = OpenDev(SERIAL_PORT);
    if (fd == -1)
    {
        return ;
    }

    uartDeviceConfigure(fd, B921600);

    write(fd, info, size);

    nwrite = read(fd, buf, 256);
    for(; i < nwrite; i++)
    {
        printf("%.X ", buf[i]);
    }

    close(fd);
}

int main(int argc, char** argv)
{
    unsigned int value = 0;

    int count = 0;

    if(argc == 5)
    {
        instParity = atoi(argv[1]);
        instStopBits = atoi(argv[2]);
        instDataBits = atoi(argv[3]);
        instFlowControl = atoi(argv[4]);
    }

    while(1)
    {
        char writeInfo[] = {0x3d, 0x3c, 0x2d, 0x2f, 0x98, 0x87, 0x00};
 //       writeInitCmdToDevice(writeInfo, sizeof(writeInfo));
 //

        printf("%.X \n", writeInfo[0]);
        sleep(5);
    }
}
