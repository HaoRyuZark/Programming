#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000
#define MAX_KEY_LEN 256

/*
 * ===========================
 *          HASHING
 * ===========================
 *
 * Definition:
 * Hashing is a technique used to map data of arbitrary size 
 * (keys) to fixed-size values (hashes) using a hash function.
 * These hash values act as indexes into a hash table, enabling
 * very fast insertion, search, and deletion on average.
 *
 * Open Hashing (Separate Chaining):
 * In open hashing, each table index points to a linked list (or
 * other data structure) of entries that share the same hash.
 * Collisions are handled by simply adding the new key to the list.
 *
 * Closed Hashing (Open Addressing):
 * In closed hashing, all elements are stored directly in the hash
 * table array. When a collision occurs, probing is used to find
 * another open slot.
 *
 * Linear Probing:
 * When a collision occurs, check the next slot (index + 1), and 
 * continue sequentially until an empty slot is found.
 *
 * Quadratic Probing:
 * Similar to linear probing, but instead of moving one step at a 
 * time, the step size increases quadratically (i.e. 1^2, 2^2, 3^2...).
 * This helps reduce clustering.
 *
 * Double Hashing:
 * Uses a second hash function to calculate the step size for probing,
 * giving better distribution and minimizing clustering.
 *
 * How Big Should a Hash Table Be:
 * Ideally, the table size should be a prime number to minimize
 * clustering and reduce collisions. The size should be chosen
 * based on the expected number of elements and desired load factor.
 * A common practice is to keep the load factor <= 0.7 for good
 * performance.
 */
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
