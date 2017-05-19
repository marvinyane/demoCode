#include <stdio.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void once_run(void)
{
    printf("once_run in thread %d.\n", (unsigned int )pthread_self());
}

void * child1(void * arg)
{
    pthread_t tid =pthread_self();
    printf("thread %d enter\n", (unsigned int )tid);
    pthread_once(&once,once_run);
    printf("thread %d return\n", (unsigned int )tid);
}


void * child2(void * arg)
{
    pthread_t tid =pthread_self();
    printf("thread %d enter\n", (unsigned int )tid);
    pthread_once(&once,once_run);
    printf("thread %d return\n", (unsigned int )tid);
}

int main(void)
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,child1,NULL);
    pthread_create(&tid2,NULL,child2,NULL);
    sleep(10);

    return 0;
}
