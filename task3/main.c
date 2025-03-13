#include "task3.h"
#include <assert.h>
#include <stdio.h>
void test1() {
  struct Stack *new_stack = create_stack(2);
  push(new_stack, 5);
  push(new_stack, 7);
  push(new_stack, 9);
  assert(is_empty(new_stack) == 0 && pop(new_stack) == 9);
  assert(is_empty(new_stack) == 0 && pop(new_stack) == 7);
  assert(is_empty(new_stack) == 0 && pop(new_stack) == 5);
  assert(is_empty(new_stack) == 1);
  delete_stack(new_stack);
}
int main() {
  test1();
  printf("The test was completed successfully\n");
  return 0;
}