# The C Programming Language

My favorite language. This is a quick reference for `C` with examples and some explanations. I am 
not trying to make a better reference this is just for me. For a full referece there are man-pages.

## Header Files in C 

This are commonly used header files inside `C` projects

```c
#include <errno.h>
#include <stdatomic.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "./my_custom_header.h"
```

## Numbers in C 

In the `C` programming language numbers in other base different from 10 can be used by adding a prefix to the number's start

```c

int b = 0b10010; // Binary

int o = 0222; // Octal 

int hex = 0xFFFF; // Hexadecimal
```

--- 

## Memory Management

Memory management is a critical aspect of systems programming. It involves allocating and deallocating memory for variables and data structures. In C, memory management is done using functions like `malloc`, `calloc`, `realloc`, and `free`.

Example of memory allocation in C:

```C

#include <stdio.h>
#include <stdlib.h>

void memory_management_c_style() {

    // Requesting memory
    int* arr = (int*)malloc(5 * sizeof(int));

    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }

    for (int i = 0; i < 5; ++i) {
        printf("%d", arr[i]);
    }
    
    // Exapanding the memory previously requested
    int* temp = (int*)realloc(arr, 10 * sizeof(int));

    if (temp != NULL) {
        arr = temp;
        for (int i = 5; i < 10; ++i) {
            arr[i] = i * 10;
        }
    }
    
    // Very important freeing the memory after use
    free(arr);
}
```

---

## Pointers

Pointers are a fundamental concept in low-level programming. They allow you to directly manipulate memory addresses, which is crucial for performance 
and resource management. A pointer is a variable that stores the address of another variable.

Example of using pointers in C:

```c
#include <stdio.h>

int main() {

int var = 42;
    
    int* ptr = &var;

    printf("Value of var: %d\n", var);
    printf("Address of var: %p\n", (void *)&var);
    printf("Value of ptr: %p\n", (void *)ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);
    
    int** dptr = &ptr;

    printf("Dereferencing double pointer %d", **ptr);
    return 0;
}
```

### Function Pointers 

```c 
// Function pointer example
void (*func_ptr)(int); // pointer to a function that takes an int and returns void
```

### Cursed Pointers

Here some examples of "weird" pointers in C:

```c

//Really cursed pointers 
int (*x())[10]; //  x is a function that returns a pointer to an array of 10 integers 
int (*((*x)[]))() // x is a pointer to an array of pointers to functions that return int
char *(*(*x[8][8])())[10]; // x is a 2D array of pointers to functions that return pointers to arrays of 10 chars
```

### Strings and Char Buffers in C

In C, strings are represented as arrays of characters terminated by a null character ('\0'). Unlike higher-level languages, C does not have a native 
string type—just character arrays.

```c
char str1[] = "Hello";       // Size is automatically 6 (5 + null terminator)
char str2[10] = "Hi";        // Manually specified size, with extra space
char *str3 = "World";        // Pointer to a string literal (read-only)
```

#### Char Buffers

A char buffer is just a character array that can hold a string, often used for input/output or manipulation:

```c
char buffer[100];  // Buffer that can store up to 99 characters + '\0'
```

You can use functions like strcpy, strcat, strlen, and strcmp from <string.h> to work with these buffers.

#### Common Pitfalls

Always ensure there’s enough space for the null terminator `('\0')`.

Be careful with buffer overflows—C doesn’t do bounds checking.

Writing to string literals (like char *s = "text";) is undefined behavior.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char name[20];
    strcpy(name, "Alice");
    strcat(name, " Smith");
    printf("Full name: %s\n", name);
    return 0;
}
```

#### Common String functions in C 

```c 
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
```
---

## The __restrict keywords 

The `__restrict` keywords is used to tell the compiler that the pointer given 
is the only owner of the date during its lifetime.

```c 
void foo(int* __restrict a, int* __restrict b) {
    for (int i = 0; i < 100; ++i) {
        a[i] += b[i];
    }
}
```

--- 

## Bit Manipulation

Bit manipulation is a powerful technique in systems programming that allows you to perform operations at the bit level. This can be useful for 
optimizing performance, reducing memory usage, and implementing low-level protocols.

Example of bit manipulation in C:

```C
#include <stdio.h>
int main() {
    unsigned int x = 5; // 0000 0101 in binary
    unsigned int y = 3; // 0000 0011 in binary

    // Bitwise AND
    unsigned int and_result = x & y; // 0000 0001
    printf("AND result: %u\n", and_result);

    // Bitwise OR
    unsigned int or_result = x | y; // 0000 0111
    printf("OR result: %u\n", or_result);

    // Bitwise XOR
    unsigned int xor_result = x ^ y; // 0000 0110
    printf("XOR result: %u\n", xor_result);

    // Bitwise NOT
    unsigned int not_result = ~x; // 1111 1010 (assuming 8-bit representation)
    printf("NOT result: %u\n", not_result);

    return 0;
}
```

### Bit fields 

Is a series of bits where individual bits have meaning. They can be used to safe space, increase performance, etc. 
A common use is networking where we want to send compact packages.

```c
#include <stdio.h>
#include <stdint.h>

// File open flags (up to 8 bits)
#define F_READ     0x01  // 0000 0001
#define F_WRITE    0x02  // 0000 0010
#define F_APPEND   0x04  // 0000 0100
#define F_CREATE   0x08  // 0000 1000
#define F_TRUNC    0x10  // 0001 0000
#define F_BINARY   0x20  // 0010 0000

void open_file(const char *filename, uint8_t flags) {
   
   printf("Opening file: %s\n", filename);

    if (flags & F_READ)
        printf(" - Mode: READ\n");

    if (flags & F_WRITE)
        printf(" - Mode: WRITE\n");

    if (flags & F_APPEND)
        printf(" - Option: APPEND\n");

    if (flags & F_CREATE)
        printf(" - Option: CREATE if not exists\n");

    if (flags & F_TRUNC)
        printf(" - Option: TRUNCATE existing file\n");

    if (flags & F_BINARY)
        printf(" - Option: BINARY mode\n");
}


int main() {

    uint8_t flags = F_READ | F_WRITE | F_CREATE;

    open_file("data.txt", flags);

    return 0;
}
```

### Bit Masks 

It is a binary pattern used to modify anoher binary pattern using bitwise operations. 

--- 

## Macros 

The example may be overkill but here is linked list generated by macros 

```c 
#include <stdio.h>
#include <stdlib.h>

#define DEFINE_NODE(type)                   \
typedef struct Node_##type {                \
            type data;                      \
            struct Node_##type* next;       \
        } Node_##type;                                         

#define CREATE_NODE(type, val) ({                                           \ 
    Node_##type* new_node = (Node_##type*)malloc(sizeof(Node_##type));      \
     if (new_node == NULL) {                                                \
          perror("Succ");                                                   \
     }                                                                      \
    new_node->data = val;                                                   \
    new_node->next = NULL;                                                  \
    new_node;                                                               \
})

#define DEFINE_LINKED_LIST(type)           \
typedef struct Linked_List_##type {        \
        Node_##type* head;                 \
        Node_##type* tail;                 \
        int len;                           \
} Linked_List_##type;

#define CREATE_LINKED_LIST(type) ({                                                             \
        Linked_List_##type* list = (Linked_List_##type*)malloc(sizeof(Linked_List_##type));     \
        if (!list) { perror("Succ\n"); }                                                        \
        list->head = NULL;                                                                      \
        list->tail = NULL;                                                                      \
        list->len = 0;                                                                          \ 
        list;                                                                                   \
})

#define PUSH_FRONT(list, type, val) ({              \
        if (!list) {                                \
            perror("Succ\n");                       \
            ;                                       \
        }                                           \
        Node_##type* node = CREATE_NODE(type, val); \
        if (list->head == NULL) {                   \
            list->head = node;                      \
            list->tail = node;                      \
        } else {                                    \
            node->next = list->head;                \
            list->head = node;                      \
        }                                           \
        list->len++;                                \
})

#define PUSH_BACK(list, type, val) ({               \
    if (!list) {                                    \
        perror("Succ\n");                           \
        ;                                           \
    }                                               \
    Node_##type* node = CREATE_NODE(type, val);     \
    if (list->tail == NULL) {                       \
        list->head = node;                          \
        list->tail = node;                          \
    } else {                                        \
        list->tail->next = node;                    \
        list->tail = node;                          \
    }                                               \
    list->len++;                                    \
})

DEFINE_NODE(int)
DEFINE_LINKED_LIST(int)

int main() {

    Node_int* a = CREATE_NODE(int, 5);

    printf("%d\n", a->data);
    
    free(a);

    Linked_List_int* b = CREATE_LINKED_LIST(int);

    PUSH_FRONT(b, int, 6);

    printf("%d\n", b->head->data);

    PUSH_BACK(b, int, 7);

    printf("%d\n", b->tail->data);

    printf("%d\n", b->len);

    return 0;
}
```

--- 

## Simulating Objects in C 

We can emulate objects by using functions pointers inside structs. 

```c 

#include <sys/socket.h>
#include <netinet/in.h>
#include <net/ethernet.h>

typedef struct Server {

    int port;                       // port for the os to refidirect the traffic
    int socketfd;                   // file descriptor for the socket
    int backlog;                    // number of simultaneous connnections
    int interface;                  // this holds the actual IP address for the socket
    int address_family;             // socket address family 
    int domain;                     // communication domain, version of IP
    int protocol;                   // Data transfer protocol
    struct sockaddr_in server_addr; // Describes an IPv4 Internet domain socket address
    
    int (*run_func)(); 

} Server;

// Constructor
Server create_server(int port, int domain, int address_family, int protocol, int socket_type, int interface, 
                     int backlog); 

int main() {
  Server server; 

  // This will create an error due to the fields being not initialized 
  server.run_func();
  return 0;
}
```

--- 


## Arenas 


--- 

## The volatile keywords 

This keyboard is used to prevent the compiler from optimizing certain variables. 

```c 

void volatile_example() {
    volatile int flag = 0;

    // In a multi-threaded context, one thread might modify 'flag'
    // while another thread reads it. The 'volatile' keyword prevents
    // the compiler from optimizing away repeated reads of 'flag'.

    while (flag == 0) {
        // Wait for flag to be set by another thread
    }

    printf("Flag has been set!");
}

```
--- 

## Format Specifiers 

We have the following format specifiers for the printf functions.


| Format Specifier | Type                            | Example                                    |
| ---------------- | ------------------------------- | ------------------------------------------ |
| `%d`             | Signed int                      | `int x = 10; printf("%d", x);`             |
| `%i`             | Signed int                      | `int x = 10; printf("%i", x);`             |
| `%u`             | Unsigned int                    | `unsigned int x = 10; printf("%u", x);`    |
| `%f`             | Float / Double                  | `float x = 3.14; printf("%f", x);`         |
| `%lf`            | Double (scanf)                  | `double x; scanf("%lf", &x);`              |
| `%e`             | Scientific notation (lowercase) | `printf("%e", 123.45);`                    |
| `%E`             | Scientific notation (uppercase) | `printf("%E", 123.45);`                    |
| `%g`             | Shortest of `%f` or `%e`        | `printf("%g", 123.45);`                    |
| `%G`             | Shortest of `%F` or `%E`        | `printf("%G", 123.45);`                    |
| `%x`             | Hexadecimal (lowercase)         | `printf("%x", 255);`                       |
| `%X`             | Hexadecimal (uppercase)         | `printf("%X", 255);`                       |
| `%o`             | Octal                           | `printf("%o", 255);`                       |
| `%c`             | Character                       | `printf("%c", 'A');`                       |
| `%s`             | String                          | `printf("%s", "Hello");`                   |
| `%p`             | Pointer address                 | `printf("%p", ptr);`                       |
| `%ld`            | Long int                        | `long x = 1000; printf("%ld", x);`         |
| `%lu`            | Unsigned long int               | `unsigned long x; printf("%lu", x);`       |
| `%lld`           | Long long int                   | `long long x; printf("%lld", x);`          |
| `%llu`           | Unsigned long long int          | `unsigned long long x; printf("%llu", x);` |
| `%hd`            | Short int                       | `short x; printf("%hd", x);`               |
| `%hu`            | Unsigned short int              | `unsigned short x; printf("%hu", x);`      |
| `%Lf`            | Long double                     | `long double x; printf("%Lf", x);`         |
| `%%`             | Literal `%`                     | `printf("%%");`                            |


--- 

## Reading and Writing to Files

We can open files usinf the function `fopen(path, mode)`

Table of opening modes for files: 


| Opening Mode | Exaplantion | 
|:------------:| :-----------|
|`r` |  Searches file. If the file is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the first character in it. If the file cannot be opened fopen( ) returns NULL|
|`rb`|    Open for reading in binary mode. If the file does not exist, fopen( ) returns NULL|
|`w`|   Open for writing in text mode. If the file exists, its contents are overwritten. If the file doesn’t exist, a new file is created. Returns NULL, if unable to open the file|
|`wb`|  Open for writing in binary mode. If the file exists, its contents are overwritten. If the file does not exist, it will be created|
|`a`|   Searches file. If the file is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the last character in it. It opens only in the append mode. If the file doesn’t exist, a new file is created. Returns NULL, if unable to open the file|
|`ab`|  Open for append in binary mode. Data is added to the end of the file. If the file does not exist, it will be created|
|`r+`|  Searches file. It is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the first character in it. Returns NULL, if unable to open the file|
|`rb+`|     Open for both reading and writing in binary mode. If the file does not exist, fopen( ) returns NULL|
|`w+`|  Searches file. If the file exists, its contents are overwritten. If the file doesn’t exist a new file is created. Returns NULL, if unable to open the file|
|`wb+`|     Open for both reading and writing in binary mode. If the file exists, its contents are overwritten. If the file does not exist, it will be created|
|`a+`|  Searches file. If the file is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the last character in it. It opens the file in both reading and append mode. If the file doesn’t exist, a new file is created. Returns NULL, if unable to open the file|
|`ab+`| Open for both reading and appending in binary mode. If the file does not exist, it will be created|


### Text Files


| Writing Functions                                                  | Description                                                                                                          |
| ------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------- |
| `fprintf(FILE *stream, const char *format, ...)`                   | Similar to `printf()`, this function uses a formatted string and a variable argument list to print output to a file. |
| `fputs(const char *str, FILE *stream)`                             | Writes a string to a file and appends a newline at the end.                                                          |
| `fputc(int char, FILE *stream)`                                    | Writes a single character to a file.                                                                                 |
| `fputw(int num, FILE *stream)`                                     | Writes an integer value to a file.                                                                                   |
| `fwrite(const void *ptr, size_t size, size_t count, FILE *stream)` | Writes a specified number of bytes to a binary file.                                                                 |



| Reading Functions                                           | Description                                                                   |
| ----------------------------------------------------------- | ----------------------------------------------------------------------------- |
| `fscanf(FILE *stream, const char *format, ...)`             | Uses a formatted string and variable argument list to read input from a file. |
| `fgets(char *str, int n, FILE *stream)`                     | Reads an entire line from a file.                                             |
| `fgetc(FILE *stream)`                                       | Reads a single character from a file.                                         |
| `fgetw(FILE *stream)`                                       | Reads an integer value from a file.                                           |
| `fread(void *ptr, size_t size, size_t count, FILE *stream)` | Reads a specified number of bytes from a binary file.                         |


Example: 

```c
#include <stdio.h> 
#include <stdlib.h>

int main() {

    FILE* f; 

    // returns a pointer
    f = fopen("file.txt", "w"); // we specify the path and the mode: w, r, rb (read binary)
    // note that if the file does not exists it will create it

    // reading and writing to a text file
    
    int x; 
    fscanf(f, "%d", &x);
    int num = x + 10;
    fprintf(f, "%d", &num);

    // closing the file
    fclose(f); 

    
    char data[50]; 
    f = fopen("file2.txt", "r"); 
    
    while (fgets(data, 50, f) != NULL) {
        printf("%s", data);
    }

    fclose(f); 
   

    return 0;
}

void example2() {
    
    FILE* fptr;

    // Get the data to be written in file
    char data[50] = "Aman SUS";

    // Creating file using fopen()
    // with access mode "w"
    fptr = fopen("file.txt", "w");

    // Checking if the file is created
    if (fptr == NULL) 
        printf("The file is not opened.");
    else{
        printf("The file is now opened.\n");

        fputs(data, fptr);
        fputs("\n", fptr);

        // Closing the file using fclose()
        fclose(fptr);
        printf("Data successfully written in file file.txt\n");
        printf("The file is now closed.");
    }
}

void example3() {

    FILE* f; 

    // returns a pointer
    f = fopen("file.txt", "w"); // we specify the path and the mode: w, r, rb (read binary)
    // note that if the file does not exists it will create it
 
    int x;
    
    fscanf(f, "%d", &x);

    int num = x + 10;

    fprintf(f, "%d", &num);

    // closing the file
    fclose(f); 
}
```

### Binary Files

We can also write and read directly into/from binaries. 

```c
#include <stdio.h> 
#include <stdlib.h>

struct numbers {
    int n1, n2, n3;
};

int reading() {
    int n;
    struct numbers num;
    FILE* fptr;
    fptr = fopen("binaryFile.bin", "rb");
    
    // Read the data from binary 
    // file and print that data
    fread(&num, sizeof(struct numbers), 1, fptr);

    printf("n1: %d\tn2: %d\tn3: %d\n", num.n1, num.n2, num.n3);
    fclose(fptr);
    return 0;
}

int writing() {

    int n = 1 ;    
    FILE* fptr;
    fptr = fopen("binaryFile.bin", "wb");

    int flag = 0;
    
    struct numbers num;
    num.n1 = n;
    num.n2 = 5 * n;
    num.n3 = 5 * n + 1;
    
    flag = fwrite(&num, sizeof(struct numbers), 1, fptr);

    // Checking if the data is written.
    if (!flag) {
        printf("Write Operation Failure");
    } else {
        printf("Write Operation Successful");
    }
    
    fclose(fptr);
    return 0;
}
```


---

## Goto 

**goto** statements are used to directly jump to regions of memory inside a function. Note, in the 
context of `C`. 

```c 
void goto_example(int n) {

    if (n == 3) {
        goto print;
    } 

print:
    printf("AHHHH\n");
}
```
--- 

## Random Numbers

```c 
void random_numbers_example() {

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 5; ++i) {
        int num = rand() % 100; // Random number between 0 and 99
        printf("%d ", num);
    }
    printf("\n");
}
```

--- 

## Structs 

A struct is a contiguous block of memory which contaings enough memory for all members plus padding 
for addressing the word size. Mostly 64 bits or 8 bytes.

```c 
struct some {
    int a; 
    int b;
};
```
--- 

## Unions

Similar to struct it also a way of grouping data but it only allocates enough to hold the biggest member. It can only be 
in one of its variants at the time.

```c 
union some {
    int a; 
    char* b;
};
```
--- 

## Taged Unions 

This is mix of unions and structs used for representing *algraic data-types*. In the 
following exaple our struct result_alg can either hold a string or some generic data-type.

```c 
enum result {
    Some,
    Err,
};

typedef struct result_t {
    
    enum result res; 

    union {
        char* c;
        void* p;
    } value;
} result_t;

void demo_tagged_unions() {

    char abc[2] = {'a', 'b'};

    result_t r = {r.res = Some, r.value.c =abc};

    switch (r.res) {
        case Some: printf("Some content"); break;
        case Err: printf("Error"); break;
        default: printf("Invalid State");
    }

}
```

--- 


## Casting String-numbers to Numbers 

Multiple programming languages have defaults for converting string to numbers. The way this functionality works is by 
using the ASCII enconding which for the digits starts at 48. Therefore to convert a character number to a number the computer 
subtracts 48 from the binary code of the character. For multiple numbers with multiple digits a system for the positions has to be accounted.

--- 

## Memory Functions in C

`C` provides several functions which allow us to move/modify/copy alreay chuncks of memory.

```c 
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
    memcpy(dest, s, size); // copying the string
    memmove(dest, s, size); // moving the string to another location
    strncpy(dest_2, s, size); // copying the string to the other destination

}
```
---

## Header Files 

Header files `.h` are used to declare functions, structs etc. They are used to tell the compiler tool chain 
which functions are declared, but header files require also a concrete executable or object file of a `.c` file to work. 

### Strucure

```c
#ifndef SOME_NAME_H // this guard helps against infinite recursion
#define SOME_NAME_H

...

#endif
```

### Includes 

To include a header file of a local project we use `"header.h"` and to include one that is globally installed on the system 
`<header.h>`.

---

## The pthread Library 

In this section I will provide code snippets related to different uses cases of the concepts 
in multithreading using the `pthread` library 

### Passing Arguments to Threads and getting a Return-value 

```c 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

void* argument_and_return_routine(void* args) {
    
    int* res = malloc(sizeof(int));
    *res = *(int*)args + 1;

    return (void*)res;
}

int  main() {

    pthread_t t1;
    int val = 10;
    int* arg = &val; // this optional, we cal just pass &val into the create function

    int* res;

    pthread_create(&t1, NULL, &argument_and_return_routine, (void*)arg);

    pthread_join(t1,(void**)&res);

    free(res);
    return 0;

}
```

### Try_lock 

```c 
void* try_lock_routine(void* args) {
    
    if (pthread_mutex_trylock(&mutex) == 0) { // it does not guarantee the the lock is going to be got
        // Critical section
        pthread_mutex_unlock(&mutex);
    }
    
    printf("Hello, Mom");
}
```

### Barrier 

```c 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

int results[8];
int status[8] = {0};

pthread_barrier_t barrier;
pthread_barrier_t calculated_barrier;

void* rolldice(void* args) {
    
    int i = *(int*)args;

    while (1) {

        results[i] = (rand() % 6) + 1;
        pthread_barrier_wait(&barrier);
        pthread_barrier_wait(&calculated_barrier);

        if (status[i] == 1) {
            printf("Winner %d", i);
        } else {
            printf("Lost %d", i);
        }
    }
      
    free(args);
}

void barrier_example() {
    
    pthread_t threads[8];
    
    pthread_barrier_init(&barrier, NULL, 9);
    pthread_barrier_init(&calculated_barrier, NULL, 9);

    for (int i = 0; i < 8; i++) {
        int* a = malloc(sizeof(int)); 
        *a = i;
        if (pthread_create(&threads[i], NULL, &rolldice, (void*)a) != 0) {
            perror("SIKE");
        }
    }
    

    pthread_barrier_wait(&barrier);

    int max = 0;

    for (int i = 0; i < 8; i++) {
        if (results[i] > max) {
            max = results[i];
        }
    }

    for (int i = 0; i < 8; i++) {
        if (results[i] == max) {
            status[i] = 1;
        } else {
            status[i] = 0;
        }
    }

    pthread_barrier_wait(&calculated_barrier);
    
    for (int i = 0; i < 8; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Sike 2");
        }
    }

    pthread_barrier_destroy(&barrier);
    pthread_barrier_destroy(&calculated_barrier);
    return 0;
}


```

### Detached Threads 

```c 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

void* routine(void* args) { printf("Ding Dong!"); }

int main() {

    pthread_t t1;
    pthread_create(&t1, NULL, &routine, NULL);
    
    // They are used when it does not necessary for the main thread wait for the others threads
    // the thread is detached from the main thread and cleans its own resources
    pthread_detach(t1); // this puts the thread into a detached state
   
    // To create a detached thread we can do the following:
    pthread_t t2;
   
    // This is the way of creating thread attributes
    pthread_attr_t detached_t;
    pthread_attr_init(&detached_t);
    pthread_attr_setdetachstate(&detached_t, PTHREAD_CREATE_DETACHED);
    
    pthread_create(&t2, &detached_t, &routine, NULL);
    
    pthread_attr_destroy(&detached_t);
    pthread_exit(0);
}
```

### Recursive Mutexes

```c 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

// Static initializers 
pthread_mutex_t default_t = PTHREAD_MUTEX_INITIALIZER;

// Recursieve mutex

// They can be used to lock a mutex multiple for times. For example in a recursive context
pthread_mutex_t rec_mut;

int fuel = 0;

void* routine_2(void* args) {
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
   
    fuel += 1;
    
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);
}

int main() {

    pthread_t t1; 
    pthread_t t2; 
    
    pthread_mutexattr_t rec_attr; 
    pthread_mutexattr_init(&rec_attr); 
    pthread_mutexattr_settype(&rec_attr, PTHREAD_MUTEX_RECURSIVE);
    
    pthread_mutex_init(&rec_mut, &rec_attr);

    pthread_create(&t1, NULL, &routine_2, NULL); 
    pthread_create(&t2, NULL, &routine_2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutexattr_destroy(&rec_attr);
    pthread_mutex_destroy(&mutex);
    return 0;
}
```

### Binary Semaphores

```c 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

sem_t semaphore;

void* routine_3(void* args) {
    
    int sem_val;
    sem_wait(&semaphore);
    sem_getvalue(&semaphore, &sem_val);
    printf("Hola Mami %d\n", sem_val);
    sem_post(&semaphore); 
}


int main() {
    
    pthread_t t1; 
    pthread_t t2; 
    
    sem_init(&semaphore, 0, 1); // the 2nd argument is for the number of extra procceses and the 3th for the number of threads
                                                     // which are allowed to enter the critical section at the same time
    
    pthread_create(&t1, NULL, &routine_3, NULL); 
    pthread_create(&t2, NULL, &routine_3, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&semaphore);
    return 0;
}
```

### Producer Consumer Problen 

```c 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

#define THREAD_NUM 20

pthread_t thread_pool[THREAD_NUM];
pthread_mutex_t mutex;
pthread_cond_t cnd_full;
pthread_cond_t cnd_empty;

int buffer[10];
int count = 0;

void* producer(void* args) {
    while (1) {
        
        // Produce
        int x = rand() % 100;
        sleep(1);

        pthread_mutex_lock(&mutex);
        
        while (count == 10) {
            pthread_cond_wait(&cnd_full, &mutex);
        }

        buffer[count] = x;
        count++;
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cnd_empty); // this notifies only one thread 
        // pthread_cond_broadcase(&cnd); this is used to notify all threads
    }
}

void* consumer(void* args) {

    while (1) {
        
        pthread_mutex_lock(&mutex);
       
        while (count == 0) {
            pthread_cond_wait(&cnd_empty, &mutex);
        } 
   
        // Consume
        int y = buffer[count - 1];
        count--;

        printf("Got %d\n", y);
        sleep(1); 
        
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cnd_full);
    }

}

// With condition variables for the case only one producer and one consumer at a time
int main() {
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cnd_empty, NULL);
    pthread_cond_init(&cnd_full, NULL);

    for (int i = 0; i < THREAD_NUM; i++) {
        
        if (i % 2 == 0) {
            pthread_create(&thread_pool[i], NULL, &producer, NULL);
        } else {
            pthread_create(&thread_pool[i], NULL, &consumer, NULL);
        }
    }
 
    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(thread_pool[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    pthread_cond_destroy(&cnd_full);
    pthread_cond_destroy(&cnd_empty);
    pthread_mutex_destroy(&mutex);
    return 0;
}
```

### Thread Pool 

```c 
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <threads.h>

// Task representation
typedef struct Task {

    void* (*job)(void* arg);
    void* args;
    struct Task* next;

} Task;

// Queue structure for storing tasks
typedef struct Queue {

    Task* first;
    Task* last;
    int length;

} Queue;

Queue* queue_construtor() {

    Queue* queue = (Queue*)malloc(sizeof(Queue));
    
    queue->first = NULL;
    queue->last = NULL;
    queue->length = 0;

    return queue;
}

void queue_destructor(Queue* self) {
   
    Task* current = self->first;
    Task* temp;

    while (current) {
        temp = current;
        current = current->next;
        free(temp);
    }

}

// Create a new task
Task* task_constructor(void* args, void*(*job)(void* args)) {

    Task* task = (Task*)malloc(sizeof(Task));  
    task->job = job;
    task->args = args;
    task->next = NULL;

    return task;
}

Task* task_from(Task* other) {

    Task* task = (Task*)malloc(sizeof(Task));  
    task->job  = other->job;
    task->args = other->args;
    task->next = other->next;

    return task;
}

// Dequeue and execute a task (thread-safe)
void* dequeue(Queue* self) {

    Task* current = self->first;
    self->first = self->first->next;
   
    if (!self->first) {
        self->last = NULL;
    }
   
    self->length--;
    
    Task* res = task_from(current);
    
    free(current);

    return res;
}


typedef struct Thread_Pool {

    int thread_num;
    int active;
    struct Queue* tasks;
    pthread_t* workers;
    pthread_mutex_t mutex;
    pthread_cond_t condvar;

} Thread_Pool;

// Execute thread function
void* thread_job(void* args) {

    Thread_Pool* thread_pool = (Thread_Pool*)args;

    while (thread_pool->active == 1) {

        pthread_mutex_lock(&thread_pool->mutex);
        pthread_cond_wait(&thread_pool->condvar, &thread_pool->mutex);

        struct Task task = *(Task*)dequeue(thread_pool->tasks);
        
        pthread_mutex_unlock(&thread_pool->mutex);

        if (task.job) {
            task.job(task.args);
        }

    }

    return NULL;
}


// Enqueue a task into the queue (thread-safe)
void enqueue(Thread_Pool* thread_pool, Task* task) {
    
    pthread_mutex_lock(&thread_pool->mutex);

    if (!thread_pool->tasks->first) {
        thread_pool->tasks->first = task;
        thread_pool->tasks->last = task;
    } else {
        thread_pool->tasks->last->next = task;
        thread_pool->tasks->last = task;
    }
    
    thread_pool->tasks->length++;
    
    pthread_mutex_lock(&thread_pool->mutex);
    pthread_cond_signal(&thread_pool->condvar);
}

// Initialization of the thread pool and threads
Thread_Pool thread_pool_constructor(int thread_num) {
    
    Thread_Pool thread_pool;
    
    thread_pool.thread_num = thread_num; 
    thread_pool.active = 1;
    thread_pool.workers = (pthread_t*)malloc(thread_num * sizeof(pthread_t));
    
    for (int i = 0; i < thread_num; i++) {
        pthread_create(&thread_pool.workers[i], NULL,thread_job, NULL);
    }

    thread_pool.tasks = queue_construtor(); 
    thread_pool.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    thread_pool.condvar = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    return thread_pool;
}

void thread_pool_destructor(Thread_Pool* thread_pool) {
    
    thread_pool->active = 0; 

    for (int i = 0; i < thread_pool->thread_num; i++) {
        pthread_cond_signal(&thread_pool->condvar);
    }

    for (int i = 0; i < thread_pool->thread_num; i++) {
        pthread_join(thread_pool->workers[i], NULL);        
    }

    free(thread_pool->workers);
    queue_destructor(thread_pool->tasks);
}

int main() {
    
    printf("Hello Mom!");
    return 0;
}
```

--- 

## Processes

The `fork()` function is used to clone a process which means that the child process has a copy of all 
the variables and data of the parent proccess until that very point. After the fork() call all instructions 
going to be executed are the same. To actually get the child process or procceses to do something different we 
need to identify then via their id with the use of if-clauses.

If the id is 0, we are in the child process, else in the parent process

```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {

    int id1 = fork();
    int id2 = fork();

    if (id1 == 0) {

        if (id2 == 0) {
            printf("Hello from the child of the child of the parent process");
        } else {
            printf("Hello from the child1 of the parent process");
        }

    } else {
        
        if (id2 == 0) {
            printf("Hello from the child2 of the parent process processes");
        } else {
            printf("Hello from the parent processes");
        }
    }

    while (wait(NULL) != -1 || errno != ECHILD); // waiting for all processes to finish execution

    return 0;
}
```

### Pipes

**Pipes** are a way of comunication between processes. The function `pipe()` return two file descriptors to 
reference a region in memory to write and read data to (`int[2]`).

It is important to create the pipes before the forking for the file descriptors to be inherited by the 
other processes

Given a `pipe(fd)`, where `int fd[2]`. Then: 

- `fd[0]` is the read-end for the other process
- `fd[1]` is the write-end for the other process

It is important to note that pipes have a built in wait function. This means that when we read from a pipe 
we wait until data arrives. This is the reason why in the following code we do not need to specify waiting for the parent process 
when it wants the partial sum of the array computed by its child process.


```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {

    int arr[] = {1,2,3,4,5,6,7};
    int n = sizeof(arr) / sizeof(int);
    int sum = 0;
    int x;

    int fd[2];

    int i = 0; 

    if (pipe(fd) == -1) {
        perror("Could not open pipe");
    }

    int id = fork();

    if (id == -1) {
        perror("Could not instanciate a new process");
    }

    if (id == 0) {
        
        close(fd[0]);

        for (i = 0; i < n/2; i++) {
            sum += arr[i];
        }
        
        write(fd[1], &sum, sizeof(int));
        close(fd[1]);
        
    } else {

        close(fd[1]);
        for (i = n/2; i < n; i++) {
            sum += arr[i];
        }
        read(fd[0], &x, sizeof(int));
        close(fd[0]);

        sum += x;

        printf("Got the sum %d", sum);

        wait(NULL);
    }
 
    return 0;
}
```

### Named Pipes 

**Named pipes** ara files which we use to exchange information between processes just like normal pipes, but
we can given them a specific name to make them more identifible. 

```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {
    
    int fd;
    if (mkfifo("myfifo", 0777) == -1) { // parameters: name, permisions. 0777 means write and read by anybody
        if (errno != EEXIST) {
            printf("Could not create fifo file");
            return 1;
        }
    }
    
    int id = fork();
    
    if (id == 0) { 
        fd = open("myfifo", O_RDONLY); // waits until another process opens the fifo for writing
        // ...  
        close(fd); //closing the end do to processing being done
    } else {
        fd = open("myfifo", O_WRONLY); // this blocks execution until another process open the fifo for reading 
        // ...  
        close(fd); //closing the end do to processing being done
        printf("Terminating");
    }
  
    return 0;
}
```

### The exec family of functions

- 
- 
- 

```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {

    int omega;
   
    printf("Choose 1 or 0? ");
    scanf("%d",&omega);
   
    if(omega == 1){
       
        // Execute external processes
                // Without specifying environment variables and using PATH
        execlp("ping", "ping", "google.com", NULL); // Use PATH to find ping executable

        // With specifying environment variables and using PATH
        char* env[] = {
            "TEST=environment variables",
            NULL
        };
    };
    
}

```

### Redirecting Ouput 

To redirect the output to another file we have to use the functions dup() which creates a copy of an 
old file descriptor using the lowest number in the file descriptor table and dup2() which is similar but it accepts an specified fd.

```c
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {

    int id = fork();

    if (id == 0) {
        
        int file = open("example.txt", O_WRONLY | O_CREAT, 0777);

        if (file == -1) { return 2; }
        
        // int fd2 = dup(file); creates a copy of the file descriptor for the same file 
        
        // 1 is the file descriptor for stdout. We will redirect output to our file. Because the file descriptors are inherited by the child process 
        // the results of ping will be written in the file instead of being printed to the console
        int fd2 = dup2(file, 1); // replaces the specified file corresponding to a file descriptor by our own file(fifo)
        close(file); //closing the other file descriptor to our file

        int ret = execlp("ping", "ping", "-c", "3", "google.com"); 
        // another function for that is _execl(path, path, args...) or execvpe(prog, arr, env)

        if (ret == -1) {
            printf("We could not execute the other program due to the program not being found");
            return 1;
        }
        
        printf("This is not going to run due to execlp, replacling this code with the code of the other programm");

    } else {
        
        int wait_status;

        printf("Ma child is doing stuff\n");

        wait(&wait_status);

        if (WIFEXITED(wait_status)) {
            
            int status_code = WEXITSTATUS(wait_status);

            if (status_code != 0) {
                printf("Failure\n");
            }
        }
        
        printf("Terminating main\n");
    }
    return 0;
}
```

### Signals 

**Signals** are a way of inter-process communication. They are used to communicate a process an specific behaviour like terminating, halting, 
resuming etc. They are provided the OS to trigger interrupts directly.

```c
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int interrupt_count = 0;

// Signal handler function
void handle_sigint(int sig) {
    interrupt_count++;
    printf("\nCaught signal %d (SIGINT). Interrupt count: %d\n", sig, interrupt_count);

    if (interrupt_count >= 3) {
        printf("Too many interrupts. Exiting now.\n");
        exit(0);
    }
}

// Example Function for killing with a signal
void signal_example() {

    int id = fork();
    

    if (id == 0) {
        while (1) {
            printf("Infinite loop...\n");
        }
    } else {
        sleep(1);
        kill(id, SIGKILL);

        // we can also use SIGCONT and SIGSTOP to stop continue or resume a process
        wait(NULL);
    }
}

// custom handler
void handle_sigtstp(int sig) {
   printf("Stop not allowed\n"); 
}

// Prefered way of handling signals
void handling_signal() {
    
    struct sigaction sa;  // struct for hanlding signals
    sa.sa_handler = &handle_sigtstp;
    sa.sa_flags = SA_RESTART; 
    // using our own handler for the stop signal
    sigaction(SIGTSTP, &sa, NULL); // the 3thr paramerter is the the old signal handler
    // signal(SIGTSTP, &handle_sigtstp) alternative way, but its use is not encouraged

    int x;
    printf("Enter a number: ");
    scanf("%d", &x);
    printf("x = %d", x);
}

int x_g = 0;

void handle_siguser1(int sig) {
    if (x_g == 0) printf("Is a mutliple of 5\n");
}

int communication_between_proc() {

    int pid = fork();
    if (pid == -1) {
        perror("Sike");
    }

    if (pid == 0) {
        sleep(5);
        kill(getppid(), SIGUSR1); // siguser1 and 2 do nothing, but we can define a handler for them

    } else {
        struct sigaction sa; 
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_siguser1; 
        sigaction(SIGUSR1, &sa, NULL);

        printf("Guess the number:");
        scanf("%d", &x_g);

        printf("Got: %d", (x_g == 15)? 1 : 0);
    }

    return 1;
}

int main() {
    // Register signal handler
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl+C to send SIGINT. Program will exit after 3 interrupts.\n");

    // Infinite loop
    while (1) {
        printf("Working...\n");
        sleep(1);
    }

    return 0;
}
```

### Calling Fork multiple times and using multiple pipes

```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define PROCESS_NUM 10

int main() {

    int pids[PROCESS_NUM];  //arr of processes ids
    
    int pipes[PROCESS_NUM + 1][2]; //pipes 10 + 1 because of the parent process
    
    int i;
    
    // Creating pipes
    for (i = 0; i < PROCESS_NUM + 1; i++) {
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }
    
    // Creating different processes which are clones of the current process
    //
    // when creating processes in a loop we need to check for the id directly and if we do not want 
    // the child process to create other child process we need to return/break/goto after doing our task. Otherswise 
    // we will have an exponential number of processes
    for (i = 0; i < PROCESS_NUM; i++) {
        
        pids[i] = fork();

        // ----------------------- The cloned processes start executing from here ----------------          

        if (pids[i] == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        // If the id is not the id of the parent process then 
        // Take a value from one process increment its value and finally give it to the next process    
        if (pids[i] == 0) {

            int j;
           
            for (j = 0; j < PROCESS_NUM + 1; j++) {
                if (i != j) {
                    close(pipes[j][0]);         //close all read-pipes of the other processes except the current
                }
                if (i + 1 != j) {                   //the same but with the write except for the next process
                    close(pipes[j][1]);
                }
            }
            
            int x;

            if (read(pipes[i][0], &x, sizeof(int)) == -1) {    //read from the current process
                printf("Error at reading\n");
                return 3;
            }
            
            printf("(%d) Got %d\n", i, x);
            
            x++;
            
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) { //write to the next process
                printf("Error at writing\n");
                return 4;
            }
            
            printf("(%d) Sent %d\n", i, x);
            
            close(pipes[i][0]);      //close read end of the current process   
            close(pipes[i + 1][1]);  //close write end of the next process
            
            return 0;
        }
    }

    // Main process
    int j; 

    for (j = 0; j < PROCESS_NUM + 1; j++) {

        if (j != PROCESS_NUM) {
            close(pipes[j][0]); //closes all read pipes execept the last read
        }
        
        if (j != 0) {               //close all write pipes except for the parent process
            close(pipes[j][1]);
        }    int pid1 = fork();
    if (pid1 == -1) {
        printf("Error creating process");
        return 1;
    }
    if (pid1 == 0) {
        sleep(4);
        printf("Finished execution (%d)\n", getpid());
        return 0;   
    }

    int pid2 = fork();
    if (pid2 == -1) {
        printf("Error creating process");
        return 2;
    }
    if (pid2 == 0) {
        sleep(1);
        printf("Finished execution (%d)\n", getpid());
        return 0;   
    }

    int pid1_res = waitpid(-1, NULL, WNOHANG);
    printf("Waited for %d\n", pid1_res);
    int pid2_res = waitpid(pid2, NULL, WNOHANG);
    printf("Waited for %d\n", pid2_res);

    return 0;
    }
   
    // Procedure for sending the first value 

    int y = 5;

    printf("Main process sent %d\n", y);
    
    if (write(pipes[0][1], &y, sizeof(int)) == -1) { //write value to the next process
        printf("Error at writing\n");
        return 4;
    }
    
    // Read from the last process
    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) { //read from the last process
        printf("Error at reading\n");
        return 3;
    }

    printf("The final result is %d\n", y);
    
    // Clean Up
    close(pipes[0][1]); //close last pipes
    close(pipes[PROCESS_NUM][0]);
    
    //Wait for all processes to do their work. Wait is called after read because the parent 
    //process must first retrieve the result from the pipeline. Also, it has to signalize that it is 
    //expecting some result of the last process because other wise the last child processes will be never 
    //terminate properly because it has no way of sending the data

    for (i = 0; i < PROCESS_NUM; i++) { //wait for all processes
        wait(NULL); // wait returns the id of the processes you are waiting for
    }

    return 0;
}
```

### Emulating the Pipe opertor 

```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {
    
    int fd[2]; 
    pipe(fd);

    int id = fork();
    
    if (id == 0) {
        
        dup2(fd[1], STDOUT_FILENO);
        
        // Closing pipes as they are not needed
        close(fd[0]);
        close(fd[1]);
        
        // The output will be redirected to the copy of fd[1]
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
        
    }
    
    int id2 = fork(); 

    if (id2 == 0) {

        dup2(fd[0], STDIN_FILENO);

        // Closing pipes as they are not needed
        close(fd[0]);
        close(fd[1]);
       
        execlp("grep", "grep", "rtt", NULL);
    }

    close(fd[0]);
    close(fd[1]);
       
    
    waitpid(id, NULL, 0); //waiting for an specific process
    waitpid(id2, NULL, 0);

    return 0;
}
```

### Waitpid 

It is used to wait for a processes based on its id to change its state.

```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {

    int pid1 = fork();
    if (pid1 == -1) {
        printf("Error creating process");
        return 1;
    }
    if (pid1 == 0) {
        sleep(4);
        printf("Finished execution (%d)\n", getpid());
        return 0;   
    }

    int pid2 = fork();
    if (pid2 == -1) {
        printf("Error creating process");
        return 2;
    }
    if (pid2 == 0) {
        sleep(1);
        printf("Finished execution (%d)\n", getpid());
        return 0;   
    }

    int pid1_res = waitpid(pid1, NULL, 0); 
    printf("Waited for %d\n", pid1_res);
   
    int pid2_res = waitpid(pid2, NULL, 0);
    printf("Waited for %d\n", pid2_res);

    return 0;
}
```

A more complex example: 

```c 
#include <errno.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main() {

    int fd[3][2]; 

    for (int i = 0; i < 3; i++) {
        pipe(fd[i]);
    }
    
    int id1 = fork();
    
    if (id1 == 0) {
        
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        
        int x; 
        
        // read from the parent
        read(fd[0][0], &x, sizeof(int));
        
        x += 5;
        
        // write to the second child
        write(fd[1][1], &x, sizeof(int));
        
        close(fd[0][0]);
        close(fd[1][1]);
        return 0; 
    }

    int id2 = fork();

    if (id2 == 0) {

        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        
        int x; 
        
        // read from the child
        read(fd[1][0], &x, sizeof(int));
        
        x += 5;

        // write to the parent
        write(fd[2][1], &x, sizeof(int));
 
        close(fd[1][0]);
        close(fd[2][1]);

        return 0; 
    }
    
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    
    int x = 5; 
    int res; 
    
    // write to the child
    write(fd[0][1], &x, sizeof(int));
    
    // read from the child
    read(fd[2][0], &x, sizeof(int));

    printf("Res: %d", res);            
    
    close(fd[2][0]);
    close(fd[0][1]);

    waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);

    return 0;
}
```

---


