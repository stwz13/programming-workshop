#include "assert.h"
#include "list.h"
void test1() {
  int completion;
  list *new_list = create_new_list();

  app_to_end(new_list, 5);
  app_to_top(new_list, 3);
  find_element(new_list, -1, &completion);
  assert(count(new_list) == 2 && completion == -1);

  int element = find_element(new_list, 1, &completion);
  assert(count(new_list) == 2 && element == 3 && completion == 0);

  delete_list(new_list);
}

void test2() {
  int completion;
  list *new_list = create_new_list();

  remove_node(new_list, 1, &completion);
  assert(completion == -2);

  app_to_end(new_list, 5);
  remove_node(new_list, -5, &completion);
  assert(completion == -1);

  remove_node(new_list, 1, &completion);
  assert(completion == 0);

  delete_list(new_list);
}

void test3() {
  int completion;
  list *new_list = create_new_list();

  app(new_list, 5, 1, &completion);
  assert(completion == 0 && find_element(new_list, 1, &completion) == 5);

  app(new_list, 7, 2, &completion);
  assert(completion == 0 && find_element(new_list, 2, &completion) == 7);

  app(new_list, 9, 2, &completion);
  assert(completion == 0 && find_element(new_list, 2, &completion) == 9);

  app(new_list, 1, -1, &completion);
  assert(completion == -1);

  delete_list(new_list);
}

int main() {
  test1();
  test2();
  test3();
  return 0;
}
