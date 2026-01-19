#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 10

// Global mutex and condition variable for synchronizing access to the queue
cnd_t condQueue;
mtx_t mutexQueue;
int done = 0; // Flag to indicate when no more tasks will be enqueued

// Task representation
typedef struct Task {

    int (*task_function)(int, int);
    int arg1, arg2;
    struct Task* next;

} Task;

// Queue structure for storing tasks
typedef struct Queue {

    Task* first;
    Task* last;
    int length;

} Queue;

// Create a new task
Task* task_constructor(int arg1, int arg2, int(*task_function)(int, int)) {

    Task* task = (Task*)malloc(sizeof(Task));
    task->arg1 = arg1;
    task->arg2 = arg2;
    task->task_function = task_function;
    task->next = NULL;
   
    return task;
}

// Enqueue a task into the queue (thread-safe)
void enqueue(Queue* self, Task* task) {

    mtx_lock(&mutexQueue);
   
    if (!self->first) {
        self->first = task;
        self->last = task;
    } else {
        self->last->next = task;
        self->last = task;
    }
   
    self->length++;
   
    mtx_unlock(&mutexQueue);
    cnd_signal(&condQueue); // Wake up one waiting thread
}

// Dequeue and execute a task (thread-safe)
int dequeue(Queue* self) {

    mtx_lock(&mutexQueue);
   
    while (self->length == 0 && !done) {
        cnd_wait(&condQueue, &mutexQueue); // Wait until new task arrives
    }

    if (done && self->length == 0) {
        mtx_unlock(&mutexQueue);
        return -1; // Signal termination
    }

    Task* current = self->first;
    self->first = self->first->next;
   
    if (!self->first) {
        self->last = NULL;
    }
   
    self->length--;

    mtx_unlock(&mutexQueue);

    // Execute task
    int result = current->task_function(current->arg1, current->arg2);
   
    printf("The sum of %d and %d is %d\n", current->arg1, current->arg2, result);
    free(current);

    return result;
}

// Example task functions
int sum(int a, int b) {
    return a + b;
}
int product(int a, int b) {
    return a * b;
}

// Global queue
Queue queue = { .first = NULL, .last = NULL, .length = 0 };

// Thread function
int startThread(void* args) {
   
    (void)args; // Unused
   
    while (1) {
        int result = dequeue(&queue);
        if (result == -1) break; // Stop thread
    }
    return 0;
}

int main() {
   
    thrd_t th[THREAD_NUM];
   
    mtx_init(&mutexQueue, mtx_plain);
    cnd_init(&condQueue);

    srand(time(NULL));

    // Create threads
   
    for (int i = 0; i < THREAD_NUM; i++) {
        thrd_create(&th[i], startThread, NULL);
    }

    // Enqueue random tasks
    for (int i = 0; i < THREAD_NUM; i++) {
        
        int a = rand() % 100;
        int b = rand() % 100;
        Task* t = task_constructor(a, b, sum);
        enqueue(&queue, t);
    }

    // Signal threads to finish
    mtx_lock(&mutexQueue);
   
    done = 1;
    
    mtx_unlock(&mutexQueue);
    cnd_broadcast(&condQueue); // Wake up all threads

    // Join threads
    for (int i = 0; i < THREAD_NUM; i++) {
        thrd_join(th[i], NULL);
    }

    mtx_destroy(&mutexQueue);
    cnd_destroy(&condQueue);

    return 0;
}
