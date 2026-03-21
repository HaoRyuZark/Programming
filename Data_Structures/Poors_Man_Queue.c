#include <stdio.h>

typedef struct Poors_Man_Queue {

    int right[10];
    int left[10];
    int right_index;

} Poors_Man_Queue;

Poors_Man_Queue init() {
   
    Poors_Man_Queue queue = {
        .right = {0},
        .left = {0},
        .right_index = 0,
    };

    return queue;
}

void enqueue(Poors_Man_Queue* queue, int data) {
    
   if (queue->right_index >= 10) {
        return;
   } 

   queue->right[queue->right_index++] = data;
}

int dequeue(Poors_Man_Queue* queue) {
    
    int j = 0;
    int i = 0;

    for (i = queue->right_index - 1; i >= 0; i--) {
        queue->left[j++] = queue->right[i];
    }
     
    int ret = queue->left[j--];

    for (i = 0; j >= 0; j--) {
         queue->right[i++] = queue->left[j];
    }

    queue->right_index = i;
    
    return ret;
}

int main() {
    
    return 0;
}
