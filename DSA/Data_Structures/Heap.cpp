#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>


// Complete binary tree:
// -> Every level is completely filled exept for the leafs at the extrems
//
// Heap Property:
// -> Each node is smaller/greater(for max heap) than or equal to its children.
typedef struct Heap {    
    std::vector<int> arr;
} Heap;

/*
 * Heap as array:
 *
 * Node i: 
 *  -> left: 2i + 1
 *  -> right: 2i + 2
 *  -> parent (i - 1)/2
 * 
 * Example:
 *
 * -0 1 2 3  4 5 6  8
 *  3 6 4 9 12 8 7 14
 *
 *      3
 *   /   \
 *  6     4
 * / \   \  \
 * 9 12   8  7   
 * */

int get_parent(int index) {
    return (index - 1)/ 2;
}

int get_left_child(int index) {
    return 2 * index + 1;
}

int get_right_child(int index) {
    return 2 * index + 2;
}

void shift_up(Heap* heap, int index) {
    
    int parent = get_parent(index);
    
    while (index != 0 && heap->arr[index] < heap->arr[parent]) {
        
        std::swap(heap->arr[index], heap->arr[parent]);
        index = parent;
        parent = get_parent(index);
    }
}

void shift_down(Heap* heap, int index) {

    int left_index = get_left_child(index);
    int right_index = get_right_child(index);
    
    int min = std::min(heap->arr[left_index], heap->arr[right_index]);
    int min_index = (heap->arr[left_index] == min)? left_index : right_index;

    while (heap->arr[index] > heap->arr[min_index]) {

        std::swap(heap->arr[index], heap->arr[min_index]);
        
        index = min_index;

        left_index = get_left_child(index);
        right_index = get_right_child(index);

        min = std::min(heap->arr[left_index], heap->arr[right_index]);
        min_index = (heap->arr[left_index] == min)? left_index : right_index;
    }
}

void insert(Heap* heap, int val) {
    
    heap->arr.push_back(val);
    shift_up(heap, heap->arr.size() - 1);
}

int get_min(Heap* heap) {
    return heap->arr[0];
}

int extract_min(Heap* heap) {
    
    std::swap(heap->arr[0], heap->arr[heap->arr.size() - 1]);
    
    int min = heap->arr[heap->arr.size() - 1];
    heap->arr.pop_back();

    shift_down(heap, 0);

    return min;
}

int find_index(Heap* heap, int val) {
    
    int i = 0;
    int found = 1;

    for (i = 0; i < heap->arr.size(); i++) {
        if (heap->arr[i] == val) {
            found = 0;
            break;
        }
    }
    if (found != 0) {
        i = -1;
    }

    return i;
}

void update(Heap* heap, int val, int new_val) {
    
    int index = find_index(heap, val);

    heap->arr[index] = new_val;

    if (new_val < val) { 
        shift_up(heap, index);

    } else {
        shift_down(heap, index);
    }
}

Heap* heapify(std::vector<int> &arr) {

    Heap* heap = (Heap*)malloc(sizeof(Heap));
    
    for (int i = 0; i < arr.size(); i++) {
        heap->arr.push_back(arr[i]);
    }

    for (int i = arr.size() - 1; i >= 0; --i) {
        shift_down(heap, i);
    }

    return heap;
}

void heap_sort(std::vector<int> arr) {

    Heap* heap = heapify(arr);
    
    std::vector<int> result;
    int i = 0;

    while (!heap->arr.empty()) {
        arr[i] = extract_min(heap);
        i++;
    }

    free(heap);
}

int main() {
    
    return 0;
}
