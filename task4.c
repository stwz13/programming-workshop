#include "task4.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
struct Node {
  int element;
  Node *link;
};
typedef struct List {
  struct Node *head;
} List;

List *create_new_list() {
  struct List *new_list = malloc(sizeof(List));
  new_list->head = NULL;
  return new_list;
}
int count(List *list) {
  int count = 0;
  Node *curr = list->head;
  while (curr != NULL) {
    curr = curr->link;
    count++;
  }
  return count;
}
void app_to_top(List *list, int new_element) {
  struct Node *new_node = malloc(sizeof(Node));
  new_node->element = new_element;
  if (list->head == NULL) {
    new_node->link = NULL;
    list->head = new_node;
  } else {
    new_node->link = list->head;
    list->head = new_node;
  }
}
void app_to_end(List *list, int new_element) {
  Node *new_node = malloc(sizeof(Node));
  new_node->element = new_element;
  if (list->head == NULL) {
    new_node->link = NULL;
    list->head = new_node;
  } else {
    Node *curr = list->head;
    while (curr->link != NULL)
      curr = curr->link;
    new_node->link = NULL;
    curr->link = new_node;
  }
}

void app(List *list, int new_element, int number) {
  if (number == 1)
    app_to_top(list, new_element);
  else if (number == count(list) + 1)
    app_to_end(list, new_element);
  else if (count(list) < number) {
    printf("The number exceeds the number of nodes in the list\n");
  } else {
    Node *new_node = malloc(sizeof(Node));
    new_node->element = new_element;
    Node *curr = list->head;
    for (int i = 0; i < number - 2; i++)
      curr = curr->link;
    new_node->link = curr->link;
    curr->link = new_node;
  }
}
void remove_node(List *list, int number) {
  Node *curr = list->head;
  if (count(list) == 0) {
    printf("List is empty\n");
  } else if (count(list) < number || number <= 0)
    printf("The number exceeds the number of list items or is not a natural "
           "number.\n");
  else if (number == 1) {
    list->head = curr->link;
  } else {
    for (int i = 0; i < number - 2; i++)
      curr = curr->link;
    Node *node_to_delete = curr->link;
    curr->link = curr->link->link;
    free(node_to_delete);
  }
}
int find_element(List *list, int number) {
  if (count(list) < number || number <= 0) {
    printf("The number exceeds the number of nodes in the list\n");
    return -1;
  }
  Node *curr = list->head;
  for (int i = 0; i < number - 1; i++)
    curr = curr->link;
  return curr->element;
}
void delete_list(List *list) {
  Node *curr = list->head;
  while (curr != NULL) {
    Node *node_to_delete = curr;
    curr = curr->link;
    free(node_to_delete);
  }
  free(list);
}