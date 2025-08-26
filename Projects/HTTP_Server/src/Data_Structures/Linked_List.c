#include "Linked_List.h"

Linked_List* create_List() {

    Linked_List* list = malloc(sizeof(Linked_List));

    if (list == NULL) {
        printf("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;

    return list;
}

// Creating a node

Node* create_node(int data) {

  Node* new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  new_node->data = data;
  new_node->next = NULL;

  return new_node;
}

// Appending a node at the start

void append_at_start(Linked_List* list, int data) {

  Node* new_node = create_node(data);

  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    new_node->next = list->head;
    list->head = new_node;
  }

    printf("Node was appended at the start of the list\n");
    list->len++; 
}

// Pushing a node to the end

void append_at_end(Linked_List* list, int data) {

  Node* new_node = create_node(data);

  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
    new_node->next = NULL;
  }
  printf("Node was appended at the end of the list\n");
  list->len++;
}
// Pop a node

int pop_node(Linked_List* list) {

  Node* current = list->head;
  Node* previous = NULL;

  if (list->head == NULL) {
    
    printf("The list is empty\n");
  
    return EMPTY_LIST;

  } else if (list->head == list->tail) {
  
    list->head = NULL;
   
    list->tail = NULL;
    printf("The last node was deleted. The list is empty\n");
    
    return EMPTY_LIST;
  }

    while (current->next != NULL) {

      previous = current;
      current = current->next;
    }
    
    int data = previous->next->data;
    list->tail = previous;
    
    free(current);
    printf("The last node was deleted\n");
    list->len--;

    return data;
}

// Inserting a node

void insert_node(Linked_List* list, int data, int position) {

  if (list->head == NULL && list->tail == NULL) {
    append_at_start(list, data);
  }

  Node* current = list->head;
  Node* previous = NULL;

  while (current->next != NULL && position != 0) {
    previous = current;
    current = current->next;
    position--;
  }

  if (position != 0) {
    printf("The position is invalid\n");
    return;
  }

  Node* new_node = create_node(data);

  if (previous == NULL) {
    new_node->next = list->head;
  } else {
    previous->next = new_node;
    new_node->next = current;
  }

  printf("The node was inserted at position: %d \n", position);
  
  list->len++;
}

// Deleting a node

int delete_node(Linked_List* list, int position) {

    if (list->head == NULL) {
        printf("The list is empty\n");
        return EMPTY_LIST;
    }

    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL && position != 0) {
        previous = current;
        current = current->next;
        position--;
    }

    if (current == NULL) {
        printf("The position is invalid\n");
        return EMPTY_LIST;
    }

    if (previous == NULL) {

        list->head = current->next;

    if (list->head == NULL) {
          list->tail = NULL;
    }

    } else {

        previous->next = current->next;

        if (current->next == NULL) {
              list->tail = previous;
        }
    }
    
    int data = current->data;
    free(current);
    
    list->len--;
    return data;
}

// Deleting the list

void delete_list(Linked_List* list) {

  Node* current = list->head;
  Node* next_node;

  while (current != NULL) {
    next_node = current;
    free(current);
    current = next_node;
  }

  free(list);

  printf("The list was deleted\n");
}

Node* reverse(Linked_List* list) {

  if (list->head == NULL) {
    return NULL;
  }

  Node* prev = NULL;
  Node* current = list->head;
  Node* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;

    current = next;
  }

  list->head = prev;
  return list->head;
}


