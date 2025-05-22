#include "../pool_allocator/pool_allocator.h"
#include <stdlib.h>

#define ALLOCATION_ERROR -1
typedef struct {
  size_t count;
  void *object;
  pool_allocator *allocator;
} ref_count_t;

int ref_create(ref_count_t **ref_object, pool_allocator *allocator,
               void *object);
int ref_increase(ref_count_t *ref);
int ref_reduce(ref_count_t **ref);
