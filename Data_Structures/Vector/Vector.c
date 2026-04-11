#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Not really usable due to not having error handling just a reference
#define INITIAL_CAPACITY 50

typedef struct Vector {
  size_t capacity;
  int* arr;
  size_t size;
} Vector;

void create(Vector* self) {

  self->arr = (int*)malloc(sizeof(int) * INITIAL_CAPACITY); 
  self->size = 0;
  self->capacity = 10;
}

void create_from(Vector* self, Vector* other) {

  self->arr = (int*)malloc(sizeof(int) * other->size); 
  
  memccpy(self->arr, other->arr, 1, other->size);

  self->size = other->size;
  self->capacity = other->capacity;
}

void create_from_arr(Vector* self, int* arr, size_t len) {

  self->arr = (int*)malloc(sizeof(int) * len); 
  
  memccpy(self->arr, arr, 1, len);

  self->size = len;
  self->capacity = len;
}

void push(Vector* vec, int v) {

  if (vec->size >= vec->capacity) { // if the index is greater or equal to the
                                    // capacity (last index) then ->
    vec->capacity *= 2;             // double the capacity
    vec->arr = (int *)realloc(vec->arr, sizeof(int) * vec->capacity); // realloc the capacity
  }

  vec->arr[vec->size++] = v; // otherwise just store the value at the index of
                             // size and then increments its by one
}

int pop(Vector* vec) { // deleting last element

  int temp = vec->arr[vec->size - 1];
  
  vec->arr[vec->size - 1] = 0;

  vec->size = vec->size - 1;
  
  return temp;
}

int get(Vector* vec, int index) {

    if (index >= vec->size) {
      return -1;
    }

    return vec->arr[index];
}

void print_v(Vector *vec) { // printing

  for (int i = 0; i < vec->size; i++) {
    printf("%d ", vec->arr[i]);
  }
  printf("\n");
}

void free_v(Vector *vec) { // deleting vector

  free(vec->arr);
  free(vec);
}

int main() { return 0; }
