#include "migux_strings.h"

#define INITIAL_CAPACITY 50

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Private */

static int cs_resize(string* self) {
    
    if (self == NULL) {
        fprintf(stderr, "%s", S_ERR_SELF_NULL);
        return EXIT_FAILURE;
    }
    
    size_t new_cap = self->capacity * 2;
    char*  tmp     = (char*)realloc(self->str, new_cap);
    
    if (tmp == NULL) {
        fprintf(stderr, "%s", S_ERR_REALLOC);
        return EXIT_FAILURE;
    }
    
    self->str      = tmp;
    self->capacity = new_cap;
    return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Heap constructors */

void create_empty_string(string* self) {

    s_check_null_return(self, S_ERR_SELF_NULL);

    self->str = (char*)malloc(INITIAL_CAPACITY);

    s_check_allocation_of_inner_char_buffer_return(self->str);

    self->len      = 0;
    self->capacity = INITIAL_CAPACITY;
}

void create_string_from(string* self, const char* str) {

    s_check_null_return(str, "string: input string is NULL\n");

    size_t len = strlen(str); 

    s_check_null_return(self, S_ERR_SELF_NULL);

    size_t cap = len < INITIAL_CAPACITY ? INITIAL_CAPACITY : len * 2;

    self->str  = (char*)malloc(cap);
    s_check_allocation_of_inner_char_buffer_return(self->str); 

    memcpy(self->str, str, len);
    self->len      = len;
    self->capacity = cap;
}

void create_string_from_with_len(string* self, const char* str, size_t len) {

    s_check_null_return(str, "string: input string is NULL\n");

    s_check_null_return(self, S_ERR_SELF_NULL);

    size_t cap = len < INITIAL_CAPACITY ? INITIAL_CAPACITY : len * 2;
    self->str  = (char*)malloc(cap); 

    s_check_allocation_of_inner_char_buffer_return(self->str);  

    memcpy(self->str, str, len);
    self->len      = len;
    self->capacity = cap;
}

void create_string_from_c_string(string* self, const string* other) {

    s_check_null_return(other, S_ERR_SELF_NULL);
 
    s_check_null_return(self, S_ERR_SELF_NULL);

    self->str = (char*)malloc(other->capacity);
    
    s_check_allocation_of_inner_char_buffer_return(self->str); 
 
    memcpy(self->str, other->str, other->len);
    self->len      = other->len;
    self->capacity = other->capacity;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Accessors */

int get_len(const string* self) {
    s_check_null_return_failure(self, S_ERR_SELF_NULL);
    return self->len;
}

char* get_str(const string* self) {
    s_check_null_return_null(self, S_ERR_SELF_NULL);
    return self->str;
}


int get_char_at_index(const string* self, size_t index) {
    
    s_check_null_return_failure(self, S_ERR_SELF_NULL); 
    s_check_null_return_failure(self, S_OUT_OF_BOUNDS);
   
    return (unsigned char)self->str[index];
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Operations */

int append_to_c_string(string* self, char c) {
    
    s_check_null_return_failure(self, S_ERR_SELF_NULL);

    if (self->len == self->capacity) {
        if (cs_resize(self) != EXIT_SUCCESS) { return EXIT_FAILURE; }
    }
    
    self->str[self->len++] = c;
    return EXIT_SUCCESS;
}


void get_substring(const string* self, string* other, size_t start, size_t end) {
    
    s_check_null_return(self, S_ERR_SELF_NULL);

    if (start > self->len || end > self->len || start > end) {
        fprintf(stderr, "string: invalid substring range [%zu, %zu) for len=%zu\n",
                start, end, self->len);
        return;
    }

    create_string_from_with_len(other, self->str + start, end - start);
}

bool compare_strings(const string* self, const string* other) {
    if (self == NULL || other == NULL) {
        fprintf(stderr, "%s", S_ERR_SELF_NULL);
        return false;
    }
    if (self->len != other->len) return false;
    return memcmp(self->str, other->str, self->len) == 0;
}

void concatenate_c_strings(string* self, const string* other) {
    
    s_check_null_return(self,  S_ERR_SELF_NULL);
    s_check_null_return(other, S_ERR_SELF_NULL);

    for (size_t i = 0; i < other->len; i++) {
        if (append_to_c_string(self, other->str[i]) != EXIT_SUCCESS) { return; }
    }
}

void concatenate_c_string_and_native_string(string* self, const char* other, size_t other_size) {
   
    s_check_null_return(self,  S_ERR_SELF_NULL);
    s_check_null_return(other, S_OTHER_NULL);

    for (size_t i = 0; i < other_size; i++) {
        if (append_to_c_string(self, other[i]) != EXIT_SUCCESS) return;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Conversion */

char* to_string_with_null_terminator(const string* self) {
    
    s_check_null_return_null(self, S_ERR_SELF_NULL);

    char* ret = (char*)malloc(self->len + 1);
    
    if (ret == NULL) {
        fprintf(stderr, "%s", S_ERR_STR_NULL);
        return NULL;
    }
    
    memcpy(ret, self->str, self->len);
    ret[self->len] = '\0';
    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Search */

// TODO

size_t find_first_occurrence_of(const string* self, const char* pattern) {return 0;}

int* find_occurrences_of(const string* self, const char* pattern, size_t* out_count) { return NULL; }

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Hash */

unsigned long hash(const string* self) { return 0; }

//////////////////////////////////////////////////////////////////////////////////////////////////

/* Destructor */

void destructor(string* self) {
    
    if (self == NULL) { return; }

    free(self->str);
    free(self);
}
