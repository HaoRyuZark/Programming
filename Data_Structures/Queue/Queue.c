#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NO_ELEMENTS -134

typedef struct Node {
    int data;
    struct Node* next;
}Node;

typedef struct Queue {
    Node* first;
    Node* last;
    size_t data_size;
    unsigned int len;
} Queue;


Node* create_node(int data) {

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void create_queue(Queue* self) {


    if (self == NULL) {
        perror("Could not allocate memory for queue");
        return;
    }

    self->first = NULL;
    self->last = NULL;
    self->len = 0;
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

void destructor(Queue* self) {
    if (self == NULL) { return; }

    if (self->first == NULL) { return; }

    Node* temp; 

    while (self->first != NULL) { 
        temp = self->first;
        self->first = self->first->next;
        free(temp);
    }
}


int main() {
    return 0;
}
