#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


typedef struct H2O {
    pthread_mutex_t mutex; 
    pthread_cond_t cond; 
    int h_count;
    int iter;
    size_t n;
} H2O;

void releaseHydrogen() {
    printf("H");
}

void releaseOxygen() {
    printf("O");
}

H2O* h2oCreate(int n) {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);

    obj->n = n;
    obj->h_count = 0;
    obj->iter = 1;
    
    return obj;
}

void* hydrogen(void* arg) {
    
    H2O* obj = (H2O*)arg;
     
    pthread_mutex_lock(&obj->mutex);
    while (obj->iter <= obj->n) {
        
       // While there is hydrogen 
        while (obj->h_count == 2) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        
        if (obj->iter > obj->n) break;

        releaseHydrogen();

        obj->h_count++;

        pthread_cond_signal(&obj->cond);
    }

    pthread_mutex_unlock(&obj->mutex);
    return NULL;

}

void* oxygen(void* arg) {

    H2O* obj = (H2O*)arg;
    
    pthread_mutex_lock(&obj->mutex);
    while (obj->iter <= obj->n) {

        
       // While there is not enough hydrogen 
        while (obj->h_count < 2) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }

   
        if (obj->iter > obj->n) break;

        releaseOxygen();
        obj->h_count = 0;
        obj->iter++; // only increment iter (number of water molecules after a complete cycle)

        pthread_cond_signal(&obj->cond);
    }
    
    pthread_mutex_unlock(&obj->mutex);

    return NULL;
}

void h2oFree(H2O* obj) {
    pthread_mutex_destroy(&obj->mutex); 
    pthread_cond_destroy(&obj->cond); 
    free(obj);
}

int main() {
  
    H2O* obj = h2oCreate(4); 

    pthread_t threads[2];
    
    pthread_create(&threads[0], NULL, &hydrogen, (void*)obj);
    pthread_create(&threads[1], NULL, &oxygen, (void*)obj);


    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    h2oFree(obj);
    return 0;
}
