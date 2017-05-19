#include <stdio.h>
#include <pthread.h>

#include "ringbuffer.h"


void* readThread(void* args)
{
    tsRingbuffer* ts = (tsRingbuffer*)args;

    int i = 1;
    for (; i < 1000; i++) 
    {
        char buffer[1024];
        int len = insertIntoRingbuffer(ts, buffer, i);
        if (len != i)
        {
            printf("insert into ring buffer failed. %d %d\n", len, i);
            usleep(100);
        }

        usleep(95);
    }

    return NULL;
}

int main()
{
    tsRingbuffer *ts = NULL;
    int ret = createRingbuffer(&ts, 1023);
    if (ret != iRINGBUFFER_OK) 
    {
        printf("create ring buffer failed.\n");
        return 0;
    }

    pthread_t pid;
    pthread_create(&pid, NULL, readThread, ts);
    
    int i = 1;
    for(; i < 1000; i++)
    {
        char buffer[1024];
        int len = extractFromRingbuffer(ts, buffer, i);
        if (len != i) 
        {
            printf("extrat from ringbuffer not enough ... %d %d.\n", len , i);
            usleep(100);
        }

        usleep(100);
    }

    pthread_join(pid, NULL);

    return 0;
}
