#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIFO "/home/marvin/study/temCode/pipe/named/myfifo"

int main()
{
    char buf[100];
    int fd;
    int nread;

    fd_set readfd;
    struct timeval timeout;
    int ret;

    pid_t pid;

    if((mkfifo(FIFO, O_CREAT|O_EXCL) < 0 ) && (errno != EEXIST))
    {
        printf("cannot create fifo server! \n");
        return 0;
    }

    printf("preparing for reading bytes...\n");
    memset(buf, 0, sizeof(buf));

    fd = open(FIFO, O_RDONLY|O_NONBLOCK, 0);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    while(1)
    {
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        FD_ZERO(&readfd);
        FD_SET(fd, &readfd);

        ret = select(fd+1, &readfd, NULL, NULL, &timeout);

        if(FD_ISSET(fd, &readfd))
        {
            nread = read(fd, buf, 100);
            printf(" read %s from FIFO \n", buf);
            break;
        }
        else
        {
            printf("time out \n");
        }
    }
    close(readfd);
    unlink(FIFO);

    return 0;
}
