#include "task4.h"
#include <stdio.h>
#include <stdlib.h>
struct Node {
  int element;
  struct Node *link;
};
struct List {
  struct Node *head;
};
struct List *create_new_list() {
  struct List *new_list = malloc(sizeof(struct List));
  new_list->head = NULL;
  return new_list;
}
int count(struct List *list) {
  int count = 0;
  struct Node *curr = list->head;
  while (curr != NULL) {
    curr = curr->link;
    count++;
  }
  return count;
}
void app_to_top(struct List *list, int new_element) {
  struct Node *new_node = malloc(sizeof(struct Node));
  new_node->element = new_element;
  if (list->head == NULL) {
    new_node->link = NULL;
    list->head = new_node;
  } else {
    new_node->link = list->head;
    list->head = new_node;
  }
}
void app_to_end(struct List *list, int new_element) {
  struct Node *new_node = malloc(sizeof(struct Node));
  new_node->element = new_element;
  if (list->head == NULL) {
    new_node->link = NULL;
    list->head = new_node;
  } else {
    struct Node *curr = list->head;
    while (curr->link != NULL)
      curr = curr->link;
    new_node->link = NULL;
    curr->link = new_node;
  }
}

void app(struct List *list, int new_element, int number) {
  if (number == 1)
    app_to_top(list, new_element);
  else if (number == count(list) + 1)
    app_to_end(list, new_element);
  else if (count(list) < number) {
    printf("The number exceeds the number of nodes in the list");
  } else {
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->element = new_element;
    struct Node *curr = list->head;
    for (int i = 0; i < number - 2; i++)
      curr = curr->link;
    new_node->link = curr->link;
    curr->link = new_node;
  }
}
void remove_node(struct List *list, int number) {
  struct Node *curr = list->head;
  if (count(list) == 0) {
    printf("List is empty");
  } else if (count(list) < number || number <= 0)
    printf("The number exceeds the number of list items or is not a natural "
           "number.\n");
  else if (number == 1) {
    list->head = curr->link;
  } else {
    for (int i = 0; i < number - 2; i++)
      curr = curr->link;
    curr->link = curr->link->link;
  }
}
int find_element(struct List *list, int number) {
  if (count(list) < number || number <= 0)
    printf("The number exceeds the number of nodes in the list");
  struct Node *curr = list->head;
  for (int i = 0; i < number - 1; i++)
    curr = curr->link;
  return curr->element;
}