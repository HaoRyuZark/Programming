#ifndef NODE_H 
#define NODE_H 

typedef struct Node {
    struct Node* next;
    int data;
} Node;

struct Node* create_Node(int data);

#endif
