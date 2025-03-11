#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
  int *elements;
  int max_size;
  int number_of_elements;
} Stack;
Stack *create_stack(int size_of_stack) {
  struct Stack *stack = malloc(sizeof(Stack));
  stack->elements = malloc(size_of_stack * sizeof(int));
  stack->number_of_elements = 0;
  stack->max_size = size_of_stack;
  return stack;
}
void expand_stack(Stack *stack) {
  stack->max_size = 2 * stack->max_size;
  stack->elements = realloc(stack->elements, stack->max_size * sizeof(int));
}
void push(Stack *stack, int new_element) {
  if (stack->max_size < stack->number_of_elements + 1) {
    printf("Stack is full. Memory is being added.\n");
    expand_stack(stack);
  }
  stack->elements[stack->number_of_elements] = new_element;
  stack->number_of_elements++;
}
int is_empty(Stack *stack) { return (stack->number_of_elements == 0); }
int pop(Stack *stack) {
  if (is_empty(stack) == 1) {
    printf("Stack is empty\n");
    exit(EXIT_FAILURE);
  } else {
    int last_element = stack->elements[stack->number_of_elements - 1];
    stack->number_of_elements--;
    return last_element;
  }
}
void delete_stack(Stack *stack) {
  free(stack->elements);
  free(stack);
}
void print(Stack *stack) {
  for (int i = 0; i < stack->number_of_elements; i++) {
    printf("%d\n", stack->elements[i]);
  }
}