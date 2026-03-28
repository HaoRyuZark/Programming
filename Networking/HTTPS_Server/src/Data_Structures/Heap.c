#include "Heap.h"
#include "Vector.h"
#include "../Common/Error_Handling.h"

Heap create_heap() {

    Heap heap;

    heap.vec = create_vec();

    return heap;
}

Heap create_heap_from(Vec* vec) {

    Heap heap;

    heap.vec = heapify_vec(vec);

    return heap;
}

Heap create_heap_from_arr(int* arr) {

    Heap heap;

    heap.vec = create_vec_from(heapify_arr(arr), sizeof(arr)); // TODO

    return heap;

}

int get_left_child(int index) {
     
    return (2 * index) + 1;
}

int get_right_child(int index) {
    
    return (2 * index) + 2;
}

int get_parent(int index) {

    return (index - 1)/ 2;
}

void swap_last_and_first(Vec* vec) {

    int first = vec->arr[0];
    int last = vec->arr[vec->len];
    
    int temp = first;
    vec->arr[0] = last;
    vec->arr[vec->len] = first;
}

void shift_down(Heap* self) {

    int left_index = get_left_child(0);
    int right_index = get_right_child(0);


}

void shift_up(Heap* self);

void enqueue(Heap* self, int data) {

    handle_error(self, "The heap has not been inintialized")
    
    push_back(self->vec, data);
    shift_up(self);
}

int dequeue(Heap* self) {

    handle_error_with_return(self, -1, "The heap has not been inintialized")
     
    swap_last_and_first(self->vec);    
    int res = pop_back(self->vec);    
    shift_down(self);

    return res;
}

Vec* heapify_vec(Vec* vec);

int* heapify_arr(int* arr);


