#include "array.h"
#include <assert.h>

void test_init() {

  void *memory = malloc(1024);

  pool_allocator alloc;

  init_pool_allocator(&alloc, memory, 1024, 8 * sizeof(void *));
  array_list list;

  assert(arraylist_init(NULL, NULL) == ALLOCATION_ERROR);
  assert(arraylist_init(NULL, &alloc) == ALLOCATION_ERROR);
  assert(arraylist_init(&list, NULL) == ALLOCATION_ERROR);

  assert(arraylist_init(&list, &alloc) == SUCCESSFUL_RESULT);
  assert(list.allocator == &alloc);
  assert(list.capacity == DEFAULT_CAPACITY);
  assert(list.head_of_elements != NULL);
  assert(list.length == 0);

  for (int i = 0; i < list.capacity; i++) {
    assert(list.head_of_elements[i] == NULL);
  }

  arraylist_free(&list);
  free(memory);
}

void test_expand() {

  void *memory = malloc(1024);
  pool_allocator alloc;
  array_list list;

  init_pool_allocator(&alloc, memory, 1024, 256);
  assert(arraylist_init(&list, &alloc) == SUCCESSFUL_RESULT);

  assert(arraylist_expand(NULL) == ALLOCATION_ERROR);

  int value = 1;
  int begin_capacity = list.capacity;

  for (int i = 0; i < list.capacity; i++) {
    assert(arraylist_add(&list, &value, i) == SUCCESSFUL_RESULT);
  }

  int begin_length = list.length;

  assert(arraylist_expand(&list) == SUCCESSFUL_RESULT);
  assert(list.capacity == 2 * begin_capacity);
  assert(list.length == begin_length);

  for (int i = 0; i < list.length; i++) {
    assert(*(int *)arraylist_get(&list, i) == value);
  }

  for (int i = list.length; i < list.capacity; i++) {
    assert(arraylist_get(&list, i) == NULL);
  }

  arraylist_free(&list);
  free(memory);
}

void test_add() {

  void *memory = malloc(1024);
  pool_allocator alloc;
  array_list list;
  init_pool_allocator(&alloc, memory, 1024, 256);
  assert(arraylist_init(&list, &alloc) == SUCCESSFUL_RESULT);

  char char_new_element = 'a';
  assert(arraylist_add(NULL, &char_new_element, 0) == ALLOCATION_ERROR);
  assert(arraylist_add(&list, NULL, 0) == ALLOCATION_ERROR);

  assert(arraylist_add(&list, &char_new_element, 0) == SUCCESSFUL_RESULT);
  assert(list.length == 1);

  int int_new_element = 1;
  assert(arraylist_add(&list, &int_new_element, 2) == BEYOND_LIST_LENGTH);

  assert(arraylist_add(&list, &int_new_element, 0) == SUCCESSFUL_RESULT);

  assert(list.length == 2);

  assert(*(int *)arraylist_get(&list, 0) == int_new_element);
  assert(*(char *)arraylist_get(&list, 1) == char_new_element);

  char *string_new_element = "abc";
  assert(arraylist_add(&list, string_new_element, 2) == SUCCESSFUL_RESULT);

  assert(arraylist_get(&list, 2) == string_new_element);
  assert(list.length == 3);

  for (int i = list.length - 1; i < list.capacity; i++) {
    assert(arraylist_add(&list, &int_new_element, i) == SUCCESSFUL_RESULT);
    assert(*(int *)arraylist_get(&list, i) == int_new_element);
  }

  assert(arraylist_add(&list, &char_new_element, list.length) ==
         SUCCESSFUL_RESULT);

  int middle_element = -1;

  assert(arraylist_add(&list, &middle_element, 2) == SUCCESSFUL_RESULT);

  assert(*(int *)arraylist_get(&list, 2) == middle_element);

  arraylist_free(&list);
  free(memory);
}

void test_get() {
  void *memory = malloc(1024);
  pool_allocator alloc;
  array_list list;
  init_pool_allocator(&alloc, memory, 1024, 256);

  assert(arraylist_init(&list, &alloc) == SUCCESSFUL_RESULT);
  assert(arraylist_get(&list, 127) == NULL);
  assert(arraylist_get(NULL, 0) == NULL);

  assert(arraylist_get(&list, 0) == NULL);
  char char_new_element = 'a';
  for (int i = 0; i < list.capacity; i++) {
    assert(arraylist_add(&list, &char_new_element, i) == SUCCESSFUL_RESULT);
  }

  for (int i = 0; i < list.length; i++) {
    assert(*(char *)arraylist_get(&list, i) == char_new_element);
  }
  int int_new_element = 7;
  assert(arraylist_add(&list, &int_new_element, list.length) ==
         SUCCESSFUL_RESULT);
  assert(*(int *)arraylist_get(&list, list.length - 1) == int_new_element);

  arraylist_free(&list);
  free(memory);
}

void test_del() {
  void *memory = malloc(1024);
  pool_allocator alloc;
  array_list list;
  init_pool_allocator(&alloc, memory, 1024, 256);

  assert(arraylist_init(&list, &alloc) == SUCCESSFUL_RESULT);
  assert(arraylist_del(NULL, 0) == ALLOCATION_ERROR);
  assert(arraylist_del(&list, 0) == BEYOND_LIST_LENGTH);

  int first_element = 1;
  char second_element = '2';
  int third_element = 3;

  assert(arraylist_add(&list, &first_element, list.length) ==
         SUCCESSFUL_RESULT);
  assert(arraylist_add(&list, &second_element, list.length) ==
         SUCCESSFUL_RESULT);
  assert(arraylist_add(&list, &third_element, list.length) ==
         SUCCESSFUL_RESULT);

  assert(list.length == 3);

  assert(arraylist_del(&list, 0) == SUCCESSFUL_RESULT);
  assert(list.length == 2);
  assert(*(char *)arraylist_get(&list, 0) == '2');

  int first_element_after_del = 4;
  assert(arraylist_add(&list, &first_element_after_del, 0) ==
         SUCCESSFUL_RESULT);

  assert(list.length == 3);

  assert(*(int *)arraylist_get(&list, 0) == 4);
  assert(*(char *)arraylist_get(&list, 1) == '2');
  assert(*(int *)arraylist_get(&list, 2) == 3);

  assert(arraylist_del(&list, 0) == SUCCESSFUL_RESULT);
  assert(arraylist_del(&list, 0) == SUCCESSFUL_RESULT);
  assert(arraylist_del(&list, 0) == SUCCESSFUL_RESULT);

  assert(list.length == 0);

  assert(arraylist_get(&list, 0) == NULL);

  arraylist_free(&list);
  free(memory);
}

void test_free() {
  void *memory = malloc(1024);
  pool_allocator alloc;
  array_list list;
  init_pool_allocator(&alloc, memory, 1024, 256);

  assert(arraylist_init(&list, &alloc) == SUCCESSFUL_RESULT);

  assert(arraylist_free(NULL) == ALLOCATION_ERROR);

  int element = 5;
  for (int i = 0; i < 3; i++) {
    assert(arraylist_add(&list, &element, 0) == SUCCESSFUL_RESULT);
  }

  assert(list.length == 3);

  assert(arraylist_free(&list) == SUCCESSFUL_RESULT);
  assert(list.allocator == NULL);
  assert(list.capacity == 0);
  assert(list.length == 0);
  assert(list.head_of_elements == NULL);

  free(memory);
}
int main() {
  test_init();
  test_expand();
  test_add();
  test_get();
  test_del();
  test_free();
  return 0;
}
