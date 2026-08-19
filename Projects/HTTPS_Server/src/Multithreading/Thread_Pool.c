#include "Thread_Pool.h"

/*
 * A thread pool is way of handling multiple request or tasks in 
 * a system by initilizing a certain number of threads "worker" which 
 * continously check if there are task in a queue and if there are jobs to 
 * do they execute it and then repeat the process.
 * */
Task_Queue* queue_construtor() {

    Task_Queue* queue = (Task_Queue*)malloc(sizeof(Task_Queue));
    
    queue->first = NULL;
    queue->last = NULL;
    queue->length = 0;

    return queue;
}

void queue_destructor(Task_Queue* self) {
    
    handle_error_and_exit(self, "Task-queue is NULL!")
    
    Task* current = self->first;
    Task* temp;

    while (current) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

// Create a new task
Task* task_constructor(void* args, void*(*job)(void* args)) {

    Task* task = (Task*)malloc(sizeof(Task));  
    task->job = job;
    task->args = args;
    task->next = NULL;

    return task;
}

Task* task_from(Task* other) {

    Task* task = (Task*)malloc(sizeof(Task));  
    task->job  = other->job;
    task->args = other->args;
    task->next = other->next;

    return task;
}

void* dequeue(Task_Queue* self) {
    
    handle_error_and_exit(self, "Task-queue is NULL!")

    Task* current = self->first;
    self->first = self->first->next;
   
    if (!self->first) {
        self->last = NULL;
    }
   
    self->length--;
    
    Task* res = task_from(current);
    
    free(current);

    return res;
}

/* Execute thread function 
 *
 * It runs an infinite loop and if thre are tasks availiable it executes it. 
 * For synchornization the mutex is aquired and the condition variable signals 
 * if there are even any tasks*/
void* thread_job(void* args) {
    
    Thread_Pool* thread_pool = (Thread_Pool*)args;
    
    while (thread_pool->active == 1) {

        pthread_mutex_lock(&thread_pool->mutex);
        pthread_cond_wait(&thread_pool->condvar, &thread_pool->mutex);

        struct Task task = *(Task*)dequeue(thread_pool->tasks);
        
        pthread_mutex_unlock(&thread_pool->mutex);

        if (task.job) {
            task.job(task.args);
        }

    }

    return NULL;
}


/* 
 * Enqueue a task into the queue (thread-safe). 
 *
 * When adding a task we make sure that only the current thread can 
 * modify its contents. Then after adding a task to the queue we release the 
 * mutex and also notify all the thread waiting for a task to execute it*/
void enqueue(Thread_Pool* thread_pool, Task* task) {
    

    pthread_mutex_lock(&thread_pool->mutex);
    
    handle_error_and_exit(thread_pool->workers, "Task-queue is NULL!")
    
    if (!thread_pool->tasks->first) {
        thread_pool->tasks->first = task;
        thread_pool->tasks->last = task;
    } else {
        thread_pool->tasks->last->next = task;
        thread_pool->tasks->last = task;
    }
    
    thread_pool->tasks->length++;
    
    pthread_mutex_unlock(&thread_pool->mutex);
    pthread_cond_signal(&thread_pool->condvar);
}

// Initialization of the thread pool and threads
Thread_Pool thread_pool_constructor(int thread_num) {
    
    Thread_Pool thread_pool;
    
    thread_pool.thread_num = thread_num; 
    thread_pool.active = 1;
    thread_pool.workers = (pthread_t*)malloc(thread_num * sizeof(pthread_t));
    
    for (int i = 0; i < thread_num; i++) {
        pthread_create(&thread_pool.workers[i], NULL,thread_job, NULL);
    }

    thread_pool.tasks = queue_construtor(); 
    thread_pool.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    thread_pool.condvar = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    return thread_pool;
}

void thread_pool_destructor(Thread_Pool* thread_pool) {
    
    thread_pool->active = 0; 
    
    // Signal each thread to finish their job
    for (int i = 0; i < thread_pool->thread_num; i++) {
        pthread_cond_signal(&thread_pool->condvar);
    }
    
    // Wait join all threads
    for (int i = 0; i < thread_pool->thread_num; i++) {
        pthread_join(thread_pool->workers[i], NULL);        
    }

    free(thread_pool->workers);
    queue_destructor(thread_pool->tasks);
}


