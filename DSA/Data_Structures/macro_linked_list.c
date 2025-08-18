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
