#include "../pool_allocator/pool_allocator.h"
#include <string.h>

#define EMPTY 3
#define DELETED 2
#define INITIALIZATED 1

#define SUCCESS 0
#define ALLOCATOR_ALLOCATION_ERROR -1
#define SIZE_ERROR -2
#define STR_ERROR -3
#define KEY_IS_NOT_FOUND -4

typedef struct {
  char *key;
  void *element;
  int is_init;
} hash_node;

typedef struct {
  hash_node *hash_nodes;
  size_t capacity;
  size_t count_of_nodes;
  size_t size_of_element;
  pool_allocator *allocator;
} hash_table;

int hashtable_init(hash_table *table, size_t capacity,
                   pool_allocator *allocator, size_t size_of_element);
int hashtable_insert(hash_table *table, const char *key, void *value);
void *hashtable_get(hash_table *table, const char *key);
int hashtable_del(hash_table *table, const char *key);
int hashtable_free(hash_table *table);
