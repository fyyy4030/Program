#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<errno.h>

#define DEFAULT_TIME 10
#define MIN_WAIT_TASK_NUM 10
#define DEFAULT_THREAD_VARY 10
#define true 1
#define false 0


typedef struct
{
    void *(*function)(void *);
    void *arg;
}threadpool_task_t;

typedef struct
{
    pthread_mutex_t lock;   //
    pthread_mutex_t thread_counter;
    pthread_cond_t queue_not_full;
    pthread_cond_t queue_not_empty;

    pthread_t *threads;
    pthread_t adjust_tid;
    threadpool_task_t *task_queue;

    int min_thr_num;
    int max_thr_num;
    int live_thr_num;
    int busy_thr_num;
    int wait_exit_thr_num;

    int queue_front;
    int queue_rear;
    int queue_size; //the actual task number of queue
    int queue_max_size;

    int shutdown;
}threadpool_t;





threadpool_t *threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size);

//add a new task in the queue of a thread pool
int threadpool_add(threadpool_t *pool, void*(*function)(void *arg), void *arg);

//stop and destory a threadpool
int threadpool_destory(threadpool_t *pool);

//get the thread num
int threadpool_all_threadnum(threadpool_t *pool);

//get the busy thread num
int threadpool_busy_threadnum(threadpool_t* pool);

#endif // THREADPOOL_H
