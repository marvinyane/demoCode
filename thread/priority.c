#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>


void* test(void* args)
{
    /*pid_t tid = syscall(__NR_gettid);*/
    /*int ret = setpriority(PRIO_PROCESS, tid, -13);*/
    int ret = setpriority(PRIO_PROCESS, 0, -13);

    printf("test....ret = %d.\n", ret);

    while (1)
    {
        sleep(1);
    }
}

int main()
{

    pthread_t pid;
    pthread_create(&pid, NULL, test, NULL);


    pthread_join(pid, NULL);

    return 0;
}
