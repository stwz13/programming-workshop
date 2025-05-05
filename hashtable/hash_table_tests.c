#include "hash_table.h"
#include <assert.h>

void test_init_table() {
  void *buffer = malloc(1024);

  pool_allocator small_allocator;
  pool_allocator allocator;
  pool_allocator *null_allocator = NULL;

  init_pool_allocator(&allocator, buffer, 1024, 10 * sizeof(hash_node));

  hash_table table;
  hash_table *null_table = NULL;

  assert(hashtable_init(&table, 10, null_allocator) ==
         ALLOCATOR_ALLOCATION_ERROR);

  assert(hashtable_init(null_table, 10, &allocator) ==
         ALLOCATOR_ALLOCATION_ERROR);

  assert(hashtable_init(&table, 0, &allocator) == SIZE_ERROR);

  assert(hashtable_init(&table, 10, &allocator) == SUCCESS);

  assert(table.capacity == 10);
  assert(table.allocator == &allocator);
  assert(table.count_of_nodes == 0);
  assert(table.hash_nodes != NULL);

  for (int i = 0; i < table.capacity; i++) {
    assert(table.hash_nodes[i].element == NULL);
    assert(table.hash_nodes[i].key == NULL);
  }
  free(buffer);
}

void test_insert() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, 3 * sizeof(hash_node));

  hash_table table;
  hash_table *null_table = NULL;
  const char *null_key = NULL;
  void *null_value = NULL;

  assert(hashtable_insert(null_table, null_key, null_value) ==
         ALLOCATOR_ALLOCATION_ERROR);

  assert(hashtable_init(&table, 3, &allocator) == SUCCESS);

  int value1 = 13;
  assert(hashtable_insert(&table, "key1", null_value) ==
         ALLOCATOR_ALLOCATION_ERROR);
  assert(hashtable_insert(&table, null_key, &value1) ==
         ALLOCATOR_ALLOCATION_ERROR);
  assert(hashtable_insert(null_table, "key1", &value1) ==
         ALLOCATOR_ALLOCATION_ERROR);

  assert(hashtable_insert(&table, "key1", &value1) == SUCCESS);
  assert(table.count_of_nodes == 1);

  long int value2 = 1335789;
  assert(hashtable_insert(&table, "key2", &value2) == SUCCESS);
  assert(table.count_of_nodes == 2);

  char *value3 = "thirteen";

  assert(hashtable_insert(&table, "key3", value3) == SUCCESS);
  assert(table.count_of_nodes == 3);

  int limit_value = 1;

  assert(hashtable_insert(&table, "key4", &limit_value) == SIZE_ERROR);

  assert(*(int *)hashtable_get(&table, "key1") == 13);

  assert(*(long int *)hashtable_get(&table, "key2") == 1335789);

  assert(hashtable_get(&table, "key3") == "thirteen");

  int change_value = 3;

  assert(hashtable_insert(&table, "key3", &change_value) == SUCCESS);
  assert(*(int *)hashtable_get(&table, "key3") == 3);

  free(buffer);
}

void test_get() {

  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, 3 * sizeof(hash_node));

  hash_table table;
  const char *null_key = NULL;
  hash_table *null_table = NULL;
  assert(hashtable_init(&table, 3, &allocator) == SUCCESS);

  assert(hashtable_get(null_table, "key") == NULL);
  assert(hashtable_get(null_table, null_key) == NULL);
  assert(hashtable_get(&table, null_key) == NULL);
  assert(hashtable_get(&table, "key") == NULL);

  int value1 = 13;
  assert(hashtable_insert(&table, "key1", &value1) == SUCCESS);
  assert(*(int *)hashtable_get(&table, "key1") == 13);
  assert(hashtable_get(&table, "a_non-existing_key") == NULL);

  free(buffer);
}

void test_del() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, 3 * sizeof(hash_node));

  hash_table table;
  assert(hashtable_init(&table, 3, &allocator) == SUCCESS);
  hash_table *null_table = NULL;

  assert(hashtable_del(null_table, "key1") == ALLOCATOR_ALLOCATION_ERROR);
  assert(hashtable_del(&table, "key1") == SIZE_ERROR);

  int value1 = 13;
  long int value2 = 1335789;
  char *value3 = "thirteen";

  assert(hashtable_insert(&table, "key1", &value1) == SUCCESS);
  assert(hashtable_insert(&table, "key2", &value2) == SUCCESS);
  assert(hashtable_insert(&table, "key3", value3) == SUCCESS);

  assert(hashtable_del(&table, "key4") == KEY_IS_NOT_FOUND);

  assert(hashtable_del(&table, "key1") == SUCCESS);
  assert(hashtable_get(&table, "key1") == NULL);

  assert(hashtable_del(&table, "key2") == SUCCESS);
  assert(hashtable_get(&table, "key2") == NULL);

  assert(hashtable_del(&table, "key3") == SUCCESS);
  assert(hashtable_get(&table, "key3") == NULL);

  int change_value = 1;

  assert(hashtable_insert(&table, "key1", &change_value) == SUCCESS);
  assert(*(int *)hashtable_get(&table, "key1") == 1);

  free(buffer);
}

void test_free() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, 3 * sizeof(hash_node));

  hash_table table;
  assert(hashtable_init(&table, 3, &allocator) == SUCCESS);
  hash_table *null_table = NULL;

  assert(hashtable_free(null_table) == ALLOCATOR_ALLOCATION_ERROR);
  int value1 = 13;
  long int value2 = 1335789;
  char *value3 = "thirteen";

  assert(hashtable_insert(&table, "key1", &value1) == SUCCESS);
  assert(hashtable_insert(&table, "key2", &value2) == SUCCESS);
  assert(hashtable_insert(&table, "key3", value3) == SUCCESS);

  assert(hashtable_free(&table) == SUCCESS);

  assert(table.hash_nodes == NULL);
  assert(table.count_of_nodes == 0);
  assert(table.capacity == 0);
  assert(table.allocator == NULL);

  free(buffer);
}
int main() {
  test_init_table();
  test_insert();
  test_get();
  test_del();
  test_free();
  return 0;
}
