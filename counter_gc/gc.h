#include "../pool_allocator/pool_allocator.h"
#include <stdlib.h>

#define ALLOCATION_ERROR -1

typedef struct {
  void *(*allocate)(size_t size, void *context);
  void (*deallocate)(void *ptr, void *context);
  void *context;
} memory_context;

typedef struct dependent_ref dependent_ref;

typedef struct {
  size_t count;
  void *object;
  dependent_ref *dependent_refs;
  memory_context mem_ctx;
} ref_count_t;

struct dependent_ref {
  ref_count_t **ref;
  dependent_ref *next;
};

int ref_create(ref_count_t **ref_object, memory_context mem_ctx, void *object);
int ref_increase(ref_count_t *ref);
int ref_reduce(ref_count_t **ref);
int ref_add_dependent_obj(ref_count_t *curr_ref, ref_count_t **new_ref);
