#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  size_t capacity; // actual capacity
  int* arr;
  size_t size; // index
} Vector;

Vector *create() {

  Vector *vec = (Vector *)malloc(sizeof(Vector)); // creating vector

  vec->arr = (int *)malloc(sizeof(int) * 10); // allocating initial capacity

  vec->size = 0;      // starting index
  vec->capacity = 10; // capacity

  return vec;
}

void push(Vector *vec, int v) {

  if (vec->size >= vec->capacity) { // if the index is greater or equal to the
                                    // capacity (last index) then ->
    vec->capacity *= 2;             // double the capacity
    vec->arr = (int *)realloc(
        vec->arr, sizeof(int) * vec->capacity); // realloc the capacity
  }
  vec->arr[vec->size++] = v; // otherwise just store the value at the index of
                             // size and then increments its by one
}

int pop(Vector *vec) { // deleting last element

  int temp = vec->arr[vec->size - 1];
  
  vec->arr[vec->size - 1] = 0;

  vec->size = vec->size - 1;
  
  return temp;
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
