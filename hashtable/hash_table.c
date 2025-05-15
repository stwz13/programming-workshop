#include "hash_table.h"

int hashtable_init(hash_table *table, size_t capacity,
                   pool_allocator *allocator, size_t size_of_element) {
  if (!table || !allocator)
    return ALLOCATOR_ALLOCATION_ERROR;

  if (size_of_element == 0 || capacity == 0 ||
      allocator->count_of_blocks * allocator->block_size <
          capacity * sizeof(hash_node))
    return SIZE_ERROR;

  table->allocator = allocator;
  table->capacity = capacity;
  table->count_of_nodes = 0;
  table->size_of_element = size_of_element;

  table->hash_nodes = pool_alloc(allocator);

  if (!table->hash_nodes)
    return ALLOCATOR_ALLOCATION_ERROR;

  for (int i = 0; i < capacity; i++) {
    table->hash_nodes[i].element = NULL;
    table->hash_nodes[i].key = NULL;
    table->hash_nodes[i].is_init = EMPTY;
  }
  return SUCCESS;
}

int hash_string(const char *str) {
  if (!str)
    return STR_ERROR;
  int hash_value = 5381;
  int current_char;

  while (*str) {
    current_char = *str;
    str++;
    hash_value = hash_value * 33 + current_char;
  }

  return hash_value;
}

int hashtable_insert(hash_table *table, const char *key, void *value) {
  if (!table || !key || !value)
    return ALLOCATOR_ALLOCATION_ERROR;

  int index = hash_string(key) % table->capacity;

  for (int i = 0; i < table->capacity; i++) {
    int curr_index = (index + i) % table->capacity;

    if (table->hash_nodes[curr_index].is_init != INITIALIZATED) {

      table->hash_nodes[curr_index].key = pool_alloc(table->allocator);
      table->hash_nodes[curr_index].element = pool_alloc(table->allocator);


      if (!table->hash_nodes[curr_index].key || !table->hash_nodes[curr_index].element)
        return ALLOCATOR_ALLOCATION_ERROR;

      strcpy(table->hash_nodes[curr_index].key, key);

      memcpy(table->hash_nodes[curr_index].element, value,
          table->size_of_element);

      table->hash_nodes[curr_index].is_init = INITIALIZATED;
      table->count_of_nodes++;

      return SUCCESS;

    } else if (strcmp(table->hash_nodes[curr_index].key, key) == 0) {

      memcpy(table->hash_nodes[curr_index].element, value,
             table->size_of_element);
      return SUCCESS;
    }

  }
  return SIZE_ERROR;
}

void *hashtable_get(hash_table *table, const char *key) {
  if (!table || !key)
    return NULL;

  if (table->count_of_nodes == 0)
    return NULL;

  int index = hash_string(key) % table->capacity;

  for (int i = 0; i < table->capacity; i++) {
    int curr_index = (index + i) % table->capacity;

    if (table->hash_nodes[curr_index].is_init == EMPTY)
      return NULL;
    if (table->hash_nodes[curr_index].is_init == DELETED)
      continue;
    if (strcmp(table->hash_nodes[curr_index].key, key) == 0)
      return table->hash_nodes[curr_index].element;
  }
  return NULL;
}

int hashtable_del(hash_table *table, const char *key) {
  if (!table || !key)
    return ALLOCATOR_ALLOCATION_ERROR;

  if (table->count_of_nodes == 0)
    return SIZE_ERROR;
  int index = hash_string(key) % table->capacity;

  for (int i = 0; i < table->capacity; i++) {

    int curr_index = (index + i) % table->capacity;

    if (table->hash_nodes[curr_index].is_init == EMPTY)
      return KEY_IS_NOT_FOUND;

    if (table->hash_nodes[curr_index].is_init == DELETED)
      continue;
    if (strcmp(table->hash_nodes[curr_index].key, key) == 0) {

      pool_free(table->allocator, table->hash_nodes[curr_index].key);

      table->hash_nodes[curr_index].key = NULL;
      table->hash_nodes[curr_index].is_init = DELETED;
      table->count_of_nodes--;

      return SUCCESS;
    }
  }
  return KEY_IS_NOT_FOUND;
}

int hashtable_free(hash_table *table) {
  if (!table)
    return ALLOCATOR_ALLOCATION_ERROR;
  for (int i = 0; i < table->capacity; i++) {
    pool_free(table->allocator, table->hash_nodes[i].key);
    table->hash_nodes[i].key = NULL;
    table->hash_nodes[i].element = NULL;
    table->hash_nodes[i].is_init = EMPTY;
  }

  pool_free(table->allocator, table->hash_nodes);

  table->hash_nodes = NULL;
  table->capacity = 0;
  table->count_of_nodes = 0;
  table->allocator = NULL;
  table->size_of_element = 0;

  return SUCCESS;
}
