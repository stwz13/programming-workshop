#include "../pool_allocator/pool_allocator.h"
#include <string.h>

typedef struct {
  void **head_of_elements;
  size_t capacity;
  size_t length;
  pool_allocator *allocator;
} array_list;

#define SUCCESSFUL_RESULT 0

#define ALLOCATION_ERROR -1
#define BEYOND_LIST_LENGTH -2
#define MEMORY_SIZE_ERROR -4

#define DEFAULT_CAPACITY 8

int arraylist_init(array_list *list, pool_allocator *alloc);
int arraylist_expand(array_list *list);
int arraylist_add(array_list *list, void *data, size_t index);
void *arraylist_get(array_list *list, size_t index);
int arraylist_del(array_list *list, size_t index);
int arraylist_free(array_list *list);
