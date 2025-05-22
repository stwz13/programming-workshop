#include "gc.h"

int ref_create(ref_count_t *ref_object, pool_allocator *allocator,
               void *object) {
  if (!allocator || !object || !ref_object)
    return ALLOCATION_ERROR;

  ref_object->allocator = allocator;
  ref_object->object = object;
  ref_object->count = 1;

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
    ref->object = NULL;
    pool_free(ref->allocator, ref);
    ref->allocator = NULL;
  }
  return SUCCESSFUL_COMPLETION;
}
