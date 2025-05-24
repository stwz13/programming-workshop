#include "object_control.h"

void *default_construct(pool_allocator *allocator) {
  return pool_alloc(allocator);
}

void default_destruct(pool_allocator *allocator, void *object) {
  pool_free(allocator, object);
}

int object_create(object_control *obj_control, size_t obj_size,
                  void *(*construct)(pool_allocator *allocator),
                  void (*destruct)(pool_allocator *allocator, void *object),
                  pool_allocator *allocator) {

  if (!obj_control || !allocator)
    return MEMORY_ALLOC_ERROR;

  if (obj_size == 0 || allocator->block_size < obj_size)
    return MEMORY_SIZE_ERROR;

  obj_control->allocator = allocator;
  obj_control->construct = construct ? construct : default_construct;
  obj_control->destruct = destruct ? destruct : default_destruct;
  obj_control->object = obj_control->construct(allocator);

  if (!obj_control->object)
    return MEMORY_ALLOC_ERROR;

  return SUCCESS;
}

int object_destroy(object_control *obj_control) {
  if (!obj_control)
    return MEMORY_ALLOC_ERROR;

  obj_control->destruct(obj_control->allocator, obj_control->object);

  obj_control->allocator = NULL;
  obj_control->construct = NULL;
  obj_control->destruct = NULL;
  obj_control->object = NULL;

  return SUCCESS;
}
