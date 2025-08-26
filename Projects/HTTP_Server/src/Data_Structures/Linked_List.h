#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

int const EMPTY_LIST = -1;

typedef struct Linked_List {

  Node* head;
  Node* tail;
  int len;

} Linked_List;


Linked_List* create_List();
void append_at_start(Linked_List* list, int data);
void append_at_end(Linked_List* list, int data);
void insert_node(Linked_List* list, int data, int position);
int pop_node(Linked_List* list);
int delete_node(Linked_List* list, int position);
void delete_list(Linked_List* list);
Node* reverse(Linked_List* list);


#endif
