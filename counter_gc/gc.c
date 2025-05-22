#include "gc.h"

int ref_create(ref_count_t **ref_object, pool_allocator *allocator,
               void *object) {
  if (!allocator || !object || !ref_object)
    return ALLOCATION_ERROR;

  ref_count_t *new_ref = pool_alloc(allocator);
  new_ref->allocator = allocator;
  new_ref->object = object;
  new_ref->count = 1;

  *ref_object = new_ref;

  return SUCCESSFUL_COMPLETION;
}

int ref_increase(ref_count_t *ref) {
  if (!ref)
    return ALLOCATION_ERROR;
  ref->count++;
  return SUCCESSFUL_COMPLETION;
}

int ref_reduce(ref_count_t **ref) {
  if (!ref)
    return ALLOCATION_ERROR;

  ref_count_t *curr_ref = *ref;
  curr_ref->count--;
  if (curr_ref->count == 0) {

    if (curr_ref->object == NULL)
      return ALLOCATION_ERROR;

    pool_free(curr_ref->allocator, curr_ref->object);
    curr_ref->object = NULL;
    pool_free(curr_ref->allocator, curr_ref);
    *ref = NULL;
  }
  return SUCCESSFUL_COMPLETION;
}
