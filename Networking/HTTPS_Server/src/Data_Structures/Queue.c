#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NO_ELEMENTS -134

Queue* create_queue() {

    Queue* self = (Queue*)malloc(sizeof(Queue));

    if (self == NULL) {
        perror("Could not allocate memory for queue");
        return NULL;
    }

    self->first = NULL;
    self->last = NULL;
    self->len = 0;

    return self;
}


void enqueue(Queue* self, int data) {

    if (self == NULL) {
        perror("Queue is NULL");
        return;
    }
    
    Node* node = create_node(data);

    if (self->first == NULL) {
    
        self->first = node;
        self->last = node;
    
    } else {
        
        self->last->next = node;
        self->last = self->last->next;
    }

    self->len++;
}


int dequeue(Queue* self) {

    if (self == NULL) { 
        perror("Queue is NULL");
        return NO_ELEMENTS;
    }

    if (self->first == NULL) { 
        printf("The queue is empty");
        return NO_ELEMENTS;
    }   
    
    int data = self->first->data; 
    Node* new_first = self->first->next;
    Node* current_first = self->first; 
    
    if (self->last == self->first) {
        self->last = new_first;
    }

    self->first = new_first;
    self->len--;

    free(current_first);

    return data;
}

