#include <stdio.h>
#include <stdlib.h>

struct Stack {
  int *elements;
  int max_size;
  int number_of_elements;
};
struct Stack *create_stack(int size_of_stack) {
  struct Stack *stack = malloc(sizeof(struct Stack));
  stack->elements = malloc(size_of_stack * sizeof(int));
  stack->number_of_elements = 0;
  stack->max_size = size_of_stack;
  return stack;
}
void expand_stack(struct Stack *stack) {
  stack->max_size = 2 * stack->max_size;
  stack->elements = realloc(stack->elements, stack->max_size * sizeof(int));
}
void push(struct Stack *stack, int new_element) {
  if (stack->max_size < stack->number_of_elements + 1) {
    printf("Stack is full.Memory is being added.");
    expand_stack(stack);
  } else {
    stack->elements[stack->number_of_elements] = new_element;
    stack->number_of_elements++;
  }
}

int is_empty(struct Stack *stack) {
  if (stack->number_of_elements == 0) {
    return 1;
  } else
    return 0;
}
int pop(struct Stack *stack) {
  if (is_empty(stack) == 1) {
    return -1;
  } else {
    int last_element = stack->elements[stack->number_of_elements - 1];
    stack->number_of_elements--;
    return last_element;
  }
}
void delete_stack(struct Stack *stack) {
  free(stack->elements);
  free(stack);
}