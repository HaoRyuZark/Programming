#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>

#define THREAD_NUM 10

cnd_t condQueue;
mtx_t mutexQueue;

typedef struct Task {
    int(*task_function)(int, int);
    int arg1, arg2;
    struct Task* next;

} Task;

typedef struct Queue {
    Task* first;
    Task* last;
    int length;

} Queue;

Task* task_constructor(int arg1, int arg2, int(*task_function)(int, int)) {
    Task* task = (Task*)malloc(sizeof(Task));
    
    task->arg1 = arg1;
    task->arg2 = arg2;
    task->task_function = task_function;
    task->next = NULL;

    return task;
}

void enqueue(Queue* self, Task* task) {
    mtx_lock(&mutexQueue);
    if(!self->first) {
        self->first = task;
        self->last = task;
    } else {
        self->last->next = task;
        self->last = task;
    }
    self->length += 1;
    mtx_unlock(&mutexQueue);
    cnd_signal(&condQueue);
}

void dequeue(Queue* self, int* result) {
    if(!self->first) {
        return;
    }
    
    Task* current = self->first;
    self->first = self->first->next;
    if(!self->first) {
        self->last = NULL;
    }
    self->length -= 1;
    *result = current->task_function(current->arg1, current->arg2);
    free(current);
}

int sum(int a, int b) {
    return a + b;
}

int product(int a, int b) {
    return a * b;
}

Queue queue = {
    .first = NULL,
    .last = NULL,
    .length = 0
};

int startThread(void* args) {

    int* result = (int*)(args);

    while(1) {
        Task* task;

        mtx_lock(&mutexQueue);
        while(queue.length == 0) {
            cnd_wait(&condQueue, &mutexQueue);

        }

        task = queue.first;
        mtx_unlock(&mutexQueue);
        dequeue(&queue, result);
    }

    return 0;
}


int main(int argc, char* argv[]) {

    thrd_t th[THREAD_NUM];
    mtx_init(&mutexQueue, NULL);
    cnd_init(&condQueue);

    int i;
    int results[THREAD_NUM];
    for(i = 0; i < THREAD_NUM; i++){
        th[i] = thrd_create(&th[i], &startThread, (void*)&results[i]);
    }

    srand(time(NULL));
    for(i = 0; i < THREAD_NUM; i++) {
        int a = rand() % 100;
        int b = rand() % 100;

        Task* t = task_constructor(a, b, sum);

        enqueue(&queue, t);
    }

    for(i = 0; i < THREAD_NUM; i++){
        thrd_join(th[i], NULL);
    }

    mtx_destroy(&mutexQueue);
    cnd_destroy(&condQueue);
    return 0;
}
