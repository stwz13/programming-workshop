#include "task4.h"
#include <assert.h>
#include <stdio.h>
void test1() {
  struct List *new_list = create_new_list();
  app_to_top(new_list, 5);
  app_to_end(new_list, 7);
  app(new_list, 9, 1);
  assert(count(new_list) == 3 && find_element(new_list, 1) == 9 &&
         find_element(new_list, 2) == 5 && find_element(new_list, 3) == 7);
  remove_node(new_list, 3);
  assert(count(new_list) == 2 && find_element(new_list, 1) == 9 &&
         find_element(new_list, 2) == 5);
  remove_node(new_list, 1);
  assert(count(new_list) == 1 && find_element(new_list, 1) == 5);
  remove_node(new_list, 1);
  assert(count(new_list) == 0);
  delete_list(new_list);
}
int main() {
  test1();
  return 0;
}
