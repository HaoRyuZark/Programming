#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct ZeroEvenOdd {
    int n;
    int count;
    bool zero_turn;

    pthread_mutex_t mutex;
    pthread_cond_t cond;

} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));

    obj->n = n;
    obj->count = 1;
    obj->zero_turn = true;

    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);

    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void printNumber(int x) {
    printf("%d", x);
}

void* zero(void* args) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)args;

    pthread_mutex_lock(&obj->mutex);
    while (obj->count <= obj->n) {
        while (obj->count <= obj->n && !obj->zero_turn) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        if (obj->count > obj->n) break;

        printNumber(0);
        obj->zero_turn = false;

        pthread_cond_broadcast(&obj->cond);
    }
    pthread_mutex_unlock(&obj->mutex);
    return NULL;
}

void* even(void* args) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)args;

    pthread_mutex_lock(&obj->mutex);
    while (obj->count <= obj->n) {
        while (obj->count <= obj->n &&
               (obj->zero_turn || obj->count % 2 != 0)) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        if (obj->count > obj->n) break;

        printNumber(obj->count);
        obj->count++;
        obj->zero_turn = true;

        pthread_cond_broadcast(&obj->cond);
    }
    pthread_mutex_unlock(&obj->mutex);
    return NULL;
}

void* odd(void* args) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)args;

    pthread_mutex_lock(&obj->mutex);
    while (obj->count <= obj->n) {
        while (obj->count <= obj->n &&
               (obj->zero_turn || obj->count % 2 == 0)) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        if (obj->count > obj->n) break;

        printNumber(obj->count);
        obj->count++;
        obj->zero_turn = true;

        pthread_cond_broadcast(&obj->cond);
    }
    pthread_mutex_unlock(&obj->mutex);
    return NULL;
}


void zeroEvenOddFree(ZeroEvenOdd* obj) {
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->cond);
    free(obj);
}

int main () {

    pthread_t threads[3];
    ZeroEvenOdd* self = zeroEvenOddCreate(6);

    for (int i = 0; i < 3; i ++) {

        switch (i) {
            case 0: { pthread_create(&threads[i], NULL, &zero, (void*)self); break; }
            case 1: { pthread_create(&threads[i], NULL, &even, (void*)self); break; }
            case 2: { pthread_create(&threads[i], NULL, odd, (void*)self); break; }
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    zeroEvenOddFree(self);
}
