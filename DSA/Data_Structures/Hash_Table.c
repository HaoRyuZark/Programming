#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000
#define MAX_KEY_LEN 256

/* Hash Tables
 *
 * -> Hash tables are arrays with a hash function that allow us to store key-value pair.
 * -> A hash function is a partially injectice function takes some input and returns a numeric output.
 * -> When more than one key maps to the same index it is called a collisions
 *
 *  Handling collisions
 * 
 *  - Open Hashing: Create a linkedlist at the index when a collision takes place. For further collisions append 
 *   the value at the end of the linkedlist.
 *
 *  - Closed Hashing: There are different approaches for this but all have the goal of finding another place in the hash table to 
 *    put the pair instead of chaining them in a linked list.
 *
 *    -> Linear Probing (h(k) + i) % size: Sequential search.
 *       Pros: Table completely full
 *             Simple
 *             Efficient
 *       Cons: Clustering
 *             For Some hash functions it will be very problematic
 *
 *    -> Quadratic Probing (h(k) + i^2) % size: cuadratic search
 *          Pros: Same as the linear approach and solves the Clustering problematic
 *          Cons: In some cases the the table is not completely filled
 *
 *    -> Double Hashing (h1(k) + i *h2(k)) & size:
 *          Pros: No Clustering
 *                Uniform distribution
 *                More effective than the preious ones
 *          Cons:
 *              Collisions can still occur and can cause thrashing 
 * */

typedef struct Pair {
    char key[MAX_KEY_LEN];
    int value;
    int is_deleted;
} Pair;

typedef struct HashTable {
    Pair* entries[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key) {

    unsigned long hash = 5381;
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

HashTable* create_table() {

    HashTable* table = malloc(sizeof(HashTable));
   
    if (!table) {
        perror("Failed to allocate hash table");
        exit(1);
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        table->entries[i] = NULL;
    }

    return table;
}

// Create a new key-value pair
Pair* create_pair(const char* key, int value) {
    
    Pair* pair = malloc(sizeof(Pair));
    
    if (!pair) return NULL;

    strncpy(pair->key, key, MAX_KEY_LEN - 1);
    
    pair->key[MAX_KEY_LEN - 1] = '\0';
    pair->value = value;
    pair->is_deleted = 0;
    
    return pair;
}

// Insert a key-value pair
void insert(HashTable* table, const char* key, int value) {
    
    unsigned int index = hash(key);
    unsigned int original_index = index;

    // Loop for handling collisions
    while (table->entries[index] != NULL) {
        
        if (!table->entries[index]->is_deleted && strcmp(table->entries[index]->key, key) == 0) {
            
            table->entries[index]->value = value; // Update value
            return;
        }

        index = (index + 1) % TABLE_SIZE;
        
        if (index == original_index) {   //Stop signal if we are where we started
            printf("Hash table is full!\n");
            return;
        }
    }
    
    // Default behaviour
    table->entries[index] = create_pair(key, value);
}

// Search for a value by key
int* search(HashTable* table, const char* key) {
    
    unsigned int index = hash(key);
    unsigned int original_index = index;

    while (table->entries[index] != NULL) {
        
        if (!table->entries[index]->is_deleted && strcmp(table->entries[index]->key, key) == 0) {
            
            return &table->entries[index]->value;
        }
        
        index = (index + 1) % TABLE_SIZE;
        
        if (index == original_index) break;
    }

    return NULL; // Not found
}

// Delete a key-value pair by key
void delete(HashTable* table, const char* key) {
    
    unsigned int index = hash(key);
    unsigned int original_index = index;

    while (table->entries[index] != NULL) {
    
        if (!table->entries[index]->is_deleted && strcmp(table->entries[index]->key, key) == 0) {
            
            table->entries[index]->is_deleted = 1;
            return;
        }
        
        index = (index + 1) % TABLE_SIZE;
        
        if (index == original_index) break;
    }
}

// Free the hash table
void free_table(HashTable* table) {
    
    for (int i = 0; i < TABLE_SIZE; ++i) {
        
        if (table->entries[i] != NULL) {
            free(table->entries[i]);
        }
    }
    free(table);
}

// Demo
int main() {
    
    HashTable* table = create_table();

    insert(table, "apple", 10);
    insert(table, "banana", 20);
    insert(table, "orange", 30);

    int* val = search(table, "banana");
    
    if (val) printf("banana = %d\n", *val);

    delete(table, "banana");

    val = search(table, "banana");
    
    if (!val) printf("banana not found (deleted)\n");

    free_table(table);
    return 0;
}
