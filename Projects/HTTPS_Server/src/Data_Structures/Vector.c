#include "Vector.h"
#include"../Common/Error_Handling.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 50

Vec* create_vec() {

    Vec* vec = (Vec*)malloc(sizeof(Vec));
    
    handle_error_with_return(vec, NULL, "Could not initialize vec")

    vec->arr = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    
    handle_error_with_return(vec->arr, NULL,"Could not allocate memory for the internal array in vec")
    
    vec->len = 0;
    vec->capacity = INITIAL_CAPACITY;

    return vec;
}

Vec* create_vec_with(int capacity) {

    Vec* vec = (Vec*)malloc(sizeof(Vec));
    
    handle_error_with_return(vec, NULL, "Could not initialize vec"); 

    vec->arr = (int*)malloc(capacity * sizeof(int));
    
    handle_error_with_return(vec->arr, NULL,"Could not allocate memory for the internal array in vec");
   
    vec->len = 0;
    vec->capacity = capacity;

    return vec;
}

Vec* create_vec_from(int* arr, int size) {

    Vec* vec = (Vec*)malloc(sizeof(Vec));

    handle_error_with_return(vec, NULL, "Could not initialize vec"); 
   
    int padded_size = size + 10;

    vec->arr = (int*)malloc(padded_size * sizeof(int));
    
    handle_error_with_return(vec->arr, NULL,"Could not allocate memory for the internal array in vec");
    
    for (int i = 0; i < size; i++) {
        vec->arr[i] = arr[i];
    }
    
    vec->len = size;
    vec->capacity = padded_size;

    return vec;
}

void adjust_size(Vec* self) {

    if (self->len >= self->capacity) {

        self->arr = (int*)realloc(self->arr, (self->capacity * 2)*sizeof(int));
        
        handle_error(self, "Could not resize array");

        self->capacity = self->capacity * 2;
    }
}

void push_back(Vec* self, int data) {

    handle_error(self, "Vec is NULL");
    
    adjust_size(self);

    self->arr[self->len] = data;
    self->len++;
}

int pop_back(Vec* self) {

    handle_error_with_return(self, 0, "Vec is NULL");
    
    if (self->len == 0) {
        return self->arr[self->len];
    }

    int data = self->arr[self->len--];
    
    return data;
}

void shift_right(Vec* self, int data) {
    
    adjust_size(self);
    
    int l = self->len + 1;

    for (int i = self->len; i > 1; i--) {

        self->arr[l] = self->arr[i];
        l--;
    }

    self->arr[0] = data;
}


void push_front(Vec* self, int data) {
    
    handle_error(self, "Vec is NULL");
    
    if (self->len == 0) {
        self->arr[self->len] = data;
    } 

    else {
        shift_right(self, data);
    }

    self->len++;
}

void shift_left(Vec* self) {
    
     int l = 1;

    for (int i = 0; i < self->len - 1; i++) {

        self->arr[i] = self->arr[l];
        l++;
    }
}

int pop_front(Vec* self) {

    handle_error_with_return(self, 0, "Vec is NULL");
        
    int data = self->arr[0];

    if (self->len > 0) { 
        shift_left(self);
    } 

    self->len--;
    return data;
}

void free_vec(Vec* self) {
    
    handle_error(self, "Vec is already NULL");
    
    free(self->arr);
    free(self);

    self = NULL;
}

void set_at_index(Vec* self, int data, int index) {

    handle_error(self, "Vec is NULL");

    if (index < 0 || index >= self->capacity) {
        return;
    }

    adjust_size(self);
    
    int l = self->len + 1;

    for (int i = self->len; i >= index; i--) {

        self->arr[l] = self->arr[i];
        l--;
    }
    
    self->arr[index] = data;
}

int get(Vec* self, int index) {

    handle_error_with_return(self, 0, "Vec is NULL");

    if (index < 0 || index >= self->capacity) {
        return 0;
    }
    
    return self->arr[index];
}

int binary_search(Vec *self, int data, int s, int e) {
    
    int start = s;
    int end = e;

    while (start <= end) {
        int m = start + (end - start) / 2;

        if (self->arr[m] == data) {
            return m;
        } else if (self->arr[m] > data) {
            end = m - 1;
        } else {
            start = m + 1;
        }
    }
    return -1;
}

int get_index_of(Vec* self, int data) {

    handle_error_with_return(self, -1, "Vec is NULL");
    
    return binary_search(self, data, 0, self->len);
}

