typedef struct {
  int *elements;
  int max_size;
  int number_of_elements;
} stack_t;
stack_t *create_stack(int size_of_stack);
void expand_stack(stack_t *stack);
void push(stack_t *stack, int new_element, int *completion);
int is_empty(stack_t *stack);
int pop(stack_t *stack, int *completion);
void delete_stack(stack_t *stack);
