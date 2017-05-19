#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
bool signaled = false;

void init()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

void deinit()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void wait()
{
    pthread_mutex_lock(&mutex);
    while(!signaled)
    {
        pthread_cond_wait(&cond, &mutex);
    }
    //signaled = false;
    pthread_mutex_unlock(&mutex);
}

void _signal()
{
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond);
    signaled = true;
    pthread_mutex_unlock(&mutex);
}
void broadcast()
{
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    signaled = true;
    pthread_mutex_unlock(&mutex);
}

void* thread1(void)
{
    printf("thread1 \n");
    wait();
    printf("thread1 wake up \n");
}

void* thread2(void)
{
    printf("thread2 \n");
    wait();
    printf("thread2 wake up \n");
}

int main()
{
    int ret = 0;
    pthread_t p1, p2;
    
    init();

    ret = pthread_create(&p1, NULL, (void*)thread1, NULL);

    if(ret)
    {
        perror("create failed: ");
        return 1;
    }

    ret = pthread_create(&p2, NULL, (void*)thread2, NULL);

    if(ret)
    {
        perror("create failed:");
        return 1;
    }

    sleep(1);
    broadcast();
    _signal();

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    deinit();
    return 0;
}



