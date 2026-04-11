# The C Programming Language

My favorite language. This is a quick reference for `C` with examples and some explanations. I am
not trying to make a better reference; this is just for me. For a full reference, there are man-pages.

## Header Files in C

These are commonly used header files inside `C` projects

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

In the `C` programming language, numbers in bases other than 10 can be used by adding a prefix to the number's start.

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
    
    // Expanding the memory previously requested
    int* temp = (int*)realloc(arr, 10 * sizeof(int));

    if (temp != NULL) {
        arr = temp;
        for (int i = 5; i < 10; ++i) {
            arr[i] = i * 10;
        }
    }
    
    // Very important: freeing the memory after use
    free(arr);
}
```

---

## sizeof

The `size_t sizeof()` operator returns the size of an element in bytes.

- We use `sizeof(arr)/sizeof(arr[0])` to get the length of the array.

--- 

## offsetof

The `size_t offsetof(type, name_of_the_field)` operator return the starting byte of a member of a struct. 

```c 
typedef struct Example {
    int x;
    char y;
    char z;
} Example;

offsetof(Example, y);
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

    printf("Dereferencing double pointer %d", **dptr);
    return 0;
}
```

### Pointer Arithmetic

We sometimes need to move a pointer by a certain amount to access a contiguous block of memory.

```c

#include <stdio.h> 
#include <stdlib.h>

int main() {
    
    int* arr = (int*)malloc(sizeof(int) * 10); //allocating 40 bytes or 10 integers
    
    for (int i = 0; i < 10; i++) {
        *(arr + i) = i; //moving from our starting address always a multiple of 4 bytes
        //equivalent to arr[i]
    }
    
    free(arr);
    return 0;
}
```

### Arrays

Arrays in `C` decay to pointers, which means they are only pointers.

Here we create an array as a pointer.

```c
#include <stdio.h> 
#include <stdlib.h>

// decay to int*
void print_size1(int* arr) {

    printf("Size of the array in function with int*: %d", sizeof(arr));
}

// decay to int*
void print_size2(int arr[]) {

    printf("Size of the array in function with int[]: %d", sizeof(arr));
}

int main() {
    
    // this is equivalent to int arr[10]
    int* const arr = alloca(sizeof(int) * 10); // stack allocated 
    for (int i = 0; i < 10; i++) {
        *(arr + i) = i; 
    }

    printf("First element: %d", 1[arr]); // this is cursed but allowed: gets translated to *(1 + arr)
    printf("First element: %d", "hello"[1]); // this is cursed but allowed: similar
    
    print_size1(arr); // 8 bytes
    print_size2(arr); // 8 bytes
    printf("Size of the array in main: %d", sizeof(arr)); // 40

    return 0;
}
```

### Function Pointers

```c
// Function pointer example
void (*func_ptr)(int); // pointer to a function that takes an int and returns void
```

### Cursed Pointers

Here are some examples of "weird" pointers in C:

```c

//Really cursed pointers 
int (*x())[10]; //  x is a function that returns a pointer to an array of 10 integers 
int (*((*x)[]))(); // x is a pointer to an array of pointers to functions that return int
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

You can use functions like `strcpy`, `strcat`, `strlen`, and `strcmp` from `<string.h>` to work with these buffers.

#### Common Pitfalls

Always ensure there’s enough space for the null terminator `('\0')`.

Be careful with buffer overflows—C doesn’t do bounds checking.

Writing to string literals (like `char *s = "text";`) is undefined behavior.

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
    
    int len = strnlen(str, MAX_LEN); // number of chars plus \0 terminator 

    // Tokenization (destructive)!!!!
    
    char* piece = strtok(str, " "); // returns the string until the separator 
    // will return "A\0"

    piece = strtok(NULL, " "); // will take the previously used string but now without "A"
    
    printf("%s", piece);
    
    
    // Newer alternatives 
    char* original = strdup("AHHHHHH, ajbakjnvkjnc , ijajavja");
    char* rest = original;
    char* token;
    
    // Similar to the original but with only one call
    while ((token = strtok_r(rest, ",", &rest))) {
        printf("Token: %s", token);
    }
    
    // This one also returns separators separated by separators 
    while ((token = strsep(&original, ",")) != NULL) {
        printf("Token: %s", token);
    }    

    // Other string functions
    char dest[50];

    strncpy(dest, "Hello, World!", sizeof(dest) - 1); // Copy string

    strncat(dest, " How are you?", sizeof(dest) - strlen(dest) - 1); // Concatenate strings

    int cmp = strncmp(dest, "Hello, World! How are you?", strnlen(dest, sizeof(dest)) ); // Compare strings

    printf("String length: %zu\n", strlen(dest)); // Get string length  

    char* holi = "Sexo en el Oxxo";
    strcspn(holi, 'O'); //returns the first occurrence of the char in the string, else it returns the length of the string

}
```

### sizeof vs strlen 

- `sizeof()`: returns the size plus the null terminator.
- `strlen()`:  return the size of the string without the null terminator.

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

It is a binary pattern used to modify another binary pattern using bitwise operations.

--- 

## Branchless Programming 

Branching in not really a problem for modern CPUs, but for achiving maximal performance in constrain environments we can 
utilize bitwise operator and math to make simplify if-else expressions at the C or Assembly level. 

```c 
// Before
int max(int a, int b) {
    return a < b ? b : a;
}

// After 
int max_branchless(int a, int b) {
    return a*(a >= b) + b*(b > a); // the conditionals get evaluated to 1 or 0 and we use addition to concatenate
                                   // different cases
}
```

We can achive compound conditions with the help of bitwise operators.

**Note:** that the cases need to be completely disjoint to work and also this technique is bet suited for 
expressions, not multiple instructions-blocks. It also hurts readability, while compiler optimizations may achive the same result.

---

## Variadic Functions 

**Variadic functions** are special function which can take a variable number of argumets. 

```c 
#include <stdarg.h>

void variadic_function(int number_of_args, ...) {

    va_list args; 
    va_start(args, obligatory_arg);

    for (int i = 0; i < obligatory_arg; i++) {
        int val = va_arg(args, int);
        printf("%d\n", val);
    }

    va_end(args);
}
```

--- 


## Macros

Macros are code which is inserted inside the code before compilation.

### Parenthesis 

When a macro should produce a value i.e it is a expression we use parenthesis 
in the macro body. 

```c 
#define EXPRESSION((A)) ( (A) > 100 ? (A) : -1)
```

We also use parenthesis around the parameters to make it evaluate the parameter only one times. If 
we left out the parenthesis we would get for a call like:

```c 
int i = 0;
EXPRESSION(i++) ( (i++ > 100 ? i++ : -1)
//         1       2           3

```
                 `
### Compound Expressions 

In `C` we can create compound expressions; which are expressions with multiple statements 
and expressions inside them, by enclossing the body of the macro inside `{}`.

```c 
#define MAX_bet_INT((A),(B)) ({   \
    if ((A) > (B)) {              \
        return A;    \ 
    } else {                  \ 
        return B;    \ 
    }                         \
})
```

### Opeators 

- `#define name_of_macro(opt_param_1, opt_param2, ...)`: `#define` is used to define a macro.

- `#undef`: is used to undefine a macro.

-`\`: this allows us to define multiline macros. Example:

```c 
#define MAX_bet_INT(A,B) (   \
    if (A > B) {              \
        printf("%d\n", A);    \ 
    } else {                  \ 
        printf("%d\n", B);    \ 
    }                         \
)
```

- `#`: The stringinize operator allows us to use our parameters passed to a macros as literal strings. Example: 

```c 
#define p(name) printf("%s\n",#name);
```

- `##`: The token parsing operator enables the programmer to combine to tokes inside a macro together. 
Example:

```c 

#define token_parsing(n) printf("%d\n", token_##n);

int main () {
    int token_25 = 100;
    token_parsing(25) // this will be converted to printf("%d\n", token_25);
    return 0;
}
```

- `#pragma`: Used to call specific directives which can have from small to affect large effects on the struture of our code.

- `#error`: Is used to define our own compilation errors inside blocks of conditional compilation.

- `#if`: if-clause as directive. This and the following ones are not meanf for control-flow inside the program 
but more for conditional compilation. This is very powerful, because depending on the contents of our source code we can choose to 
compile or not compile certain sections.

- `#ifdef`: is used to check if a macro was already defined.

- `#else`: else-clasuse as directive.

- `#elif`: else-if-clasuse as directive.

- `#ifndef`: checks if a macro was not already defined.

- `#endif`: is used to end if-directives

- `defined`: is a directive for conditional compilation. It tells wherever a macro is defined or not.


### Types of Macros

- **Constants**:

```c
#define PI 3.14
```

- **Function like**:

```c
#define MIN(A, B) (                    \ 
            typeof(A) _a = (A);         \
            typeof(B) _b = (B);         \ 
            _a < _b ? _a : _b;          \
) 
```

- **Do-while-Pattern**: This a very niche case but, when we use 
macros some people still write a semicolon at the then for consistency even if 
they are not necessary. This can leaad to problems when we wan to skip curly braces inside 
if statements or loops. For that reason we can use a do-while-loop with `while(0)` to compress the whole 
statement plus the empty statement into one. 

```c 
#define foo(x) do {bar(x); bar(x + 1);} while(0)
void bar(int x) { printf("%d\n", x); }
```

- **X-Macros**: they are a special case of macros used for generating list-like structures of data 
or code.

Example with struct: 

```c 
// List structure
#define List_of_Titans \
    X(Attack)          \
    X(Armored)         \
    X(Female)          \
    X(Colosal)         \
    X(Beast)

// Actual X-defintion
struct Titans {
    #define X(name) char* name;
    List_of_Titans
    #undef X 
}; 

// The struct get initialized with each of fields begin char* titan_name

```

Example with enum: 

```c 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define List_of_Titans \
    X(Attack)          \
    X(Armored)         \
    X(Female)          \
    X(Colosal)         \
    X(Beast)

enum Titans { 
    #define X(name) name,
    List_of_Titans 
    #undef X
};

char* to_string(enum Titans c) {
    switch (c) {
        #define X(name) case name: return #name;
        List_of_Titans 
        #undef X
    }

    return NULL;
}

int main () { 
    enum Titans c = Colosus;
    printf("%s", to_string(c));
    return 0;
}
```


- **Variadic Macros**: Macros which a take a variadic number of argument by using `__VA_ARGS__`

```c 
#define eprintf(...) fprintf (stderr, __VA_ARGS__)

eprintf(1,2,3,4);

#define PRINTER(fstring, ...) fprintf(stdout, fstring, __VA_ARGS__) // old variant with the necessary format string

PRINTER("%d %d", 1, 2);


```


### Example 

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

    int port;                       // port for the OS to redirect the traffic
    int socketfd;                   // file descriptor for the socket
    int backlog;                    // number of simultaneous connections
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

## The volatile keyword

This keyword is used to prevent the compiler from optimizing certain variables.

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

## The static keyword

`static` has mainly two use cases: 

- A `static` variable inside a functions keeps its value between invocation.
- A `static` global variable is seen ony in the file in which its declared.

--- 

## Format Specifiers

We have the following format specifiers for the `printf` functions.

| Format Specifier | Type                            | Example                                    |
| ---------------- | ------------------------------- | ------------------------------------------ |
| `%d`             | Signed int                      | `int x = 10; printf("%d", x);`             |
| `%i`             | Signed int                      | `int x = 10; printf("%i", x);`             |
| `%u`             | Unsigned int                    | `unsigned int x = 10; printf("%u", x);`    |
| `%f`             | Float / Double                  | `float x = 3.14; printf("%f", x);`         |
| `%lf`            | Double (`scanf`)                | `double x; scanf("%lf", &x);`              |
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
| `%lld`           | long long int                   | `long long x; printf("%lld", x);`          |
| `%llu`           | Unsigned long long int          | `unsigned long long x; printf("%llu", x);` |
| `%hd`            | Short int                       | `short x; printf("%hd", x);`               |
| `%hu`            | Unsigned short int              | `unsigned short x; printf("%hu", x);`      |
| `%Lf`            | Long double                     | `long double x; printf("%Lf", x);`         |
| `%%`             | Literal `%`                     | `printf("%%");`                            |

---

## Reading and Writing to Files

We can open files using the function `FILE* fopen(char* path, char* mode)`. There is also the `int open(char* path, int flags)` system call,
whose flags are passed by OR-ing them bitwise and whose return value is the file descriptor of the target file. Note that `open` is slower due to the IO being unbuffered, which means that it is done byte by byte.

Table of opening modes for files with `fopen()`:

| Opening Mode | Explanation                                                                                                                                                                                                                                                                      |
| :----------: | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|     `r`      | Open an existing file for reading. The stream is positioned at the beginning of the file. The file must exist; otherwise, `fopen()` returns `NULL`.                                                                                                                              |
|     `rb`     | Open an existing file for reading in binary mode. The stream is positioned at the beginning of the file. The file must exist; otherwise, `fopen()` returns `NULL`.                                                                                                               |
|     `w`      | Open a file for writing. If the file exists, its contents are truncated to zero length. If it does not exist, a new file is created. The stream is positioned at the beginning of the file. Returns `NULL` on failure.                                                           |
|     `wb`     | Open a file for writing in binary mode. If the file exists, its contents are truncated to zero length. If it does not exist, a new file is created. The stream is positioned at the beginning of the file. Returns `NULL` on failure.                                            |
|     `a`      | Open a file for writing in append mode. All writes occur at the end of the file, regardless of the current file position. If the file does not exist, it is created. The initial file position for writing is at the end of the file. Returns `NULL` on failure.                 |
|     `ab`     | Open a file for writing in binary append mode. All writes occur at the end of the file. If the file does not exist, it is created. Returns `NULL` on failure.                                                                                                                    |
|     `r+`     | Open an existing file for both reading and writing. The stream is positioned at the beginning of the file. The file must exist; otherwise, `fopen()` returns `NULL`.                                                                                                             |
|    `rb+`     | Open an existing file for both reading and writing in binary mode. The stream is positioned at the beginning of the file. The file must exist; otherwise, `fopen()` returns `NULL`.                                                                                              |
|     `w+`     | Open a file for both reading and writing. If the file exists, its contents are truncated to zero length. If it does not exist, a new file is created. The stream is positioned at the beginning of the file. Returns `NULL` on failure.                                          |
|    `wb+`     | Open a file for both reading and writing in binary mode. If the file exists, its contents are truncated to zero length. If it does not exist, a new file is created. The stream is positioned at the beginning of the file. Returns `NULL` on failure.                           |
|     `a+`     | Open a file for reading and writing in append mode. Reading may occur at any position, but all writes occur at the end of the file. If the file does not exist, it is created. The initial file position for reading is at the beginning of the file. Returns `NULL` on failure. |
|    `ab+`     | Open a file for reading and writing in binary append mode. Reading may occur at any position, but all writes occur at the end of the file. If the file does not exist, it is created. Returns `NULL` on failure.                                                                 |

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

| Miscellaneous Functions                         | Description                                                                                         |
| ----------------------------------------------- | --------------------------------------------------------------------------------------------------- |
| `feof(FILE* stream)`                            | Returns 1 if after reading a file the comple file was read                                          |
| `ferror(FILE* stream)`                          | Returns 0 if no error occurred during the reading of the file                                       |
| `rewind(FILE* stream)`                          | Restores the file pointer to the start of the file                                                  |
| `fseek(FILE* stream, long offset, int wherece)` | Moves the position of the file pointer to an specific location                                      |
|                                                 | The whence tells us from where we are going to move in bytes: `SEEK_SET`, `SEEK_END` and `SEEK_CUR` |
| `ftell(FILE* stream)`                           | It returns the current position of the file pointer                                                 |
| `rename(char* path, char* new_name)`            | Renames the file                                                                                    |
| `remove(char* path)`                            | Deletes the file                                                                                    |

Example:

```c
#include <stdio.h> 
#include <stdlib.h>

int main() {
    
    // The FILE struct contains the pointer to the actual copy of the file loaded into 
    // RAM plus other meta data. What we use is a pointer to such a struct
    FILE* f; 

    // returns a pointer
    f = fopen("file.txt", "w"); // we specify the path and the mode: w, r, rb (read binary)
    // note that if the file does not exist it will create it
    fputc('1', f); // writing a single character
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
    // note that if the file does not exist it will create it
 
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

## GOTO

`goto` statements are used to directly jump to regions of memory inside a function. Note, in the
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

A struct is a contiguous block of memory which contains enough memory for all members plus padding
for addressing the word size. Mostly 64 bits or 8 bytes.

```c
struct some {
    int a; 
    int b;
};
```

### Struct Padding

The order of the members of the struct matter because the compiler will try to adjust the data in most optimal way
for fetching the data in the most efficient way possible. This means that for optimizing to read always
the processors **word-size** it will add padding between the members if necessary.

Example with word-size = 4 bytes = 32 bits

```c
// True size: 6 data bytes + 2 bytes of padding after the char c and int b
struct some_padded {
    char a;  // 1 byte
    char c; // 1 byte
    int b;  // 4 bytes 
};
```

---

## Unions

Similar to struct it also a way of grouping data, but it only allocates enough to hold the biggest member. It can only be
in one of its variants at the time.

```c
union some {
    int a; 
    char* b;
};
```

---

## Tagged Unions

This is mix of unions and structs used for representing *algebraic data-types*. In the
following example our struct `result_alg` can either hold a string or some generic data-type.

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
using the ASCII encoding which for the digits starts at 48. Therefore, to convert a character number to a number the computer
subtracts 48 from the binary code of the character. For multiple numbers with multiple digits a system for the positions has to be accounted.

---

## Memory Functions in C

`C` provides several functions which allow us to move/modify/copy chunks of memory.

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

### Structure

```c
#ifndef SOME_NAME_H // this guard helps against infinite recursion
#define SOME_NAME_H

...

#endif
```

### Includes

To include a header file of a local project we use `"header.h"`, and to include one that is globally installed on the system
we use `<header.h>`.

---

## The pthread Library

In this section I will provide code snippets related to different use cases of the concepts
in multithreading using the `pthread` library.

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
    int* arg = &val; // this is optional, we can just pass &val into the create function

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
    
    if (pthread_mutex_trylock(&mutex) == 0) { // it does not guarantee that the lock is going to be acquired
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
    
    // They are used when it is not necessary for the main thread to wait for the other threads
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

// They can be used to lock a mutex multiple times. For example, in a recursive context
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
    
    sem_init(&semaphore, 0, 1); // the 2nd argument is for the number of extra processes and the 3rd for the number of threads
                                                     // which are allowed to enter the critical section at the same time
    
    pthread_create(&t1, NULL, &routine_3, NULL); 
    pthread_create(&t2, NULL, &routine_3, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&semaphore);
    return 0;
}
```

### Producer Consumer Problem

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
        // pthread_cond_broadcast(&cnd); this is used to notify all threads
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


Queue* queue_constructor() {

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
    
    pthread_cond_signal(&thread_pool->condvar);
    pthread_mutex_unlock(&thread_pool->mutex);
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

    thread_pool.tasks = queue_constructor(); 
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

The `fork()` function is used to clone a process, which means that the child process has a copy of all
the variables and data of the parent process until that very point. After the fork() call, all instructions
going to be executed are the same. To actually get the child process or processes to do something different, we
need to identify them via their ID with the use of if-clauses.

If the ID is 0, we are in the child process; else, we are in the parent process.

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

**Pipes** are a way of communication between processes. The function `pipe()` returns two file descriptors to
reference a region in memory to write and read data to (`int[2]`).

It is important to create the pipes before forking for the file descriptors to be inherited by the
other processes.

Given a `pipe(fd)`, where `int fd[2]`. Then:

- `fd[0]` is the read-end for the other process
- `fd[1]` is the write-end for the other process

It is important to note that pipes have a built-in wait function. This means that when we read from a pipe
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
        perror("Could not instantiate a new process");
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

**Named pipes** are files which we use to exchange information between processes just like normal pipes, but
we can give them a specific name to make them more identifiable.

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

This family of function replaces the current process image with a new process image. 
The initial argument for these fuctions is the path of the file to be executed.

By all of the second and eventually third arguments the arrays or variadic list have to be `NULL` terminated. 

**Firs argument**: path to the other executable. 

**Second argument**: NULL-terminated array or variadic list of arguments for the new program.

**Third arugment**: NULL-terminated array or variadic list of environment variables in the form of `KEY=VALUE` pair strings. 

- `execl(const char *pathname, const char *arg, ..., (char *) NULL)`

- `execlp(const char *file, const char *arg, ... , (char *) NULL)`

- `execle(const char *pathname, const char *arg, ... , (char *) NULL, char *const envp[])`

- `execv(const char *pathname, char *const argv[])`

- `execvp(const char *file, char *const argv[])`

- `execvpe(const char *file, char *const argv[], char *const envp[])`

Example: 

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

### Redirecting Output

To redirect the output to another file, we have to use the function `dup()`, which creates a copy of an
old file descriptor using the lowest number in the file descriptor table, and dup2(), which is similar but accepts a specified **fd**.

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
        
        printf("This is not going to run due to execlp, replacing this code with the code of the other program");

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

**Signals** are a way of inter-process communication. They are used to communicating to a process a specific behavior like terminating, halting,
resuming, etc. They are provided by the OS to trigger interrupts directly.

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
    // signal(SIGTSTP, &handle_sigtstp) is an alternative way, but its use is not encouraged

    int x;
    printf("Enter a number: ");
    scanf("%d", &x);
    printf("x = %d", x);
}

int x_g = 0;

void handle_siguser1(int sig) {
    if (x_g == 0) printf("Is a multiple of 5\n");
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

### Emulating the Pipe operator

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

It is used to wait for a processes based on its ID to change its state.

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

    printf("Res: %d", x);            
    
    close(fd[2][0]);
    close(fd[0][1]);

    waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);

    return 0;
}
```

---

## Pragmas

Pragmas are a kind of preprocessor directive used for giving the compiler more information.
They are operating system specific, i.e., system call specific.

Example:

```c

// Init will be called at the start of the program 
// Term will be called after the termination 

#pragma startup init 
#pragma exit term 

void __attribute__((constructor))init() { 
    printf("Init\n");
}

void __attribute__((destructor))term() { 
    printf("Terminating\n");
}

int main() {

    return 0;
}

```

We can also use pragmas to suppress some warnings:

```c
#pragma warn -rvl // No return value  
#pragma warn -par // Parameter not used 
#pragma warn -rch // Unreachable code
```

---

## OpenMP

It is a standard for parallel programming for scientific computing at the thread level.

In this example the text will be printed number_of_cores_in_machine times:

```c
#include <stdio.h>
#include <omp.h>

int main() {
    int x = 6; 
    omp_set_num_threads(x); // is used to overwrite the default number of threads 
    #pragma omp parallel
    {
        printf("Hello, World from thread %d!\n", omp_get_thread_num());
    }
    return 0;
}
```

### How to Compile

We need to specify that we will use `openmp`.

```bash
gcc -fopenmp -o PP PP.c
```

### Loop Parallelization

Parallelization for for-loops.

**Manual**:

```c 
void example_loop_parallelization(int iterations) {
    
    int i = 0;

    #pragma omp parallel firstprivate(i) 
    {
        int id = omp_get_thread_num();
        int thread_num = omp_get_num_threads();

        for (i = id; i < iterations; i += thread_num) {
            printf("Iteration %d by thread %d \n", i, id);
        }
    }
}
```

**Automatic**:

```c
#pragma omp parallel for
for (int i=0; i<10; i++) {
// ...
}
```

Important note `omp for` is to be used inside a parallel region because it does not spawn threads, unlike `omp parallel for` which 
creates a parallel region and also shares the work accross threads.

#### When are Loops Safe to Parallelized 

We can parallelize nested loops when there are no inner dependencies for the indexes inside the loops 

- **Nested Loop with no Dependencies**

```c 
#pragma omp parallel for
for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        A[i][j] = B[i][j] + 1; // i and j only dependt on themselfs without the previous being important
    }
}
```

- **Inner loop parallelization but not the outer**

```c
void selectionSort(int arr[], int n) {
    
    // Outher loop has a dependency can not be parallelized
    for (int i = 0; i < n - 1; i++) {

        int min_idx = i; // dependency in the inner loop
    
        // No dependencies
        #pragma omp parallel for 
        for (int j = i + 1; j < n; j++) { // searching for the index of the smalles element
            if (arr[j] < arr[min_idx]) {
                #pragma omp critical
                min_idx = j; // even after found it get not changed
            }
        }
    
    int temp = arr[i];
    arr[i] = arr[min_idx];
    arr[min_idx] = temp;
    }
}
```

- **Double Buffering**

```c 

// Unsafe to partial dependencies
for (int t = 0; t < T; t++) {
    for (int i = 1; i < N-1; i++) {
        A[i] = (A[i-1] + A[i] + A[i+1]) / 3;
    }
}

// Writes to B swaps with A
for (int t = 0; t < T; t++) {
    #pragma omp parallel for
    for (int i = 1; i < N-1; i++) {
        B[i] = (A[i-1] + A[i] + A[i+1]) / 3; // preserves the structure of A
    }
    swap(A, B);
}
```

#### Non-safe Parallelization

- **Previous Index Dependency**:

```c 
for (int i = 1; i < N; i++) {
    A[i] = A[i-1] + 1;
}
```


### Regions in OpenMP

- **Parallel Region**: The block under `#pragma omp parallel`.

- **Worksharing Region**: These are parts of the code inside parallel regions.

- **Single Region**: Only one thread executes the code.

- **Sections Region**: Each thread executes one of the regions. If there are fewer threads than sections
then threads must work on multiple sections. By more threads than sections, then some threads will be without work.

Example:

```c
#pragma omp parallel
{
    // Code here is executed by all threads
    printf("Hello Mom\n"); 

    // Only one thread
    #pragma omp single
    {
    // Worksharing-Region 1
    }

    #pragma omp for
    for (int i=0; i<n; i++) {
        // Worksharing-Region 2
    }
    
    #pragma omp sections
    {
        #pragma omp section
        {
            printf("I am section 1\n");
        }
        #pragma omp section
        {
            printf("I am section 2\n");
        }
    }
}
```

By default, threads wait at the end of the worksharing-regions.

Example 2:

```c
int main() {
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i=0; i<10; i++) {
        printf("i=%d -> Thread Nr. %d\n", i, omp_get_thread_num());
    }
    return 0;
}
```

### Regulating Access to Variables in Threads

Variables inside a parallel region exists **separetly** for each thread, but
we can limit their scope using specific directives.

- Disabling access to variables outside the parallel region.

```c
#pragma omp parallel default(none)
```

We can also declare shared variables and also private variables for each of threads.
 
- `shared(var)`: Shared variable across the threads. Changes are visible to everyone.

- `private(var)`: Each thread gets its own separate copy. The variable original value is not copied and changes 
do not affect the original variable.

- `firstprivate(var)`: like private but the original value is copied. 

- `lastprivate(var)`: only used for workshareing constructs with loops. Each thread gets its own copy but after the loop 
the last value is copied to the original variable.

Example:

```c
#include <stdio.h>
#include <omp.h>

int main() {

    int sum = 0;
    omp_set_num_threads(4);
    #pragma omp parallel default(none) firstprivate(sum)
    {
     #pragma omp for
     for (int i=0; i<100000; i++) {
         sum++;
     }
     printf("Thread %d: Number of iterations: %d\n", omp_get_thread_num(), sum);
 }
    return 0;
}
```

### Reductions

OpenMP support reduction operations.

Supported operations;

- `+:var`
- `*:var`
- `max:var`
- `min:var`

Also, **all** the bitwise operations are supported.

Example:

```c
#include <stdio.h>
#include <omp.h>

int main() {

    int sum = 0;
    omp_set_num_threads(4);

    #pragma omp parallel default(none) reduction(+:sum)
    {
        #pragma omp for
        for (int i=0; i<100000; i++) {
            sum++;
        }
    }
 
    //starting from here is sum=100000
    printf("Thread %d: Number of iterations: %d\n", omp_get_thread_num(), sum);
    return 0;
}
```

### Synchronization Mechanisms

Mechanisms to prevent race conditions

#### Reductions as Synchronization Mechanism

Reductions in general.

Example:

```c
#include <stdio.h>
#include <omp.h>

int main() {

    int sum = 0;
    omp_set_num_threads(4);

    #pragma omp parallel default(none) reduction(+:sum)
    {
     #pragma omp for
     for (int i=0; i<100000; i++) {
         sum++;
     }
 }
 
    printf("Thread %d: Number of iterations: %d\n", omp_get_thread_num(), sum);
    return 0;
}
```

#### Critical

With this we can mark the part of the code to be synchronized.

Example:

```c

#pragma omp parallel for default(none) shared(x)
for (int i=0; i<1000000; i++) {
 #pragma omp critical
 {
  x++;
 }
}
```

#### Atomic

While useful, only one basic operation can be inside an atomic block.

Supported: `++, --,  +=, *=, -=, /=, &=, ^=, |=, <<=, >>=`

Example:

```c
#pragma omp parallel for default(none) shared(x)
for (int i=0; i<1000000; i++) {
 #pragma omp atomic
 x++;  //Beispiel fuehrt zu Serialisierung
}
```

#### Barriers

By default, at the end of each worksharing-region there is **always** a barrier.

We can declare them with:

```c
#pragma omp barrier
```

or disable them with:

```c
#pragma omp for nowait
```

#### Locks

This is just a mutex

```c

omp_lock_t my_lock;

omp_init_lock(&my_lock);

omp_set_lock(&my_lock);
// critical operations 
omp_unset_lock(&my_lock);

omp_destroy_lock(&my_lock);
```

#### Single and Master

One refers to a block which is only executed by one thread and the other to a block only performed by
the main thread.

Master is no worksharing-region; therefore it has no barrier.

```c
#pragma omp master
{
// .......
}

#pragma omp single
{
// .......
}
```

#### Ordered

This construct ensures that inside a loop the execution happens in order

```c
#pragma omp for
for (int i = 0; i < n; i++) {
    #pragma omp ordered
    {
        // Code block, executed in the order of the loop iteration
    }
}
```

#### General Example

The goal is to count to 4 million.

Version 1:

```c
#include <stdio.h>
#include <omp.h>

int main() {
 omp_set_num_threads(4);
 int g = 0;
 int result = 0;
 #pragma omp parallel default(none) firstprivate(g) shared(result)
 {
  #pragma omp for 
  for (int i=0; i<1000000; i++) {
   g+=1;
  }
  #pragma omp atomic
  result += g;
 }
 printf("%d\n", result);
 return 0;
}
```

Version 2:

```c
#include <stdio.h>
#include <omp.h>

int main() {
 
    omp_set_num_threads(4);
    
    int f[1] = {0};
    int* ff = f;
    int result = 0;

    #pragma omp parallel default(none) shared(result) firstprivate(ff) 
 {
  #pragma omp for 
  for (int i=0; i<1000000; i++) {
   *ff+=1;
  }
  #pragma omp atomic
  result += *ff;
 }

    printf("%d\n", result);
 return 0;
}
```

#### Complex Example

```c
void matrix_vector_multiplication() {
    const int size = 10; 

    double a[size][size];
    double b[size]; 
    double c[size];

    double total = 0.0;
    
    #pragma omp parallel 
    {
        
        #pragma omp for
        for (int i = 0; i< size; i++) {

            for (int j = 0; j < size; j++) {
                a[i][j] = (j + 1) * 1.0;
            }

            b[i] = 1.0 + (i + 1);
            c[i] = 0.0;
        }
    
        #pragma omp for reduction(+: total)
        for (int i = 0; i < size; i++) {

            for (int j = 0; j < size; j++) {
                c[i] += a[i][j] * b[j];
            }
            
            total += c[i];
        }
    }

    printf("\nMatrix-vector total - sum of all c[] = %.2f\n\n", total);
}

void random_array() {

    int arr[1000000];
    int control = 0;
    int count_100s = 0;

    #pragma omp parallel for
    for (int i = 0; i < 1000000; i++) {
        unsigned int seed = time(NULL) ^ omp_get_thread_num() ^ clock();
        arr[i] = rand_r(&seed) % 100 + 1;
    }

    #pragma omp parallel for reduction(+:count_100s)
    for (int i = 0; i < 1000000; i++) {
        if (arr[i] == 100)
            count_100s += 1;
    }

    for (int i = 0; i < 1000000; i++) {
        if (arr[i] == 100)
            control += 1;
    }

    printf("Number of 100s %d\n", count_100s);
    printf("Number of 100s control %d\n", control);
}
```

### How Is Work inside Loops Divided

Each thread gets **blocks/chunks** of iterations to work with. These are mostly assigned using 

#### Schedule

We have the `schedule(behavior, chunk_size)` directive to determine how many threads are going to
work on the loop.

**Chunk size**: It is the number of iterations divided by the number of threads.

**Behaviors**:

- `static`: By n threads the indices will be split into blocks of more or less equal size across the threads.

```c
#pragma omp parallel for schedule(static, 10)
for (int i=0; i<1000; i++) {
  printf("Thread Nr. %d, i=%d\n", omp_get_thread_num(), i);
}
```

Each block consists of 10 iterations.

- `dynamic`: It is similar to static, but if a thread is already done it can proceed to take another block.
It is useful if the work divided across the blocks is not equally time-consuming.

```c
#pragma omp for schedule(dynamic, 10)
for (int i=0; i<1000; i++) {
  // ...
}
```

- `auto`: No one uses auto.

- `guided`: Makes the blocks first big and then small at the end.

```c
// minimal block size 10
#pragma omp for schedule(guided, 10)
for (int i=0; i<1000; i++) {
  // ...
}
```

### Nested Loops

When we have nested loops which obey the following conditions:

- Both loop heads happen after the other.

- The boundary of the inner loop does not depend on the outer loop.

Then we can use the `collapse(2)` directive to allow parallelism with nested loops.

Example:

```c
#pragma omp parallel for collapse(2)
for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
         printf("Iteration (%d/%d) run by thread %d\n",
             i, j, omp_get_thread_num());
    }
}
```

### How to Minimize Overhead

- Minimize the number of parallel regions.
- Combine parallel regions into one if possible.
- If possible transform nested loop into regular loops and parallelize them.
- Limit the use of critical sections
- Use primitive locking mechanisms to reduce overhead.

### Miscellaneous Functions

- `omp_set_num_threads`: Set number of threads to use.
- `omp_get_num_threads`: Return the current number of threads.
- `omp_get_thread_num`: Return the current thread ID relative to the main thread.

### Environment Variables

- `OMP_SCHEDULE`: Changes the behavior of the Schedule clause if not specified.

- `OMP_NUM_THREADS`: Sets the maximum number of threads in the parallel scope unless they are defined by
`omp_set_num_threads` or `num_threads` overridden.

- `OMP_DYNAMIC`: Specifies whether the OpenMP runtime can adjust the number of threads
in a parallel scope.

- `OMP_NESTED`: Specifies whether nested concurrency is enabled unless nested concurrency is enabled or
disabled with `omp_set_nested`.

### Manual Worksharing

We can also not use worksharing-constructs a still get parallel work. For that we can use
the thread id.

Example 1:

```c
#include <omp.h>
#include <stdio.h>

int main() {
 omp_set_num_threads(2);
 
 #pragma omp parallel
 {
  int id = omp_get_thread_num();
  switch (id) {
   case 0:
    printf("I am the master thread\n");
    break;
   case 1:
    printf("I am the worker thread\n");
    break;
  }
 }
 return 0;
}
```

Example 2:

```c
#include <omp.h>
#include <stdio.h>

int main() {
 omp_set_num_threads(3);
 
 #pragma omp parallel
 {
  int id = omp_get_thread_num();
  int n = omp_get_num_threads();
     
        // Each thread will execute the loop starting from its own id
  for (int i=id; i<10; i+=n) {
   printf("Thread: %d: Iteration: %d\n", id, i);
  }
 }
}
```

### Master Worker Schema

There is one **master thread** which can instantiate multiple **worker threads**
to do certain work. This is the case for the well known **thread pool**.

The synchronization points are

- The master gives a worker the data and task
- The worker gives the master the result

#### Thread-Pool in Open MP

It looks weird but create one by creating a single region in between a parallel region.

```c
#pragma omp parallel 
#pragma omp single
```

The parallel region is needed for initializing the multithreading, and the single region will put all
threads to sleep except for the master thread. All other threads form the thread pool.

To initialize a worker we use the following construct which creates a task.

```c
#pragma omp task
{
 job();
}
```

To get the result from a task we need a variable which will be used to store it.

```c
double result = 0;

#pragma omp task shared(result)
{
 result = job();
}

// ...
# pragma omp taskwait
printf("%f\n", result);
```

With `taskwait` we tell the master-thread to wait until all workers are done.

Example:

```c
int getFactorCount(int num) {
 int count = 0;
 return count;
}

int asyncFactorCount(int num) {
 int result = 0;
 
 #pragma omp parallel default(none) shared(num, result) // vars for the results
 #pragma omp single
 {
  #pragma omp task default(none) shared(result) firstprivate(num)
  {
   result = getFactorCount(num);
  }
  
        // Waiting for the worker
    #pragma omp taskwait   
 }
 return result;
}
```

#### Nested Loops and Tasks

There are two main ways to correctly handle tasks inside nested loops: a simpler and non-flexible one and
a complicated and flexible one:

- **Variant 1**: Initiating the task inside the second loop.

```c
#pragma omp parallel
#pragma omp single 
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<i; j++) {
            #pragma omp task firstprivate(i, j)
            {
                printf("Iteration (%d/%d) runs on thread %d\n",
                       i, j, omp_get_thread_num());
            }
        }
    }
}
```

- **Variant 2**: Tasks are initialized in 2 steps.

```c
#pragma omp parallel
#pragma omp single
{
    for (int i=0; i<4; i++) {
        #pragma omp task firstprivate(i) 
        {
            for (int j=0; j<i; j++) {
                #pragma omp task firstprivate(j)
                {
                    printf("Iteration (%d/%d) runs on thread %d\n",
                           i, j, omp_get_thread_num());
                }
            }
        }
    }
}
```

This second is more flexible because the master thread only waits for the  
task created in the outer loop. If we want to also wait, we would need to explicitly
specify that we want to wait for the inner tasks.

```c
#pragma omp parallel
#pragma omp single
for (int i=0; i<4; i++) {
    #pragma omp task firstprivate(i)
    {
        for (int j=0; j<i; j++) {
            #pragma omp task firstprivate(j)
            {
                printf("Iteration (%d/%d) runs on thread %d\n",
                       i, j, omp_get_thread_num());
            }
        }
        #pragma omp taskwait
    }
}
```

#### Recursive Tasks

The parallel version of the Fibonacci code first creates a thread pool and then
proceeds to create a task for the call of `_fibonacci(n - 1)` before proceeding to wait for the
task to finish execution.

```c

int _fibonacci(int n) {
    if (n<=2) {
        return 1;
    }
    
    int x, y;
    #pragma omp task shared(n, x)
    {
        x = _fibonacci(n-1);
    }
    
    y = _fibonacci(n-2);
    #pragma omp taskwait
    return x+y;
}

int fibonacci(int n) {
    int result;
    #pragma omp parallel default(none) shared(n, result)
    #pragma omp single
    {
        result = _fibonacci(n);
    }
    
    return result;
}
```

They use the same work-stealing technique like in Java in case there are no more free working
threads but open tasks.

#### Framework 


- **Master**: We use parallel and single for the initial call.

```c 
#pragma omp parallel default(none) shared(n, result)
    #pragma omp single
    {
        result = _rec(n);
    }
```

- **Worker**: We assign the return value to a variable an create the task.

```c 
#pragma omp task shared(n, x)
{
    x = _rec(n-1);
}

#pragma omp taskwait
```

Example: 

```c 
void permute_parallel_helper(int num, int cnt, int first, int last) {

    if (cnt==0) {
        printf("(Thread %d) %d\n", omp_get_thread_num(), num);
        return;
    }
    num = num*10;

    for (int i = first; i <= last; i++) {
        #pragma omp task default(none) shared(num, cnt, first, last) firstprivate(i)
        {
            permute_parallel_helper(num+i, cnt-1, first, last);
        }
    }
    #pragma omp taskwait
    }
    
void permute_parallel(int cnt, int first, int last) {
    #pragma omp parallel default(none) shared(cnt, first, last)
    {
        #pragma omp single
        {
        permute_parallel_helper(0, cnt, first, last);
        }
    }
}
```
---

## MPI

**MPI** is a specification for libraries designed for parallel computing in the area of computer clusters.
The implementation also depends on the distributor.

Example program:

```c
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int procRank,procCount;

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&procCount);
    MPI_Comm_rank(MPI_COMM_WORLD,&procRank);
 
    printf("Hello World from process [%d]/[%d]\n",procRank,procCount);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
```

**Important** notes:

- MPI functions always return 0 or some other number. This means that because they only
return their status code to get some value out of the function we pass a pointer to a variable to store the
value.

- To setup te enviroment the following is needed:
    - `sudo [package_manager] install openmpi openmi-devel environment-modules`
    - `module load mpi/openmpi-x86_64` or we need to export the env-var manually with `export PATH=/usr/lib64/openmpi/bin:$PATH` and 
    `export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib:$LD_LIBRARY_PATH` 

- The to run and compile we use: 
    - `mpicc opts file`
    - `mpicc -np <number of processes> file`

### How To Compile And Execute An MPI Program

- **Compilation**

```bash
mpiicc -std=c99 HelloWorld.c -o HelloWorld
```

We can adjust the c version among other parameters.

- **Execution**

```c
mpiiexec -np 3 ./HelloWorld
```

When executing, we can, via the `-np` followed by a number, define the number of processes to run our program.

### MPI Init And Finalize

`MPI_Init(&argc, &argv)` must always be the first function to call in our program and
`MPI_Finalize()` the last one before the `return 0` of the main function.

### Get Process Count and Id

The following functions return the number of processes and also the id/rank of the current process.

```c
MPI_Comm_size(MPI_COMM_WORLD,&procCount);
MPI_Comm_rank(MPI_COMM_WORLD,&procRank); 
```

### Communicators

**Communicators** are descriptors for groups of processes.

- `MPI_COMM_WORLD`: refers to the group of all processes.
- `MPI_COMM_SELF`: contains only the current processes.
- `MPI_COMM_NULL`: refers 0 processes.

### Inter-Process-Communication

Like with Unix processes we have parent and child processes, but this time
the process with the id of **0** is the parent while the one with the id of **1** is the child
process.

Example:

```c
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
 int procRank,procCount;

 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&procCount);
 MPI_Comm_rank(MPI_COMM_WORLD,&procRank);
    
    // Parent
 if (procRank == 0) {
  
        int message = 42;
        int tagSend = 0;
  MPI_Send(&message, 1, MPI_INT, 1, tagSend, MPI_COMM_WORLD);
    
    // Child
    } else if (procRank == 1) {
  
        int message = 0;    
  int tagSend = 0;
  MPI_Recv(&message, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  printf("Recv. Message: %i\n",message);
 }

 MPI_Finalize();
 return EXIT_SUCCESS;
}
```

#### Sending

This  routine  will  block  until  the message is sent to the destination. For an in-depth explanation of the semantics of the standard-mode send, refer to the MPI
Standard.

```c
MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
```

1. `buf`: The address of the source.
2. `count`: How many size of primitive datatype.
3. `datatype`The data type.
4. `dest`: ID of the receiver.
5. `tag`: The tag is a free int-value to mark a message. When receiving, the first message with a matching tag is received.
6. `comm`: Group of processes.

It is mostly **blocking** which means that until the message is not send it can not proceed.

#### Receiving

This basic receive operation, MPI_Recv, is blocking: it returns only after the receive buffer contains the newly received message. A receive can complete before the
matching send has completed (of course, it can complete only after the matching send has started).

```c
MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
```

1. `buf`: The address of the destination.
2. `count`: How many chunks.
3. `datatype`: The data type.
4. `source`: ID of the sender. We can also use `MPI_ANY_SOURCE` to just get the next message in the queue.
5. `tag`: The tag is a free int-value to mark a message. When receiving, the first message with a matching tag is received. If the tag is not important, we can use `MPI_ANY_TAG`.
6. `comm`: Group of processes.
7. `status`: Status of the transaction.

It is mostly **blocking** which means that until the message is not send it can not proceed.

Example:

```c

MPI_Status status;

MPI_Recv(&message, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD, &status);

printf("Source of the message: %d\n", status.MPI_SOURCE);
printf("Tag of the message: %d\n", status.MPI_TAG);

int count = 0;
MPI_Get_count(&status, MPI_INT, &count);
printf("Size of the message: %d\n", count);
```

### Receiving A String

We can use the status to send metadata about the message alongside
the `MPI_Probe(sender, tag, communicator, status)` function to just get the status
and with it the length of the package.

**Structure**:

```c

// All inside the processes which do not know about the data!!!

MPI_Status status;

// Receive the status
MPI_Probe(0, tag, MPI_COMM_WORLD, &status);

// Extract the length
int size = 0;
MPI_Get_count(&status, MPI_CHAR, &size);

// Allocate Space
char* buf = (char*) malloc(size * sizeof(char));

// Receive the message
MPI_Recv(buf, size, MPI_CHAR, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
```

Real example:

```C 
void example3() {

    int rank;
    int size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
   
        int size_arr = 50;
    
        int arr[] = {3, 6, 7, 5, 3, 5, 6, 2, 9, 1, 2, 7, 0, 9, 3, 6, 0, 6, 2, 6,
        1, 8, 7, 9, 2, 0, 2, 3, 7, 5, 9, 2, 2, 8, 9, 7, 3, 6 ,1, 2,
        9, 3, 1, 9, 4, 7, 8, 4, 5, 0};
        
        MPI_Status status;
 
        for (int i = 1; i < size; i++) {
            MPI_Send(arr, size_arr, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        int base = size_arr / size;
        int remainder = size_arr % size;

        int local_n = base + (rank < remainder ? 1 : 0);
        int start = rank * base + (rank < remainder ? rank : remainder);
        int end = start + local_n;

        int loc_count = count_zeros(arr, start, end);
        int x;

        for (int i = 1; i < size; i++) {
            MPI_Recv(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            loc_count += x;
        }

        printf("Got %d zeros in total\n", loc_count);

    } else {

        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD,  &status);
        
        int size_arr;     
        MPI_Get_count(&status, MPI_INT, &size_arr);

        int* arr = (int*)malloc(sizeof(int) * size_arr);
        MPI_Recv(arr, size_arr, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);       

        int base = size_arr / size;
        int remainder = size_arr % size;

        int local_n = base + (rank < remainder ? 1 : 0);
        int start = rank * base + (rank < remainder ? rank : remainder);
        int end = start + local_n;

        int loc_count = count_zeros(arr, start, end);
        MPI_Send(&loc_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        free(arr);
    }
}
```

### Blocking And Non-Blocking Communication in MPI

- **Blocking**: After sending and receiving the main thread waits for the response. 

- **Non-Blocking**: The main threads delegates the work to a worker thread and continues exectuion.

- **Sync**: The main thread only get the signal when the message was send.

- **Async**: The main thread makes the sending and does not care more about the rest of the process.

The receiving is always **synchronized**.

##### Non-Blocking Sending

Start send operation and return before data is completely copied out of the buffer.

##### Non-Blocking Receiving

Start receive operation and return before data is completely copied in to the buffer.

#### Receiving Variants

- `MPI_Recv`: Blocking variant. It returns when the receiving was done.

- `MPI_Irecv`: Non-Blocking variant. It returns directly and a worker thread handles the 
rest of the transaction.

##### Request Object for Receiving

THe request argument inside `MPI_Irecv` is used to determine if the receiving is done. 

- `MPI_Wait()`: waits for the receiving to be completed.
- `MPI_Test()`: tests if the receiving was completed but it does not wait.

Example with wait: 

```c 
MPI_Request request;

// Open channel for receiving data
MPI_Irecv(&message, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD, &request);

// Thread 0 does stuff without the data
// ...
// Now it needs the data 

MPI_Status status;

MPI_Wait(&request, &status); // waiting for the message

// Data was received and can be used
printf("%d\n", message);
```

Example with test: 

```c 
MPI_Request request;

MPI_Irecv(&message, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD, &request);

// Thread 0 does stuff without the data
// ...
// Now it needs the data 

MPI_Status status;
int completed = 0; 

MPI_TEST(&request, &completed, &status); 

if (completed) {
    printf("%d\n", message);
}
```

###### Defining Our Own Await Function

```c 

void await_request(int rank, MPI_Request* request) {
    
    #if BUSY_WAIT
    int flag = 0; 
    int wait_count = 0;
    MPI_Status status;

    do  {
        wait_count++;
        MPI_Test(request, &flag, &status);
    } while(!flag); 
    #endif
}
```

#### Sending Variants

- `MPI_Send`: is sync and blocking.
- `MPI_ISend`: delegates the sending to a worker thread.
- `MPI_Ssend`: blocks until the receiver starts with receiving.

Example: 

```c 
MPI_Request request;
MPI_Isend(&message, 1, MPI_INT, 1, tagSend, MPI_COMM_WORLD, &request);

// Process 0 does stuff
// ..

MPI_Status status;
MPI_Wait(&request, &status); // waiting for the sending

// The data was send and we can modify use the message data again without race conditions.
message = 0;
```

We can also use `MPI_Test` instead of wait with its consequences.

#### Asynchronous Sending 

When sending asynchronously a buffer is created to copy the data to be send. The data 
gets copied, and a worker thread performs the sending.

- `MPI_Bsend()`: Data gets copied into the buffer and the function returns. A worker thread handles the rest of the operation.

- `MPI_Ibesend()`: Returns even earlier than the previous function, due to the copying being done by the worker thread.

#### Exchange the Values of Variables 

To exchange variables we use `MPI_Sendrecv_replace`

Example:

```c 
if (procRank == 0) {

    int message = 5;
	int sendTag = 1;
	int recvTag = 2;
	
	MPI_Sendrecv_replace(&message, 1, MPI_INT, 1, sendTag, 1, recvTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

} else if (procRank == 1) {

    int message = 7;
	int sendTag = 2;
	int recvTag = 1;

	MPI_Sendrecv_replace(&message, 1, MPI_INT, 0, sendTag, 0, recvTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
```

### simultaneous Send-Recive

Using `MPI_Sendrecv(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status * status)`

```c 

if (procRank == 0) {

	int message = 5;
	int otherMessage = 0;
	int sendTag = 1;
	int recvTag = 2;
	
	MPI_Sendrecv(&message, 1, MPI_INT, 1, sendTag,
	             &otherMessage, 1, MPI_INT, 1, recvTag,
	             MPI_COMM_WORLD, MPI_STATUS_IGNORE);

} else if (procRank == 1) {
	
    int message = 7;
	int otherMessage = 0;
	int sendTag = 2;
	int recvTag = 1;
	
    MPI_Sendrecv(&message, 1, MPI_INT, 0, sendTag,
	             &otherMessage, 1, MPI_INT, 0, recvTag,
	             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
```

### Collective Communication

In a collective communication all processes of a **communicator** participate. 

We can use following orders: 

- `MPI_Bcast(buffer, count, datatype, sender, comm)`: A process sends its data to all other processes. The 
functions works by when all processes call the function depending on their own rank they can realize if they are sending or receiving.

Example: 

```c 
int val = 0;

int  broadcaster_rank = 0;

if (procRank==0) {
    printf("Enter a value: ");
    scanf("%ld", &val);
}

MPI_Bcast(&val, 1, MPI_INT, broadcaster_rank, MPI_COMM_WORLD);
printf("Rank: %d, Value: %d\n", procRank, val);
```

- `MPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm)`: Data accross processes is reduced to a single value via an operation like addtion. Then 
the results is send to one processes.

**Operators**: `MPI_MAX`, `MPI_MIN` `MPI_SUM`, `MPI_PROD`, plus a lot more.

Example: 

```c 
int result = 0;

MPI_Reduce(&procRank)T, MPI_SUM, 0, MPI_COMM_WORLD);
printf("Rank: %d, Wert: %d\n", procRank, result);
```

- `MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm)`: The same as before but the data gets sended to everyone.

Example: 

```c 
MPI_Comm_rank(MPI_COMM_WORLD,&procRank);

int result = 0;

MPI_Allreduce(&procRank, &result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
printf("Rank: %d, Value: %d\n", procRank, result);
```

- `MPI_Barrier`: Like a `pthread_barrier_t` but for processes in MPI but it is realesed 
once every processes has called it.

Example:

```c 

if (procRank == 0) {
    
    int x;

    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Recv((void*)&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

} else {
    
    int x = 1;

    MPI_Barrier(MPI_COMM_WORLD);
 
    MPI_Send((void*)&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
```

- `MPI_Scatter(*sendbuf, sendcount, sendtype, *recvbuf, recvcount, recvtype, root, comm)`: It is used to divide an array accross mulitple processes.

Example:

```c 

```

- `MPI_Gather(*sendbuf, sendcount, sendtype, *recvbuf, recvcount, recvtype, root, comm)`: This is the inverse of scatter, which means that it reasemblies an array from parts 
divided accross other processes.

Example:

```c 
int procRank;
int result[3];

MPI_Comm_rank(MPI_COMM_WORLD,&procRank);

MPI_Gather(&procRank, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);
printf("Rank: %d, Value: %d/%d/%d\n", procRank, result[0], result[1], result[2]);
```

- `MPI_Allgather(*sendbuf, sendcount, sendtype, *recvbuf, recvcount, recvtype, comm)`: Similar to gather, but now all processes have the resulting array.

Example:

```c 
int procRank;
int result[3];

MPI_Comm_rank(MPI_COMM_WORLD,&procRank);

MPI_Gather(&procRank, 1, MPI_INT, result, 1, MPI_INT, MPI_COMM_WORLD);
printf("Rank: %d, Value: %d/%d/%d\n", procRank, result[0], result[1], result[2]);

```

### Communication of Complex Datatypes 

- `MPI_Datatype:` it is an opaque object used when sharing information across processes. It contains tha actual 
data, its memory layout and other metadata.

- `MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype0)`: creates 
a datatype representing regularly spaced blocks of memory.

- `count`: tells us how many blocks.
- `blocklength`: How many contiguous elements per block.
- `stride`: Distance between the start of blocks. Usually the number of columns.

Usually is used to send columns of matrices because the elements are not stored contiguosly.

```c 
// 3 blocks, 2 int sper block, each int starts 4 ints appart
MPI_Type_vector(3, 2, 4, MPI_INT, &newtype); // sending 6 elements
```

Example:

```c 
#include <mpi.h>
#include <stdio.h>

void example7() {

    int rank, size; 

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != 4) {
        if (rank == 0)
            printf("This example requires exactly 4 processes.\n");
        return;
    }

    /* 5x5 block taken from a 10x10 matrix */
    MPI_Datatype block_type;
    MPI_Type_vector(5, 5, 10, MPI_INT, &block_type);
    MPI_Type_commit(&block_type);

    int recv_block[25];   // each process receives 25 ints (5x5)

    if (rank == 0) {
    
        int arr[10][10];

        /* Initialize matrix */
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                arr[i][j] = i * 10 + j;
            }
        }

        /* Scatter one 5x5 block to each process */
        MPI_Scatter(arr, 1, block_type,
                    recv_block, 25, MPI_INT,
                    0, MPI_COMM_WORLD);

    } else {

        MPI_Scatter(NULL, 1, block_type,
                    recv_block, 25, MPI_INT,
                    0, MPI_COMM_WORLD);
    }

    /* Each process modifies its received block */
    for (int i = 0; i < 25; i++) {
        recv_block[i] = rank;
    }

    if (rank == 0) {

        int arr[10][10];  // result buffer

        MPI_Gather(recv_block, 25, MPI_INT,
                   arr, 1, block_type,
                   0, MPI_COMM_WORLD);

        printf("Gather complete.\n");

    } else {

        MPI_Gather(recv_block, 25, MPI_INT,
                   NULL, 1, block_type,
                   0, MPI_COMM_WORLD);
    }

    MPI_Type_free(&block_type);
}
```

- `MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype)`: similar to vector but the elements are 
stored contiguously.

- `MPI_Type_commit(MPI_Datatype* datatype)`: finilizes a derived datatype before use in communication.

Example: 

```c 
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int part_data[10][10];

void test(int procRank, int* data) {
    
    int p = 0;
    
    if (procRank == 0) {
        printf("Number of processes: ");
        scanf("%d", &p);
        printf("\n");
    }
    
    MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (procRank == p) {

        printf("p = %d\n", p);

        for (int i=0; i<100; i++) {

            printf("%3d ", part_data[i/10][i%10]);
      
            if ( i%10 == 9) {
                printf("\n");
            }
        }
    }
}

int main(int argc, char* argv[]) {
    
    // Basic MPI setup
    int proc_rank,proc_count;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&proc_count);
    MPI_Comm_rank(MPI_COMM_WORLD,&proc_rank);

    // Preparing the setup for transporting the data
	MPI_Datatype dest_type;
	MPI_Type_contiguous(100, MPI_INT, &dest_type);
	MPI_Type_commit(&dest_type);

    // Data of the main processes
    int* total_data;

    if (proc_rank == 0) {
        
        // Populating the total_data
        total_data = (int*) malloc(900 * sizeof(int));

        for (int i=0; i<900; i++) {
            total_data[i] = i;
        }

		// Process sends itself its part of the data.
		// MPI_Sendrecv(*sendbuf, sendcount, sendtype, dest, sendtag,
		//              *recvbuf, recvcount, recvtype, source, recvtag, comm, *status)
		MPI_Sendrecv(total_data, 1, source_type, 0, 0, part_data,  1, dest_type,   0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		// Process 0 sends the data to the other process
		for (int i=1; i<9; i++) {
			int start = (i/3) * 300 + (i%3) * 10;
	        MPI_Send(&total_data[start], 1, source_type, i, 0, MPI_COMM_WORLD);
	    }

	} else {
		// Processes receive the data
		MPI_Recv(part_data, 1, dest_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
    
    // Freeing the memory
	if (proc_rank == 0) {
		free(total_data);
	}

	test(proc_rank, (int*) part_data);

	MPI_Type_free(&source_type);
	MPI_Type_free(&dest_type);

	MPI_Finalize();    int count,
    MPI_Datatype oldtype,
    MPI_Datatype *newtype
}
```

### Custom Communicators

The only possibility to create new communicators inside MPI is to take an already existing communicator and
reduce the number of process it contains. Adding process to an already existing commincator is not allowed.

Example with `MPI_Group_excl`:

```c 
MPI_Group world_group, win_group;
MPI_Comm win_comm;

// This processes are not wanted
int loser[2];
loser[0] = 0;   //main
loser[1] = procCount - 1; // the last

// Extract group from communicator
MPI_Comm_group(MPI_COMM_WORLD, &world_group);

// creating a new group without the loosers from our already extracted group
MPI_Group_excl(world_group, 2, loser, &win_group);
  
// Creating the new communicator with the new group.
MPI_Comm_create(MPI_COMM_WORLD, win_group, &win_comm);
```

There is also `MPI_Group_incl` which works similar but the array contains IDs of the processes we want to keep.

#### Splitting 

`MPI_Group_split(MPI_Comm comm, int color, int key, MPI_Comm* newcomm)`: this function creates a new communicator 
by spliting a communicator into a group of subcommunicator based on the parameters color and key.

The `color` parameter is used to mark the group of which process is going to be included while 
`key` is the rank inside the new communicator.

Example with 16 processes divided into 4 groups: 

```c
int rank, size; 

MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size); 

int color = rank / 4;

MPI_Comm row_comm;
MPI_Comm_split(MPI_COMM_WORLD, color, rank, &row_comm);

int row_rank, row_size;

MPI_Comm_rank(row_comm, &row_rank);
MPI_Comm_size(row_comm, &row_size);

printf("WORLD RANK/SIZE: %d/%d \t ROW RANK/SIZE: %d/%d\n", rank, size, row_rank, row_size);

MPI_Comm_free(&row_comm);
```

### Parallelization Strategies 

- **Task/Functional Decomposition**: This is when a problem can splitted into separated steps 
which may be independent of each others. In such case, the steps can be parallelized.

- **Data/Domain Decomposition**: When the amount of data is large, we can splitt work across threads becuase each 
processing unit does not depend on the others.



