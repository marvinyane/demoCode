#include <stdio.h>
#include <sys/prctl.h>
#include <pthread.h>


//  ps H -C a.out -o 'pid tid cmd comm'

void* test(void* args)
{
    prctl(PR_SET_NAME, (unsigned long)"marvin", 0, 0, 0);

    while (1)
    {
        sleep(10);
    }
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, test, NULL);

    pthread_join(tid, NULL);

    return 0;
}
