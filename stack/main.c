#include "stack.h"
#include <assert.h>
void test1() {
  int completion;
  stack_t *new_stack = create_stack(3);
  push(new_stack, 5, &completion);
  assert(completion == 0);
  delete_stack(new_stack);
}

void test2() {
  int completion;
  stack_t *new_stack = create_stack(1);
  push(new_stack, 5, &completion);
  push(new_stack, 3, &completion);
  assert(completion == -1);
  delete_stack(new_stack);
}

void test3() {
  stack_t *new_stack = create_stack(0);
  assert(is_empty(new_stack));
  delete_stack(new_stack);
}

void test4() {
  int completion;
  stack_t *new_stack = create_stack(1);
  push(new_stack, 7, &completion);
  pop(new_stack, &completion);
  assert(completion == 0);
  delete_stack(new_stack);
}

void test5() {
  int completion;
  stack_t *new_stack = create_stack(0);
  pop(new_stack, &completion);
  assert(completion == -2);
  delete_stack(new_stack);
}
int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  return 0;
}
