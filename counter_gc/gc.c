#include "gc.h"

int ref_create(ref_count_t **ref_object, memory_context mem_ctx, void *object) {
  if (!mem_ctx.context || !mem_ctx.allocate || !mem_ctx.deallocate || !object ||
      !ref_object)
    return ALLOCATION_ERROR;

  ref_count_t *new_ref = mem_ctx.allocate(sizeof(ref_count_t), mem_ctx.context);

  if (!new_ref)
    return ALLOCATION_ERROR;

  new_ref->dependent_refs = NULL;
  new_ref->mem_ctx = mem_ctx;
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

int ref_add_dependent_obj(ref_count_t *curr_ref, ref_count_t **new_ref) {
  if (!curr_ref || !new_ref)
    return ALLOCATION_ERROR;

  dependent_ref *new_dep_ref = curr_ref->mem_ctx.allocate(
      sizeof(dependent_ref), curr_ref->mem_ctx.context);
  if (!new_dep_ref)
    return ALLOCATION_ERROR;

  new_dep_ref->ref = new_ref;
  new_dep_ref->next = curr_ref->dependent_refs;
  curr_ref->dependent_refs = new_dep_ref;

  ref_increase(*new_ref);
  return SUCCESSFUL_COMPLETION;
}

int ref_reduce(ref_count_t **ref) {
  if (!ref || !*ref)
    return ALLOCATION_ERROR;

  ref_count_t *curr_ref = *ref;
  curr_ref->count--;
  if (curr_ref->count == 0) {

    if (curr_ref->object == NULL)
      return ALLOCATION_ERROR;

    dependent_ref *dep = curr_ref->dependent_refs;

    while (dep) {

      if (dep->ref)
        ref_reduce(dep->ref);

      dependent_ref *next = dep->next;

      curr_ref->mem_ctx.deallocate(dep, curr_ref->mem_ctx.context);
      dep = next;
    }

    curr_ref->dependent_refs = NULL;
    curr_ref->mem_ctx.deallocate(curr_ref->object, curr_ref->mem_ctx.context);
    curr_ref->object = NULL;
    curr_ref->mem_ctx.deallocate(curr_ref, curr_ref->mem_ctx.context);
    *ref = NULL;
  }
  return SUCCESSFUL_COMPLETION;
}
