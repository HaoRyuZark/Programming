#include <stdlib.h>
#include <stdio.h>
#include "Tree_Node.h"

Tree_Node* create_tree_node(int data) {
    
    Tree_Node* node = (Tree_Node*)malloc(sizeof(Tree_Node));
    
    if (node == NULL) {
        perror("Could not allocate memory for the tree node");
        return NULL; 
    }
    
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;

}
