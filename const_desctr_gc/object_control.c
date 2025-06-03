#include "object_control.h"

void *default_construct(memory_context *mem_ctx, size_t size) {
  return mem_ctx->allocate(mem_ctx->context, size);
}

void default_destruct(memory_context *mem_ctx, void *object) {
  mem_ctx->deallocate(object, mem_ctx->context);
}

int object_create(object_control *obj_control, size_t obj_size,
                  void *(*construct)(memory_context *mem_ctx, size_t size),
                  void (*destruct)(memory_context *mem_ctx, void *object),
                  memory_context *mem_ctx) {

  if (!obj_control || !mem_ctx)
    return MEMORY_ALLOC_ERROR;

  if (obj_size == 0)
    return MEMORY_SIZE_ERROR;

  if (!mem_ctx->allocate || !mem_ctx->deallocate)
    return MEMORY_ALLOC_ERROR;

  obj_control->mem_ctx = mem_ctx;
  obj_control->construct = construct ? construct : default_construct;
  obj_control->destruct = destruct ? destruct : default_destruct;
  mem_ctx->deallocate;
  obj_control->object = obj_control->construct(obj_control->mem_ctx, obj_size);

  if (!obj_control->object)
    return MEMORY_ALLOC_ERROR;

  return SUCCESS;
}

int object_destroy(object_control *obj_control) {
  if (!obj_control)
    return MEMORY_ALLOC_ERROR;

  obj_control->destruct(obj_control->mem_ctx, obj_control->object);

  obj_control->mem_ctx = NULL;
  obj_control->construct = NULL;
  obj_control->destruct = NULL;
  obj_control->object = NULL;

  return SUCCESS;
}
