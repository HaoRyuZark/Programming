#ifndef C_String_H
#define C_String_H

#include <cstddef>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

#define handle_null_pointer_with_return_null(ptr, msg)         \
    if (ptr == NULL) {                                         \ 
        perror(msg);                                           \ 
        return NULL;                                           \
    }                                                          

#define handle_null_pointer_with_return_1(ptr, msg)            \
    if (ptr == NULL) {                                         \ 
        perror(msg);                                           \ 
        return 1;                                              \
    }                                                          

#define _SELF_IS_NULL "The C_String ptr is NULL\n"
#define _REALLOC_FAILURE "The reallocation process failed\n"

typedef struct C_String {
    
    char* str; 
    size_t len; 
    size_t capacity;

} C_String;

//////////////////////////////////////////////////////////////////////////////////////////////////

// Private 

int _rezize(C_String* self);

//////////////////////////////////////////////////////////////////////////////////////////////////

// Public 

size_t get_len(C_String* self);

char* get_str(C_String* self);

C_String* create_empty_string();

C_String* create_string_from(char* str);

C_String* create_string_from_c_string(C_String* str);

C_String* get_substring(C_String* self, size_t start, size_t end);

bool compare_strings(C_String* self, C_String* other);

C_String* concatenate_c_strings(C_String* self, C_String* other);

C_String* concatenate_c_string_and_native_string(C_String* self, char* other, int other_size);

char* to_string_with_null_terminator(C_String* self);

char* to_string(C_String* self);

size_t find__first_occurrence_of(C_String* str, char* pattern);

int* find_occurrences_of(C_String* str, char* pattern);

unsigned long hash(C_String* self);

void destructor(C_String* self);


#endif
