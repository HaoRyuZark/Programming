#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>
#include <stdlib.h>

#define handle_error_with_return(ptr, value, msg) \
        if (ptr == NULL) {                        \
            perror(msg);                          \
            return (value);                       \
        }

#define handle_error(ptr, msg)                   \
        if (ptr == NULL) {                       \
            perror(msg);                         \
            return;                              \
        }

#define handle_error_and_exit(value, msg)          \
        if (value < 0) {                           \
            perror(msg);                           \
            exit(1);                               \
        }


#endif // !ERROR_HANDLING
