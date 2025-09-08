#include <stdio.h>
#include <stdlib.h>
#include "Binary_Tree.h"
#include "Tree_Node.h"

Binary_Tree* create_binary_tree() {

    Binary_Tree* bst = (Binary_Tree*)malloc(sizeof(Binary_Tree));

    if (bst == NULL) {
        perror("Could not allocate memory for bst\n");
        return NULL;
    }

    bst->root = NULL;

    return bst;
}


Binary_Tree* init_binary_tree(int data) {

    Binary_Tree* bst = (Binary_Tree*)malloc(sizeof(Binary_Tree));

    if (bst == NULL) {
        perror("Could not allocate memory for bst\n");
        return NULL;
    }

    bst->root = create_tree_node(data);
    return bst;
}

void insert_into_bst(Binary_Tree* self, int data) {
    
    if (self == NULL) { 
        perror("The bst is not initialized\n");
        return;
    }

    self->root = insert_rec(self->root, data);
}

Tree_Node* insert_rec(Tree_Node* root, int data) {

    if (root == NULL) {
        return create_tree_node(data);
    }
    
    if (data == root->data) {
        return root;
    }

    if (data < root->data) {

        root->left = insert_rec(root->left, data);
    
    } else if (data > root->data) {
        
        root->right = insert_rec(root->right, data);
    }

    return root;
}

void remove_from_bst(Binary_Tree* self, int data) {

    if (self == NULL) { 
        perror("The bst is not initialized\n");
        return;
    }
    
    self->root = remove_rec(self->root, data);
}


Tree_Node* get_min_of_right(Tree_Node* root) {
    
    Tree_Node* current = root->right;

    while (current != NULL && current->left != NULL) {
        current = current->left;
    }

    return current;
}

void swap_data(Tree_Node* a, Tree_Node* b) {
    
    a->data = a->data ^ b->data;
    b->data = a->data ^ b->data;
    a->data = a->data ^ b->data;
}

Tree_Node* remove_rec(Tree_Node* root, int data) {
    
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = remove_rec(root->left, data);
    } 
    
    else if (data > root->data) {
        root->right = remove_rec(root->right, data);
    } 
   
    else {
          
        // Case 0 leafs or it only has one right child.
        if (root->left == NULL) {
            Tree_Node* temp = root->right;
            free(root);
            return temp;
        }
       
        // Case 0 leafs or it only has one left child
        if (root->right == NULL) {
            Tree_Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 2 children
        Tree_Node* to_swap = get_min_of_right(root);
        root->data = to_swap->data;  
        root->right = remove_rec(root->right, to_swap->data);
    }

    return root;
}


int binary_search(Binary_Tree* self, int data) {

    if (self == NULL) {
        perror("BST not initialized\n");
        return 0;
    }

    return binary_search_rec(self->root, data);
}

int binary_search_rec(Tree_Node* root, int data) {

    if (root == NULL) {
        printf("Target not found\n");
        return 0;
    }

    if (data < root->data) {
        return binary_search_rec(root->left, data);
    }
    else if (data > root->data) {
        return binary_search_rec(root->right, data);
    } 
    
    printf("Target found\n");
    return 0;
}

void print_tree(Binary_Tree* self, void(*srch)(Tree_Node*)) { 
    srch(self->root);
}

void inorder(Tree_Node* root) {
    
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Tree_Node* root) {

    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Tree_Node* root) {
    
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void delete_rec(Tree_Node* root) {
    
    if (root == NULL) {
        return;
    }
    
    delete_rec(root->left);
    delete_rec(root->right);
    free(root);    
}

void delete_tree(Binary_Tree* self) {
    
    if (self == NULL) {
        perror("Bst is not defined\n");
        return;
    }
    
    delete_rec(self->root);

    free(self);
}

