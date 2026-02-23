#include "C_Strings.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

// Private 

int _rezize(C_String* self) {
    
    handle_null_pointer_with_return_1(self, _SELF_IS_NULL)

    self->str = (char*)realloc(self->str, 2 * self->capacity);
     
    handle_null_pointer_with_return_1(self->str, _REALLOC_FAILURE)

    self->capacity = self->capacity * 2;

    return 0;
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

C_String* create_empty_string();

C_String* create_string_from(char* str);

C_String* create_string_from_c_string(C_String* str);

C_String* get_substring(C_String* self, size_t start, size_t end);

bool compare_strings(C_String* self, C_String* other);

C_String* concatenate_c_strings(C_String* self, C_String* other);

C_String* concatenate_c_string_and_native_string(C_String* self, char* other, int other_size);

char* to_string_with_null_terminator(C_String* self);

char* to_string(C_String* self);

int* find_occurrences_of(C_String* str, char* pattern);


