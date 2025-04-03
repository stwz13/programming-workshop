#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESSFUL_COMPLETION 0
#define LIST_IS_EMPTY -2
#define BEYOND_THE_LIST_SIZE -1

list *create_new_list() {
  list *new_list = malloc(sizeof(list));
  new_list->head = NULL;
  return new_list;
}

int count(list *list) {
  int count = 0;

  node *curr = list->head;
  while (curr != NULL) {
    curr = curr->link;
    count++;
  }
  return count;
}

void app_to_top(list *list, int new_element) {
  node *new_node = malloc(sizeof(node));

  new_node->element = new_element;

  if (list->head == NULL) {
    new_node->link = NULL;
    list->head = new_node;

  } else {
    new_node->link = list->head;
    list->head = new_node;
  }
}

void app_to_end(list *list, int new_element) {
  node *new_node = malloc(sizeof(node));

  new_node->element = new_element;

  if (list->head == NULL) {
    new_node->link = NULL;
    list->head = new_node;
  } else {
    node *curr = list->head;

    while (curr->link != NULL)
      curr = curr->link;

    new_node->link = NULL;
    curr->link = new_node;
  }
}

int app(list *list, int new_element, int number) {

  if (number == 1) {
    app_to_top(list, new_element);
    return SUCCESSFUL_COMPLETION;

  } else if (number == count(list) + 1) {
    app_to_end(list, new_element);
    return SUCCESSFUL_COMPLETION;

  } else if (count(list) < number || number <= 0) {
    return BEYOND_THE_LIST_SIZE;

  } else {
    node *new_node = malloc(sizeof(node));
    new_node->element = new_element;
    node *curr = list->head;

    for (int i = 0; i < number - 2; i++)
      curr = curr->link;

    new_node->link = curr->link;
    curr->link = new_node;
    return SUCCESSFUL_COMPLETION;
  }
}

int remove_node(list *list, int number) {
  node *curr = list->head;

  if (count(list) == 0) {
    return LIST_IS_EMPTY;

  } else if (count(list) < number || number <= 0) {
    return BEYOND_THE_LIST_SIZE;

  } else if (number == 1) {
    list->head = curr->link;
    return SUCCESSFUL_COMPLETION;

  } else {
    return SUCCESSFUL_COMPLETION;

    for (int i = 0; i < number - 2; i++)
      curr = curr->link;
    node *node_to_delete = curr->link;
    curr->link = curr->link->link;
    free(node_to_delete);
  }
}

int find_element(list *list, int number, int *exit_status) {
  if (count(list) < number || number <= 0) {
    *exit_status = BEYOND_THE_LIST_SIZE;
  } else {
    *exit_status = SUCCESSFUL_COMPLETION;

    node *curr = list->head;
    for (int i = 0; i < number - 1; i++)
      curr = curr->link;
    return curr->element;
  }
}

void delete_list(list *list) {
  node *curr = list->head;
  while (curr != NULL) {
    node *node_to_delete = curr;
    curr = curr->link;
    free(node_to_delete);
  }
  free(list);
}
