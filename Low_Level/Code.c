#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Basic C Features 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Bitweise Operators 


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
void threads_producer_consumer_example() {
    
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
}


void* argument_and_return_routine(void* args) {
    
    int* res = malloc(sizeof(int));
    *res = *(int*)args + 1;

    return (void*)res;
}

void* try_lock_routine(void* args) {
    
    if (pthread_mutex_trylock(&mutex) == 0) { // it does not guarantee the the lock is going to be got
        // Critical section
        pthread_mutex_unlock(&mutex);
    }
    
    printf("Hello, Mom");
}

void example_for_arugment_and_return_values_in_threads() {

    pthread_t t1;
    int val = 10;
    int* arg = &val; // this optional, we cal just pass &val into the create function

    int* res;

    pthread_create(&t1, NULL, &argument_and_return_routine, (void*)arg);

    pthread_join(t1,(void**)&res);

    free(res);

}

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
}

void* routine(void* args) { printf("Ding Dong!"); }

void detached_threads() {

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

void rec_mutex() {

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
}

sem_t semaphore;

void* routine_3(void* args) {
    
    int sem_val;
    sem_wait(&semaphore);
    sem_getvalue(&semaphore, &sem_val);
    printf("Hola Mami %d\n", sem_val);
    sem_post(&semaphore); 
}


void semaphore_example() {
    
    pthread_t t1; 
    pthread_t t2; 
    
    sem_init(&semaphore, 0, 1); // the 2nd argument is for the number of extra procceses and the 3th for the number of threads
                                                     // which are allowed to enter the critical section at the same time
    
    pthread_create(&t1, NULL, &routine_3, NULL); 
    pthread_create(&t2, NULL, &routine_3, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&semaphore);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Entry Point

int main() {

    return 0;
}
