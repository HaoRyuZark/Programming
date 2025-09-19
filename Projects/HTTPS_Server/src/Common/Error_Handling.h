#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>

#define handle_error_with_return(ptr, value, msg) \
        if (ptr == NULL) {                        \
            printf("%s", (msg));                  \
            return (value);                       \
        }

#define handle_error(ptr, msg)                   \
        if (ptr == NULL) {                       \
            printf("%s", (msg));                 \
            return;                              \
        }


#endif // !ERROR_HANDLING
