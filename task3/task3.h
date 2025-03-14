struct Stack *create_stack(int size_of_stack);
void expand_stack(struct Stack *stack);
void push(struct Stack *stack, int new_element);
int is_empty(struct Stack *stack);
int pop(struct Stack *stack);
void delete_stack(struct Stack *stack);
