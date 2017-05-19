#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>


int main()
{
    fd_set readfd;
    struct timeval timeout;
    int ret, i;

    struct input_event event;
    int fp = open("/dev/input/event3", O_RDONLY);

    if(fp < 0)
    {
        perror("file open failed");
        return 0;
    }

    while(1)
    {
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        FD_ZERO(&readfd);
        FD_SET(fp, &readfd);
        
        ret = select(fp+1, &readfd, NULL, NULL, &timeout);
        if(FD_ISSET(fp, &readfd))
        {
            int size = read(fp, &event, sizeof(event));

            if(size != sizeof(event))
            {
                printf("%d %d \n", size, sizeof(event));
                break;
            }

            if (event.type == EV_KEY) 
            {
                printf(" type = EV_KEY, code = %s, value = %d \n", 
                        event.code == BTN_LEFT ? "MOUSE_LEFT" : 
                        event.code == BTN_RIGHT ? "MOUSE_RIGHT" : 
                        event.code == BTN_MIDDLE ? "MOUSE_MIDDLE" : 
                        event.code == BTN_SIDE ? "MOUSE_SIDE" : 
                        "Unkonw", event.value); 
            } 
            else if(event.type == EV_REL) 
            {
                printf(" type = EV_ABS, code = %s, value = %d\n", 
                        event.code == REL_X ? "ABS_X" : 
                        event.code == REL_Y ? "ABS_Y" : 
                        event.code == ABS_WHEEL ? "MOUSE_WHEEL" : 
                        event.code == ABS_PRESSURE ? "ABS_PRESSURE" : 
                        "Unkown", event.value); 
            }
        }
        else
        {
            printf("time out \n");
        }
    }

    perror("read failed ");

    return 0;

}
