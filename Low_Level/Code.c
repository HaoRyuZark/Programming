#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Basic C Features 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Bitweise Operators 

//////////////////////////////////////////////////////////////////////////////////////////////////////

//  

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Reading and Writing Files 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Format Specifiers 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Structs, Enums and Unions 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Simulating Object-Oriented Programming in C 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Function Pointers

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Void Pointers

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Macros

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Arenas 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// C strings 

#define MAX_LEN 1000

void c_strings() {
    
    char buffer[4] = {'A', 'B', 'C', '\0'};

    // String literal, will be interpreted as a const char* 
    char* str = "A normal string with no much to it";
    
    int len = strnlen(str, MAX_LEN); // number of chats plus \0 terminator 

    // Tokenization (destructive)!!!!
    
    char* piece = strtok(str, " "); // returns the string until the separator 
    // will return "A\0"

    piece = strtok(NULL, " "); // will take the previosly used string but now without "A"
    
    printf("%s", piece);
    
    
    // Newer alternaitves 
    char* original = strdup("AHHHHHH, ajbakjnvkjnc , ijajavja");
    char* rest = original;
    char* token;
    
    // Similar to the original but with only one call
    while ((token = strtok_r(rest, ",", &rest))) {
        printf("Token: %s", token);
    }
    
    // This one also return separators separated by separators 
    while ((token = strsep(&original, ",")) != NULL) {
        printf("Token: %s", token);
    }    

    // Other string functions
    char dest[50];

    strncpy(dest, "Hello, World!", sizeof(dest) - 1); // Copy string

    strncat(dest, " How are you?", sizeof(dest) - strlen(dest) - 1); // Concatenate strings

    int cmp = strncmp(dest, "Hello, World! How are you?", strnlen(dest, sizeof(dest)) ); // Compare strings

    printf("String length: %zu\n", strlen(dest)); // Get string length  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Tagged Unions 

enum result {
    Some,
    Err,
};

struct result_alg {
    
    enum result res; 

    union {
        char* c;
        void* p;
    } value;
};

void demo_tagged_unions() {

    char abc[2] = {'a', 'b'};

    struct result_alg r = {r.res = Some, r.value.c =abc};

    switch (r.res) {
        case Some: printf("Some content"); break;
        case Err: printf("Error"); break;
        default: printf("Invalid State");
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// memset, memcpy, strcpy, memmove 

char* get_deafult_string(int size) {

    char* s = (char*)malloc(sizeof(char)*size);
    
    if (s == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        s[i] = (char)i;
    }

    return s;
}

void memory_functions_example() {
    
    int size = 10; 
    char* s = get_deafult_string(size);
    char* dest = (char*)malloc(sizeof(char) * size);
    char* dest_2 = (char*)malloc(sizeof(char) * size); 

    memset(s, '1', size); // setting all characters to 1
    memcpy(dest, s, size); 
    memmove(dest, s, size); 
    strncpy(dest_2, s, size);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Pointers 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Cursed Pointers

int (*x())[20]; // s is function that that returns a pointer to an array of 20 integers

int(*(*y)[])(); // y is pointer to an array of function pointers of function that return an integer

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Pointer Arithmetic 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// restrict

void foo(int* __restrict a, int* __restrict b) {
    for (int i = 0; i < 100; ++i) {
        a[i] += b[i];
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// volatile

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Memory Management

void memory_management_c_style() {

    // Dynamic memory allocation using malloc and free
    int* arr = (int*)malloc(5 * sizeof(int));

    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }

    for (int i = 0; i < 5; ++i) {
        printf("%d", arr[i]);
    }

    int* temp = (int*)realloc(arr, 10 * sizeof(int));

    if (temp != NULL) {
        arr = temp;
        for (int i = 5; i < 10; ++i) {
            arr[i] = i * 10;
        }
    }

    free(arr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Using Structs as Buffers

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Random Numbers

void random_numbers_example() {

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 5; ++i) {
        int num = rand() % 100; // Random number between 0 and 99
        printf("%d ", num);
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Number Systems 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Bif Fields 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// pthreads 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Standard Threads

int main() {

    return 0;
}
