#ifndef migux_string_H
#define migux_string_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Internal error message constants */
#define S_ERR_SELF_NULL  "string: self pointer is NULL\n"
#define S_ERR_STR_NULL   "string: internal buffer allocation failed\n"
#define S_ERR_REALLOC    "string: reallocation failed\n"
#define S_OUT_OF_BOUNDS  "string: can not get char, the index is out of bounds\n"
#define S_OTHER_NULL     "string: other string is NULL\n"

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Null-check macros — use fprintf to avoid strerror contamination from perror */

#define s_check_null_return_null(ptr, msg) \
    do { if ((ptr) == NULL) { fprintf(stderr, "%s", (msg)); return NULL;        } } while (0)

#define s_check_null_return_failure(ptr, msg) \
    do { if ((ptr) == NULL) { fprintf(stderr, "%s", (msg)); return EXIT_FAILURE; } } while (0)

#define s_check_null_return_void(ptr, msg) \
    do { if ((ptr) == NULL) { fprintf(stderr, "%s", (msg)); return;             } } while (0)

#define s_check_allocation_of_inner_char_buffer_return_NULL(ptr) \
    do { if (ptr == NULL) { free(ptr); fprintf(stderr, "%s", S_ERR_STR_NULL); return NULL; } } while (0)


//////////////////////////////////////////////////////////////////////////////////////////////////

/* Public Struct */

typedef struct string {
    char*  str;
    size_t len;
    size_t capacity;
} string;

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Stack constructor (compound literal).
 * NOTE: str is not owned — do NOT call append/concat/resize on the result. */
#define create_on_the_stack_from_raw_str(str, len) \
    (string){ .str = (s), .len = (len), .capacity = (len) }

#define create_on_the_stack_from_raw_str_empty(str, len) \
   (string){.str = (NULL), .len = (len), .capacity = (len)} 

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Heap constructors */

string* create_empty_string(void);

string* create_string_from(const char* str);

string* create_string_from_with_len(const char* str, size_t len);

string* create_string_from_c_string(const string* other);

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Accessors */

int get_len(const string* self);

char* get_str(const string* self);

int get_char_at_index(const string* self, size_t index);

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Operations */

string* get_substring(const string* self, size_t start, size_t end);

bool compare_strings(const string* self, const string* other);

int append_to_c_string(string* self, char c);

void concatenate_c_strings(string* self, const string* other);

void concatenate_c_string_and_native_string(string* self, const char* other, size_t other_size);

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Conversion — caller is responsible for free()-ing the returned pointer */

char* to_string_with_null_terminator(const string* self);

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Search */

size_t find_first_occurrence_of(const string* self, const char* pattern);

int* find_occurrences_of(const string* self, const char* pattern, size_t* out_count);

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Hash */

unsigned long hash(const string* self);

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Destructor */

void destructor(string* self);

#endif
