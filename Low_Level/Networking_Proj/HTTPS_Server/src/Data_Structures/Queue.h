#ifndef QUEUE_H
#define QUEUE_H

#include <unistd.h>
#include "Node.h"


typedef struct Queue {
    
    Node* first;
    Node* last; 
    size_t len;

} Queue;

Queue* create_queue();

void enqueue(Queue* self, int data);

int dequeue(Queue* self);

#endif
