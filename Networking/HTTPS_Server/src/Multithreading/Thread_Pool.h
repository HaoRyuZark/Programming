#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../Common/Error_Handling.h"

// Task representation
typedef struct Task {

    void* (*job)(void* arg);
    void* args;
    struct Task* next;

} Task;

// Task_Queue structure for storing tasks
typedef struct Task_Queue {

    Task* first;
    Task* last;
    int length;

} Task_Queue;

// Thread_Pool
typedef struct Thread_Pool {

    int thread_num;
    int active;
    struct Task_Queue* tasks;
    pthread_t* workers;
    pthread_mutex_t mutex;
    pthread_cond_t condvar;

} Thread_Pool;

Task_Queue* queue_construtor(); 

void queue_destructor(Task_Queue* self);

Task* task_constructor(void* args, void*(*job)(void* args));

Task* task_from(Task* other);

void* dequeue(Task_Queue* self); 

// Execute thread function
void* thread_job(void* args);

// Enqueue a task into the queue (thread-safe)
void enqueue(Thread_Pool* thread_pool, Task* task);

// Initialization of the thread pool and threads
Thread_Pool thread_pool_constructor(int thread_num); 

void thread_pool_destructor(Thread_Pool* thread_pool); 


#endif
