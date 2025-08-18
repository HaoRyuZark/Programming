#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    void* data;
    struct Node* next;
}Node;

typedef struct Queue {
    Node* first;
    Node* last;
    size_t data_size;
    unsigned int len;
} Queue;

Queue* create_queue(size_t data_size) {
    Queue* new = (Queue*)malloc(sizeof(Queue));
    new->data_size = data_size;
    new->len = 0;
    return new;
}

void enqueue(Queue* self, void* data) {
    if(self == NULL) {
        return;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(self->data_size);
    new_node->next = NULL;

    memcpy(new_node->data, data, self->data_size);

    if(self->last == NULL) {
        self->last = new_node;
        return;
    }
    self->last->next = new_node;
    self->last = new_node;
    self->len += 1;
}

void* dequeue(Queue* self) {

    if(self->first == NULL) {
        return NULL;
    }

    Node* temp = self->first;
    void* data = temp->data;
    self->first = self->first->next;
    
    if(self->first == NULL) {
        self->last = NULL;
    }
    self->len -= 1;
    free(temp);
    return data;
}

int main() {
    return 0;
}
