#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {

  void* data;
  struct Node* next;
} Node;

typedef struct Linked_List {

  Node* head;
  Node* tail;

} Linked_List;

// Creating a list

Linked_List* create_List() {

  Linked_List* list = malloc(sizeof(Linked_List));
  if (list == NULL) {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }
  list->head = NULL;
  list->tail = NULL;

  return list;
}

// Creating a node

Node *create_node(void *data, int size) {

  Node *new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  new_node->data = malloc(sizeof(data));
  memcpy(new_node->data, data, size);
  new_node->next = NULL;

  return new_node;
}

// Appending a node at the start

void append_at_start(Linked_List *list, void *data, int size) {

  Node *new_node = create_node(data, size);

  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    new_node->next = list->head;
    list->head = new_node;
  }

  printf("Node was appended at the start of the list\n");
}

// Pushing a node to the end

void append_at_end(Linked_List *list, void *data, int size) {

  Node *new_node = create_node(data, size);

  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
    new_node->next = NULL;
  }
  printf("Node was appended at the end of the list\n");
}
// Pop a node

void pop_node(Linked_List *list) {

  Node *current = list->head;
  Node *previous = NULL;

  if (list->head == NULL) {
    printf("The list is empty\n");
  } else if (list->head == list->tail) {
    list->head = NULL;
    list->tail = NULL;
    printf("The last node was deleted. The list is empty\n");
  } else {

    while (current->next != NULL) {

      previous = current;
      current = current->next;
    }

    list->tail = previous;
    free(current->data);
    free(current);
    printf("The last node was deleted\n");
  }
}

// Inserting a node

void insert_node(Linked_List *list, void *data, int size, int position) {

  if (list->head == NULL && list->tail == NULL) {
    append_at_start(list, data, size);
  }
  Node *current = list->head;
  Node *previous = NULL;

  while (current->next != NULL && position != 0) {
    previous = current;
    current = current->next;
    position--;
  }

  if (position != 0) {
    printf("The position is invalid\n");
    return;
  }

  Node *new_node = create_node(data, size);

  if (previous == NULL) {
    new_node->next = list->head;
  } else {
    previous->next = new_node;
    new_node->next = current;
  }

  printf("The node was inserted at position: %d \n", position);
}

// Deleting a node

void delete_node(Linked_List *list, int position) {

  if (list->head == NULL) {
    printf("The list is empty\n");
    return;
  }
  Node *current = list->head;
  Node *previous = NULL;

  while (current != NULL && position != 0) {
    previous = current;
    current = current->next;
    position--;
  }

  if (current == NULL) {
    printf("The position is invalid\n");
    return;
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

  free(current->data);
  free(current);
}

// Deleting the list

void delete_list(Linked_List *list) {

  Node *current = list->head;
  Node *next_node;

  while (current != NULL) {
    next_node = current;
    free(current->data);
    free(current);
    current = next_node;
  }

  free(list);

  printf("The list was deleted\n");
}

Node *reverse(Linked_List *list) {

  if (list->head == NULL) {
    return NULL;
  }

  Node *prev = NULL;
  Node *current = list->head;
  Node *next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;

    current = next;
  }

  list->head = prev;
  return list->head;
}

Node *reverse_segment(Linked_List *list, int left, int right) {
  if (list->head == NULL || left == right) {
    return list->head;
  }

  Node dummy;
  dummy.next = list->head;
  Node *lp = &dummy;

  for (int i = 1; i < left; i++) {
    lp = lp->next;
  }

  Node *current = lp->next;
  Node *prev = NULL;

  for (int i = 0; i <= right - left; i++) {
    Node *next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  lp->next->next = current;
  lp->next = prev;

  return dummy.next;
}

int main() { return 0; }
