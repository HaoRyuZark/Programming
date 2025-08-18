#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Doubly_Linked_List {
    Node* head;
    Node* tail;
    unsigned int length;
} Doubly_Linked_List;

Node* create_node(int data) {
    
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->data = data;

    return node;
}

Doubly_Linked_List* init() {
    
    Doubly_Linked_List* new_list = (Doubly_Linked_List*)malloc(sizeof(Doubly_Linked_List));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->length = 0;

    return new_list;
}

Node* first(Doubly_Linked_List* list) {
    if(list == NULL || list->head == NULL || list->tail == NULL) {
        printf("No List\n");
        exit(1);
    }
    return list->head;
}

Node* last(Doubly_Linked_List* list) {
    if(list == NULL || list->head == NULL || list->tail == NULL) {
        printf("No List\n");
        exit(1);
    }
    return list->tail;
}

void push_back(Doubly_Linked_List* list, int data) {
    
    if (list == NULL) {
        printf("No list\n");
        exit(1);
    }

    Node* new_tail = create_node(data);

    if (list->head == NULL) {

        list->head = new_tail;
        list->tail = new_tail;
    
    } else {
        
        list->tail->next = new_tail;
        new_tail->prev = list->tail;
        list->tail = new_tail;
    
    }

    list->length += 1;
}

void push_front(Doubly_Linked_List* list, int data) {
    
    if (list == NULL) {
        printf("No list\n");
        exit(1);
    }
    if (list->head == NULL) {
        
        Node* node = create_node(data);
        list->head = node;
        list->tail = node;
        list->length += 1;
        
        return;
    }

    Node* node = create_node(data);
    node->next = list->head;
    list->head->prev = node; 
    list->head = node;
    list->length += 1;
}


void insert(Doubly_Linked_List* list, int data, unsigned int position) {
    
    if(list == NULL) {
        printf("No List\n");
        exit(1);
    }
    if(position == 0) {
        push_front(list, data);
        return;
    }
    if(position == list->length - 1) {
        push_back(list, data);
        return;
    }

    if(position >= list->length) {
        printf("The position is invalid\n");
        return;
    }

    Node* new_node = create_node(data);
    Node* current = list->head;
    int current_p = 0;

    while(current_p != position) {
        current = current->next;
        ++current_p;
    }

    new_node->next = current->next;
    if(current->next != NULL) {
        current->next->prev = new_node;
    }
    current->next = new_node;
    new_node->prev = current;

    list->length += 1;

    printf("Node inserted\n");
}

int pop_front(Doubly_Linked_List* list) {
    if(list == NULL) {
        printf("No List\n");
        exit(1);
    }
    if(list->length == 0) {
        printf("List is already empty\n");
        return -1;
    }

    Node* old_head = list->head;
    
    if(list->length == 1) {

        list->head = NULL;
        list->tail = NULL;
        list->length -= 1;

        return old_head->data;
    }

    Node* new_head = list->head->next;
    list->head = new_head;
    new_head->prev = NULL;

    list->length -= 1;
    return old_head->data;
}

int pop_back(Doubly_Linked_List* list) {
    if(list == NULL) {
        printf("No List\n");
        exit(1);
    }
    if(list->length == 0) {
        printf("List is already empty\n");
        return -1;
    }

    Node* old_tail = list->tail;
    
    if(list->length == 1) {

        list->head = NULL;
        list->tail = NULL;
        list->length -= 1;

        return old_tail->data;
    }

    list->tail = list->tail->prev;
    list->tail->next = NULL;

    list->length -= 1;
    return old_tail->data;
}

int delete(Doubly_Linked_List* list, unsigned int position) {
    if(list == NULL) {
        printf("No List\n");
        exit(1);
    }
    if(position >= list->length) {
        printf("The position is invalid\n");
        return -1;
    }
    if(position == 0) {
        return pop_front(list);
    }
    if(position == list->length - 1) {
        return pop_back(list);
    }

    Node* current = list->head;
    unsigned int current_p = 0;

    while(current_p != position) {
        current = current->next;
        ++current_p;
    }
    
    current->next->prev = current->prev;
    current->prev->next = current->next;
    list->length -= 1;
    
    return current->data;
}

unsigned int get_len(Doubly_Linked_List* list) {
    if(list == NULL) {
        printf("No List\n");
        exit(1);
    }

    return list->length;
}

void print_list(Doubly_Linked_List* list) {

    Node* current = list->head;
    int index = 0;
    printf("NULL <- ");
    while(current != NULL) {
        printf("%d -> ", current->data);
        ++index;
        current = current->next;
    }
    printf(" NULL\n");
}

void free_list(Doubly_Linked_List* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->head;
    Node* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    free(list);
}

Node* get_nth_node(Doubly_Linked_List* list, unsigned int position) {
    if(list == NULL) {
        printf("No list\n");
        return NULL;
    }
    if(position == 0) {
        return first(list);
    }
    if(position == list->length - 1) {
        return last(list);
    }

    Node* current = list->head;
    unsigned int p = 0;

    while(p != position) {
        current = current->next;
        ++p;
    }

    return current;
}

void print_nth_data(Doubly_Linked_List* list, unsigned int position) {
    if(list == NULL) {
        printf("No juice\n");
        return;
    }
    Node* node = get_nth_node(list, position);
    printf("%s\n", node->data);
}

void make_cycle(Doubly_Linked_List* list) {
    
    if (list == NULL) {
        perror("Sike");
        exit(1);
    }

    list->tail->next = list->head;
}

int check_cylces(Doubly_Linked_List* list) {
    
    if (list == NULL || list->head == NULL || list->tail == NULL) {
        return 1;
    }

    if (list->length == 1) {
        return 1;
    }

    Node* slow = list->head;
    Node* fast =  list->head;

    while (fast != NULL) {
        
        fast = fast->next->next;
        
        if (fast == NULL) {
            return 1;
        }

        if (slow == fast) {
            break;
        }

        slow = slow->next;

    }
    
    return 0;
}

int main() {
    
    printf("Hello, World!\n");

    Doubly_Linked_List* list = init();

    push_front(list, 40);
    push_front(list, 30);
    push_front(list, 20);
    push_front(list, 70);
    make_cycle(list);
    
    printf("%d\n", check_cylces(list));

    return 0;
}
