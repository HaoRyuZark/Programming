#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <threads.h>

// Task representation
typedef struct Task {

    void* (*job)(void* arg);
    void* args;
    struct Task* next;

} Task;

// Queue structure for storing tasks
typedef struct Queue {

    Task* first;
    Task* last;
    int length;

} Queue;

Queue* queue_construtor() {

    Queue* queue = (Queue*)malloc(sizeof(Queue));
    
    queue->first = NULL;
    queue->last = NULL;
    queue->length = 0;

    return queue;
}

void queue_destructor(Queue* self) {
   
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

// Dequeue and execute a task (thread-safe)
void* dequeue(Queue* self) {

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


typedef struct Thread_Pool {

    int thread_num;
    int active;
    struct Queue* tasks;
    pthread_t* workers;
    pthread_mutex_t mutex;
    pthread_cond_t condvar;

} Thread_Pool;

// Execute thread function
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


// Enqueue a task into the queue (thread-safe)
void enqueue(Thread_Pool* thread_pool, Task* task) {
    
    pthread_mutex_lock(&thread_pool->mutex);

    if (!thread_pool->tasks->first) {
        thread_pool->tasks->first = task;
        thread_pool->tasks->last = task;
    } else {
        thread_pool->tasks->last->next = task;
        thread_pool->tasks->last = task;
    }
    
    thread_pool->tasks->length++;
    
    pthread_mutex_lock(&thread_pool->mutex);
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

    for (int i = 0; i < thread_pool->thread_num; i++) {
        pthread_cond_signal(&thread_pool->condvar);
    }

    for (int i = 0; i < thread_pool->thread_num; i++) {
        pthread_join(thread_pool->workers[i], NULL);        
    }

    free(thread_pool->workers);
    queue_destructor(thread_pool->tasks);
}

int main() {
    
    printf("Hello Mom!");
    return 0;
}
