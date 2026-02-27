#include "C_Strings.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////////////////

// Private 

int _rezize(C_String* self) {
    
    handle_null_pointer_with_return_1(self, _SELF_IS_NULL)
    
    self->str = (char*)realloc(self->str, 2 * self->capacity);
     
    handle_null_pointer_with_return_1(self->str, _REALLOC_FAILURE)

    self->capacity = self->capacity * 2;

    return 0;
}

void _copy_string_with_len(char* dest, char* source, int len) {

    for(int i = 0; i < len; i++) {
        dest[i] = source[i];
    }    
}

void _copy_string_without_len(char* dest, char* source) {
    
    int i = 0; 

    while (source[i] != '\0') {
        dest[i] = source[i];
        i++;
    }    
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// Public 

size_t get_len(C_String* self) {
    handle_null_pointer_with_return_1(self, _SELF_IS_NULL) 
    return self->len;
}

char* get_str(C_String* self) {
    handle_null_pointer_with_return_null(self, _SELF_IS_NULL) 
    return self->str;
}

C_String* create_empty_string() {

    C_String* self = (C_String*)malloc(sizeof(C_String));

    handle_null_pointer_with_return_null(self, _SELF_IS_NULL)

    self->len = 0;
    self->capacity = 20; 
    self->str = (char*)malloc(sizeof(char) * self->capacity);

    handle_null_pointer_with_return_null(self->str, _STR_IS_NULL)

    return self;
}

C_String* create_string_from(char* str) {
    
    C_String* self = (C_String*)malloc(sizeof(C_String));

    handle_null_pointer_with_return_null(self, _SELF_IS_NULL)

    self->len = 0;
    self->capacity = 20; 
    self->str = (char*)malloc(sizeof(char) * self->capacity);

    handle_null_pointer_with_return_null(self->str, _STR_IS_NULL)

    _copy_string_without_len(self->str, str); 
    
    return self;
}

C_String* create_string_from_with_len(char* str, int len) { 

    C_String* self = (C_String*)malloc(sizeof(C_String));

    handle_null_pointer_with_return_null(self, _SELF_IS_NULL)

    self->len = len;
    self->capacity = len*2; 
    self->str = (char*)malloc(sizeof(char) * self->capacity);

    handle_null_pointer_with_return_null(self->str, _STR_IS_NULL)

    _copy_string_with_len(self->str, str, len);
    
    return self;
}

C_String* create_string_from_c_string(C_String* other) {
    
    handle_null_pointer_with_return_null(other, _SELF_IS_NULL)
    
    C_String* self = (C_String*)malloc(sizeof(C_String));

    handle_null_pointer_with_return_null(self, _SELF_IS_NULL)

    self->len = other->len;
    self->capacity = other->capacity; 
    self->str = (char*)malloc(sizeof(char) * self->capacity);

    handle_null_pointer_with_return_null(self->str, _STR_IS_NULL)
    
    for (int i = 0; i < other->len; i++) {
        self->str[i] = other->str[i];
    }
    
    return self;
}

C_String* get_substring(C_String* self, size_t start, size_t end);

bool compare_strings(C_String* self, C_String* other);

C_String* concatenate_c_strings(C_String* self, C_String* other);

C_String* concatenate_c_string_and_native_string(C_String* self, char* other, int other_size);

char* to_string_with_null_terminator(C_String* self);

char* to_string(C_String* self);

int* find_occurrences_of(C_String* str, char* pattern);


