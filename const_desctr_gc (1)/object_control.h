#include "../pool_allocator/pool_allocator.h"

#define SUCCESS 0
#define MEMORY_ALLOC_ERROR -1
#define MEMORY_SIZE_ERROR -2

typedef struct {
  void *(*allocate)(void *context, size_t size);
  void (*deallocate)(void *ptr, void *context);
  void *context;
} memory_context;

typedef struct {
  void *object;
  void *(*construct)(memory_context *mem_ctx, size_t size);
  void (*destruct)(memory_context *mem_ctx, void *object);
  memory_context *mem_ctx;
} object_control;

int object_create(object_control *obj_control, size_t obj_size,
                  void *(*construct)(memory_context *mem_ctx, size_t size),
                  void (*destruct)(memory_context *mem_ctx, void *object),
                  memory_context *mem_ctx);
int object_destroy(object_control *obj_control);
