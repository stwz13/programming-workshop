#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCSSFUL_COMPLETION 0;
#define STACK_OVERFLEW -1
#define STACK_IS_EMPTY -2

stack_t *create_stack(int size_of_stack) {
  stack_t *stack = malloc(sizeof(stack_t));
  stack->elements = malloc(size_of_stack * sizeof(int));
  stack->number_of_elements = 0;
  stack->max_size = size_of_stack;
  return stack;
}

void expand_stack(stack_t *stack) {
  stack->max_size = 2 * stack->max_size;
  stack->elements = realloc(stack->elements, stack->max_size * sizeof(int));
}

void push(stack_t *stack, int new_element, int *completion) {
  if (stack->max_size < stack->number_of_elements + 1) {
    *completion = STACK_OVERFLEW;
  } else {
    *completion = SUCCSSFUL_COMPLETION;
    stack->elements[stack->number_of_elements] = new_element;
    stack->number_of_elements++;
  }
}

int is_empty(stack_t *stack) { return (stack->number_of_elements == 0); }
int pop(stack_t *stack, int *completion) {
  if (is_empty(stack)) {
    *completion = STACK_IS_EMPTY;
    return -1;
  } else {
    int last_element = stack->elements[stack->number_of_elements - 1];
    stack->number_of_elements--;
    return last_element;
  }
}

void delete_stack(stack_t *stack) {
  free(stack->elements);
  free(stack);
}
