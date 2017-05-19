#include <stdio.h>
#include <pthread.h>

void* test(void* args)
{
    while (1)
    {
        sleep(10);
    }
}

int main()
{
    pthread_t pid;
    pthread_create(&pid, NULL, test, NULL);

    pthread_setname_np(pid, "marvin");

    char buf[100];
    pthread_getname_np(pid, buf, sizeof(buf));
    printf("get thread name is %s.\n", buf);

    pthread_join(pid, NULL);

    return 0;
}
