#ifndef BINARY_TREE
#define BINARY_TREE

#include "Tree_Node.h"

typedef struct Binary_Tree {
    
    Tree_Node* root; 

} Binary_Tree;

Binary_Tree* create_binary_tree();

Binary_Tree* init_binary_tree(int data);

void insert_into_bst(Binary_Tree* self, int data);

Tree_Node* insert_rec(Tree_Node* root, int data);

void remove_from_bst(Binary_Tree* self, int data);

Tree_Node* remove_rec(Tree_Node* root, int data);

int binary_search(Binary_Tree* self, int data);

int binary_search_rec(Tree_Node* root, int data);

void print_tree(Binary_Tree* self, void(*srch)(Tree_Node*));

void inorder(Tree_Node* root);

void preorder(Tree_Node* root);

void postorder(Tree_Node* root);

void delete_tree(Binary_Tree* self);

void delete_rec(Tree_Node* root);

#endif // !BINARY_TREE
