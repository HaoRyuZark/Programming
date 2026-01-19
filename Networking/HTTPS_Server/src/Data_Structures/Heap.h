#ifndef HEAP_H
#define HEAP_H 

#include "Vector.h"

typedef struct Heap {

    Vec* vec;

} Heap;

Heap create_heap();

Heap create_heap_from(Vec* vec);

Heap create_heap_from_arr(int* arr);

void bubble_down(Heap* self);

void bubble_up(Heap* self);

void enqueue(Heap* self, int data);

int dequeue(Heap* self);

Vec* heapify_vec(Vec* vec);

int* heapify_arr(int* arr);

#endif
