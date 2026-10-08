#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define FIZZ_COND      (obj->count % 3 == 0 && obj->count % 5 != 0)
#define BUZZ_COND      (obj->count % 3 != 0 && obj->count % 5 == 0)
#define FIZZ_BUZZ_COND (obj->count % 5 == 0 && obj->count % 3 == 0)
#define NUM_COND       (obj->count % 5 > 0 && obj->count % 3 > 0)

typedef struct FB {
    pthread_mutex_t mutex; 
    pthread_cond_t cond; 
    int n;
    int count;
} FB;

FB* fbCreate(int n) {
    FB* obj = (FB*) malloc(sizeof(FB));
    
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);

    obj->n = n;
    obj->count = 1;
    
    return obj;
}

void printNumber(int n) {
    printf("%d\n", n);
}

void printFizz() {
    printf("fizz\n");
} 

void printBuzz() {
    printf("buzz\n");
}

void printFizzBuzz() {
    printf("fizzbuzz\n");
}


void* fizz(void* args) {
    
    FB* obj = (FB*)args; 

    pthread_mutex_lock(&obj->mutex);

    while (obj->count <= obj->n) {
        
        while (!FIZZ_COND) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
            if (obj->count > obj->n) break;
        }

        if (obj->count > obj->n) break;

        printFizz();
        
        obj->count++;  

        pthread_cond_broadcast(&obj->cond);
   } 

   pthread_mutex_unlock(&obj->mutex);
   return NULL;
}

// printBuzz() outputs "buzz".
void* buzz(void* args) {

    FB* obj = (FB*)args; 
    pthread_mutex_lock(&obj->mutex);

    while (obj->count <= obj->n) { 
        
        while (!BUZZ_COND) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
            if (obj->count > obj->n) break;
        }

        if (obj->count > obj->n) break;
        
        printBuzz();
        obj->count++;  
        
        pthread_cond_broadcast(&obj->cond);
   } 

   pthread_mutex_unlock(&obj->mutex);
   return NULL;
}

// printFizzBuzz() outputs "fizzbuzz".
void* fizzbuzz(void* args) {

    FB* obj = (FB*)args; 
    
    pthread_mutex_lock(&obj->mutex);
 
    while (obj->count <= obj->n) {
             
        while (!FIZZ_BUZZ_COND) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
            if (obj->count > obj->n) break;
        }
    
        if (obj->count > obj->n) break;
        
        printFizzBuzz();
        obj->count++;   
        
        pthread_cond_broadcast(&obj->cond);
   } 

   pthread_mutex_unlock(&obj->mutex);
   return NULL;
}

void* number(void* args) {

    FB* obj = (FB*)args; 
    
    pthread_mutex_lock(&obj->mutex);

    while (obj->count <= obj->n) {
 
        while (!NUM_COND) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
            if (obj->count > obj->n) break;
        }
    
        if (obj->count > obj->n) break;

        printNumber(obj->count);
        obj->count++;  
        
        pthread_cond_broadcast(&obj->cond);
   } 

   pthread_mutex_unlock(&obj->mutex);   
   return NULL;
}

void fbFree(FB* obj) {
    pthread_mutex_destroy(&obj->mutex); 
    pthread_cond_destroy(&obj->cond); 
    free(obj);
}

int main() {
  
    FB* obj = fbCreate(100); 

    pthread_t threads[4];
    

    pthread_create(&threads[0], NULL, &fizz, (void*)obj);
    pthread_create(&threads[1], NULL, &buzz, (void*)obj);
    pthread_create(&threads[2], NULL, &number, (void*)obj);
    pthread_create(&threads[3], NULL, &fizzbuzz, (void*)obj);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

    fbFree(obj);
    return 0;
}
