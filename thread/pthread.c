#include <pthread.h>

void test(void* )
{
    while (1)
    {
        sleep(10);
    }
}

int main()
{
    pid_t at;
    pthread_create(&at, NULL, test, NULL);

    sleep(100);
    return 0;
}
