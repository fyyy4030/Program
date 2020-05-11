#include <stdio.h>
#include"threadpool.h"

void *process(void *arg)
{
    printf("thread 0x%x working on task %d\n", (unsigned int)pthread_self(), *(int*)arg);
    sleep(1);
    printf("task %d is end\n", *(int*)arg);

    return NULL;
}

int main(void)
{
    printf("Hello World!\n");

    //threadpool_t *thp = threadpool_create(3, 100, 100);
    threadpool_t *thp = threadpool_create(3,100,100);
    printf("pool inited");

    int num[20] = {0};
    int i;

    for (i = 0; i < 20; ++i)
    {
        num[i] = i;
        printf("add task %d\n", i);
        threadpool_add(thp, process, (void*)&num[i]);
    }

    sleep(10);
    threadpool_destory(thp);
    return 0;
}

