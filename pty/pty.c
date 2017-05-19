#include <pty.h>
#include <stdio.h>
#include <termios.h>

#include <pthread.h>
#include <fcntl.h>
#include <sys/select.h>

void* slave_read(void* args)
{
    char* dev_name = (char*)args;
    int fd = open(dev_name, O_RDWR | O_NOCTTY);

    if (fd <= 0)
    {
        perror("open file failed.");
        exit(0);
    }
    
    struct termios opt ;
    tcgetattr(fd, &opt);
    cfmakeraw(&opt);
    cfsetispeed(&opt, B9600);
    cfsetospeed(&opt, B9600);
    tcsetattr(fd, TCSANOW, &opt);

    while (1)
    {
        char buffer[512];
        int len = read(fd, buffer, 512);

        printf("slave read len = 0x%.2x\n", len);
    }
}


void* master_read(void* args)
{
    int fd = (int)args;

    while (0)
    {
        char buffer[512];
        int len = read(fd, buffer, 512);

        printf("master read len = 0x%.2x\n", len);
    }
}


int main()
{
    int fd_master, fd_slave;
    char dev_name[50];

    openpty(&fd_master, &fd_slave, dev_name, NULL, NULL);

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, slave_read, dev_name);
    pthread_create(&tid2, NULL, master_read, fd_master);


    sleep(5);
    write(fd_master, "hello", 6);

    while (1)
    {
        sleep(1);
    }
}
