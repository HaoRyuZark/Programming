#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

struct Node* create_Node(int data) {
    
    Node* node = (Node*)malloc(sizeof(Node));
    
    if (node == NULL) {
        perror("Could not allocate memory for the node");
        return NULL; 
    }
    
    node->data = data;
   
    return node;
}
