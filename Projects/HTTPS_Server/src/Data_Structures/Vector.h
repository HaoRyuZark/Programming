#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vec {
    
    int* arr;
    int  len;
    int capacity;

} Vec;

Vec* create_vec();

Vec* create_vec_with(int capacity);

Vec* create_vec_from(int* arr, int size);

void push_back(Vec* self, int data);

int pop_back(Vec* self);

void push_front(Vec* self, int data);

int pop_front(Vec* self);

void free_vec(Vec* self);

void set_at_index(Vec* self, int data, int index);

void resize(int* arr);

#endif // !VECTOR_H
