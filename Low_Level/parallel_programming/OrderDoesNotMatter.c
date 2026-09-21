#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>

void printFirst();
void printSecond();
void printThird();


typedef struct Foo {    
    void(*p1)(void);
    void(*p2)(void);
    void(*p3)(void);

} Foo;


void* start_thread(void* args);

// Globals
int count = 1;
pthread_mutex_t count_mutex;
pthread_cond_t count_cond;

Foo obj = {
    .p1 = &printFirst, 
    .p2 = &printSecond, 
    .p3 = &printThird, 
};


int main() {
    
    int num_threads = 3;
    pthread_t threads[num_threads];
    
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_cond, NULL);

    int args[3] = {2, 3, 1};

    
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, &start_thread, (void*)&args[i]);
    }

    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_cond);

    return 0;
}

void* start_thread(void* args) {
    
    int num = *(int*)args;

    pthread_mutex_lock(&count_mutex);

    while (count != num) {
      pthread_cond_wait(&count_cond, &count_mutex); 
    }
    
    switch (num) {
        case 1: obj.p1(); break;
        case 2: obj.p2(); break;
        case 3: obj.p3(); break;
        default: exit(1);
    }

    count++;
    
    pthread_mutex_unlock(&count_mutex);
    pthread_cond_broadcast(&count_cond);
    return NULL;
}

void printFirst() {
    printf("first");
}
void printSecond() { 
    printf("second");
}

void printThird() {
    printf("third");
}


