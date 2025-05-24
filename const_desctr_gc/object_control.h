#include "../pool_allocator/pool_allocator.h"

#define SUCCESS 0
#define MEMORY_ALLOC_ERROR -1
#define MEMORY_SIZE_ERROR -2

typedef struct {
  void *object;
  void *(*construct)(pool_allocator *allocator);
  void (*destruct)(pool_allocator *allocator, void *object);
  pool_allocator *allocator;
} object_control;

int object_create(object_control *obj_control, size_t obj_size,
                  void *(*construct)(pool_allocator *allocator),
                  void (*destruct)(pool_allocator *allocator, void *object),
                  pool_allocator *allocator);
int object_destroy(object_control *obj_control);
