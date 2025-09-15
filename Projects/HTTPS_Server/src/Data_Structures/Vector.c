#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 50

Vec* create_vec() {

    Vec* vec = (Vec*)malloc(sizeof(Vec));

    if (vec == NULL) {
        perror("Could not initialize vec");
        return NULL;
    }

    vec->arr = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    
    if (vec->arr == NULL) {
        perror("Could not allocate memory for the internal array in vec");
        return NULL;
    }

    vec->len = 0;
    vec->capacity = INITIAL_CAPACITY;

    return vec;
}

Vec* create_vec_with(int capacity) {

    Vec* vec = (Vec*)malloc(sizeof(Vec));

    if (vec == NULL) {
        perror("Could not initialize vec");
        return NULL;
    }

    vec->arr = (int*)malloc(capacity * sizeof(int));
    
    if (vec->arr == NULL) {
        perror("Could not allocate memory for the internal array in vec");
        return NULL;
    }

    vec->len = 0;
    vec->capacity = capacity;

    return vec;
}

Vec* create_vec_from(int* arr, int size) {

    Vec* vec = (Vec*)malloc(sizeof(Vec));

    if (vec == NULL) {
        perror("Could not initialize vec");
        return NULL;
    }
    
    int padded_size = size + 10;

    vec->arr = (int*)malloc(padded_size * sizeof(int));
    
    if (vec->arr == NULL) {
        perror("Could not allocate memory for the internal array in vec");
        return NULL;
    }


    for (int i = 0; i < size; i++) {
        vec->arr[i] = arr[i];
    }
    
    vec->len = size;
    vec->capacity = padded_size;

    return vec;
}

void push_back(Vec* self, int data) {

    if (self == NULL) {
        perror("The vector is NULL");
    }
    
    if (self->len >= self->capacity) {

        self->arr = (int*)realloc(self->arr, (self->capacity * 2)*sizeof(int));

        if (self == NULL) {
            perror("Could not resize array");
            return;
        }

        self->capacity = self->capacity * 2;
    }

    self->arr[self->len] = data;
    self->len++;
}

int pop_back(Vec* self) {
    
    if (self == NULL) {
        perror("The vector is NULL");
        return 0;
    }
    
    if (self->len == 0) {
        return self->arr[self->len];
    }

    int data = self->arr[self->len--];
    
    return data;
}

void push_front(Vec* self, int data);

int pop_front(Vec* self);

void free_vec(Vec* self);

void set_at_index(Vec* self, int data, int index);

void resize(int* arr);


