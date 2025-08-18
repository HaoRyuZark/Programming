#include <stdio.h>
#include <stdlib.h>

/*
 * B-Trees
 *
 * This data structures a pretty useful to optimize disc operation because they are cache friendly because, each node can store a 
 * pack of keys which are stored contiguous.
 *
 * Operation:
 *
 * - Searching:
 *   This one is pretty stright forward:
 *      -> Iterate over the values of a node compare the target with the keys
 *      -> If not found move to the node whose value are between keys[i] keys[i +1]
 *      -> Repeat the operation until found and return true (or value associated with the key in real use scenarios) else 
 *         return false
 * - Adding a key:
 *    # For the case the node is not overfull after insertion:
 *      -> Just put the key at the end of the keys at array and sort
 *    
 *    # When it is overfull after insertion
 * 
 *      -> Splint the node into two nodes, push the middle key to th parent node and if full again the repeat the process (Recursion). 
 *         If you arraive at the root node and it becomes full then:
 *
 *      -> Take the value at middle and make a new node whose children will be a node with values less than itself and another with
 *         the ones greater than itself. Only if we are at the root node!!!!!!
 *
 *
 *  - Removing a key:
 *      General first step search for the key and if found perform the deletion
 *
 *      Leaf cases
 *      # Case not under min after delete:
 *          -> nothing more 
 *      
 *      # Case underfull 1:
 *          -> take a key from one siebling the min for the right and the max for the left depending on the choice
 *             if possible -> they have enough keys. Take the key from the siebling and make it the new separator of the parent node 
 *             (the most right or left key) and then take the previous separator an use it to fill our node
 *      
 *      # Case underfull 2:
 *          -> Take the siebling, our node with its number of keys below the minimum, and the separator between of the parent node 
 *          and merge them into a node -> if the parent node now ends up with to few keys use repat the process of the cases 1 and 2 depending 
 *          on the sieblings (recursion)
 *
 *      Not leaf case:
 *      -> Take largest value on the left substree or the smallest on the right to become the new separator. But in the case of underfullness
 *      we already know what to do depending on the case. See above 
 * */
const int MAX_NUMBER_OF_KEYS = 4;
const int MAX_NUMBER_OF_CHILDREN = MAX_NUMBER_OF_KEYS + 1;
const int MIN_NUMBER_OF_KEYS = MAX_NUMBER_OF_KEYS / 2;

/*
 * This node object has an array of keys -> the values we want to store and use as delimiters and 
 * a array of pointers to nodes which represent the children.
 *
 * */
typedef struct Node {
    
   struct Node* childs[MAX_NUMBER_OF_CHILDREN];
   int keys[MAX_NUMBER_OF_KEYS];
   int count;

} Node;

typedef struct B_Tree {
    
    Node* root;
} B_Tree;

B_Tree* create_b_tree() {

    B_Tree* tree = (B_Tree*)malloc(sizeof(struct B_Tree));
    tree->root = NULL;

    return tree;
}

Node* create_node(int data) {
    
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->count = 1;
    node->keys[0] = data;

    return NULL; 

}

int main() {
    printf("Verga");
    return 0;
}
