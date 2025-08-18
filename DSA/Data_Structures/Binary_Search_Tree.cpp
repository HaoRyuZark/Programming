#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

/*
 * Traversals:
 *
 * BFS: Level Order
 *
 * DFS:
 *  Preorder:   root left right
 *  Inorser:    left root right
 *  Postorder:  right root left
 *
 *  */

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Binary_Search_Tree {
    
    struct Node* root;

} Binary_Search_Tree;

Node* create_node(int data) {
    
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Binary_Search_Tree create_bst() {

    Binary_Search_Tree tree = {
        .root = NULL,
    };

    return tree;
}

Binary_Search_Tree create_bst_from(int data) {
    
    Node* root = create_node(data); 

    Binary_Search_Tree tree = {
        .root = root,
    };

    return tree;
}

int search(Node* root, int data) {
    
    if (root->data == data) {
    
        return 1;
    
    } else if (root->data > data) {

        return search(root->right, data);
    
    } else {
       return search(root->left, data); 
    }
}

Node* search_node(Node* root, int data) {
    
    if (root->data == data) {
    
        return root;
    
    } else if (root->data > data) {

        return search_node(root->right, data);
    
    } else {
       return search_node(root->left, data); 
    }
}

int binary_search(Binary_Search_Tree* self, int data) {
    
    if (self == NULL) {
        return -1;
    }

    if (self->root == NULL) {
        return -1;
    }

    return search(self->root, data);
}

int insert(Node* root, int data) {

    if (root == NULL) {
        
        root = create_node(data);        
        
        return 0;

    } else {
        
        if (data == root->data) {
            return -1;
        }

        if (data < root->data) {
            
            return insert(root->left, data);
        
        } else {

            return insert(root->right, data);
        }
    }
}

int insert_data(Binary_Search_Tree* self, int data) {

    if (self == NULL) {
        return -1;
    }

    return insert(self->root, data);
}


int find_min(Node* root) {

    if (root == NULL) {
        return -1;
    }

    if (root->left == NULL) {
        return root->data;
    }

    return find_min(root);
}

int find_max(Node* root) {

    if (root == NULL) {
        return -1;
    }

    if (root->right == NULL) {
        return root->data;
    }

    return find_max(root);
}

Node* find_min_node(Node* root) {

    if (root == NULL) {
        return root;
    }

    if (root->left == NULL) {
        return root;
    }

    return find_min_node(root);
}

/*
 * Case No child -> delete
 * Case One child -> right/left shift
 * Case Two Childs -> find_min in right-substree -> copy value to the target node -> delete duplicate from the right substree
 * */
Node* delete_node(Node* root, int data) {
    
    if (root == NULL) {
    
        return root;
    
    } else if (data > root->data) { // Re-assingnin necessary for updating the parent node
        
        root->right = delete_node(root->right, data); // Updating right-pointer of parent node
    
    } else if (data < root->data) {
        
        root->left = delete_node(root->left, data); // Updating left-pointer of parent node
    
    } else {
         
        if (root->left == NULL && root->right == NULL) {
            
            free(root);
        
        } else if (root->left == NULL) {  // Temp pointer necessary for the case that the child has a substree

            Node* temp = root;
            root = root->right;
            free(temp);

        } else if (root->right == NULL){ // Same here 
            
            Node* temp = root;
            root = root->left;
            free(root->left);
        
        } else {
            
            Node* temp = find_min_node(root->right); // Min node in the right of the target
            root->data = temp->data;                            // Copying the value of the min node
            root->right = delete_node(root->right, temp->data);  // Re staring delete operation for the new target
        }
    }

    return root; // Returning the current node for the re-assingments
}

void level_order(Node* root) {

    if (root == NULL) {
        return;
    }
    
    std::queue<Node*> queue;

    queue.push(root);

    while (!queue.empty()) {

        Node* current = queue.front();

        printf("%d", current->data);

        if (current->left != NULL) {
            queue.push(current->left);
        }

        if (current->right != NULL) {
            queue.push(current->right);
        }

        queue.pop();
    }
}

void preorder(Node* root) {
    
    if (root == NULL) {
        return;
    }

    printf("%d", root->data);

    preorder(root->left);
    preorder(root->right);
}

void inorder_ascending(Node* root) {
    
    if (root == NULL) {
        return;
    }

    inorder_ascending(root->left);
    printf("%d", root->data);
    inorder_ascending(root->right);
}

void inorder_descending(Node* root) {
    
    if (root == NULL) {
        return;
    }

    inorder_descending(root->right);
    printf("%d", root->data);
    inorder_descending(root->left);
}


void postorder(Node* root) {
    
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d", root->data);
}


int main() {
    return 0;
}
