#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO "/home/marvin/study/temCode/pipe/named/myfifo"

int main()
{
    int fd;
    int nwrite;

    fd = open(FIFO, O_WRONLY|O_NONBLOCK, 0);

    if(fd == -1)
    {
        perror("open failed: ");
        return 0;
    }

    printf("client open success!! \n");

    int ret = fcntl(fd, F_GETPIPE_SZ);
    if (ret < 0)
    {
        perror("get pipe size failed:");
    }

    ret = fcntl(fd, F_SETPIPE_SZ, 4096);
    if (ret < 0)
    {
        perror("set pipe size to 4096 failed.");
    }

    if((nwrite = write(fd, "hello", 6)) == -1)
    {
        if(errno == EAGAIN)
        {
            printf("the fifo has not bean read yet, please try later \n");
        }
        else
        {
            perror("write failed \n");
        }
    }
    else
    {
        printf("write to FIFO \n");
    }

    close(fd);

    return 0;
}
