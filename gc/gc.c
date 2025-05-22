#include "gc.h"

int ref_create(ref_count_t *ref_object, pool_allocator *allocator,
               void *object) {
  if (!allocator || !object || !ref_object)
    return ALLOCATION_ERROR;
  ref_count_t *new_ref = (ref_count_t *)pool_alloc(allocator);

  if (!new_ref)
    return ALLOCATION_ERROR;

  new_ref->allocator = allocator;
  new_ref->object = object;
  new_ref->count = 1;

  return SUCCESSFUL_COMPLETION;
}

int ref_increase(ref_count_t *ref) {
  if (!ref)
    return ALLOCATION_ERROR;
  ref->count++;
  return SUCCESSFUL_COMPLETION;
}

int ref_reduce(ref_count_t *ref) {
  if (!ref)
    return ALLOCATION_ERROR;

  ref->count--;
  if (ref->count == 0) {

    if (ref->object == NULL)
      return ALLOCATION_ERROR;

    pool_free(ref->allocator, ref->object);
    pool_free(ref->allocator, ref);
  }
  return SUCCESSFUL_COMPLETION;
}
