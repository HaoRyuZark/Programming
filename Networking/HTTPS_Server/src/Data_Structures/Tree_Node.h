#ifndef TREE_NODE_H
#define TREE_NODE_H 

typedef struct Tree_Node {

    int data;
    struct Tree_Node* left;
    struct Tree_Node* right;

} Tree_Node;

Tree_Node* create_tree_node(int data);

#endif // !TREE_NODE_H
