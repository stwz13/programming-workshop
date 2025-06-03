#include "object_control.h"
#include <assert.h>
#include <string.h>

void *test_int_constr(memory_context *mem_ctx, size_t size) {
  void *obj = mem_ctx->allocate(mem_ctx->context, sizeof(int));

  memset(obj, 0, sizeof(int));

  return obj;
}

void test_destr(memory_context *mem_ctx, void *obj) {
  mem_ctx->deallocate(mem_ctx, obj);
}

void *pool_allocator_alloc(void *context, size_t size) {
  return pool_alloc((pool_allocator *)context);
}

void pool_allocator_free(void *ptr, void *context) {
  pool_free((pool_allocator *)context, ptr);
}

void test_create() {
  void *memory = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, memory, 1024, 64);

  memory_context pool_ctx = {.allocate = pool_allocator_alloc,
                             .deallocate = pool_allocator_free,
                             .context = &allocator};

  object_control int_obj;

  assert(object_create(&int_obj, sizeof(int), test_int_constr, NULL,
                       &pool_ctx) == SUCCESS);

  assert(int_obj.construct == test_int_constr);

  assert(int_obj.mem_ctx == &pool_ctx);
  assert(int_obj.object != NULL);
  assert(*(int *)int_obj.object == 0);
  assert(object_destroy(&int_obj) == SUCCESS);

  object_control new_obj;

  assert(object_create(&new_obj, sizeof(int), test_int_constr, test_destr,
                       &pool_ctx) == SUCCESS);

  assert(new_obj.mem_ctx == &pool_ctx);
  assert(new_obj.construct == test_int_constr);
  assert(new_obj.destruct == test_destr);

  assert(new_obj.object != NULL);
  assert(object_destroy(&new_obj) == SUCCESS);

  object_control default_obj;

  assert(object_create(&default_obj, sizeof(void *), NULL, NULL, NULL) ==
         MEMORY_ALLOC_ERROR);

  assert(object_create(&default_obj, sizeof(void *), NULL, NULL, &pool_ctx) ==
         SUCCESS);

  assert(default_obj.mem_ctx == &pool_ctx);
  assert(default_obj.object != NULL);

  assert(object_destroy(&default_obj) == SUCCESS);

  object_control *null_obj = NULL;
  assert(object_create(null_obj, sizeof(void *), NULL, NULL, &pool_ctx) ==
         MEMORY_ALLOC_ERROR);

  free(memory);
}

void test_destroy() {
  void *memory = malloc(1024);
  pool_allocator alloc;
  init_pool_allocator(&alloc, memory, 1024, 64);

  int count_of_destr = 0;
  object_control int_obj;
  memory_context pool_ctx = {.allocate = pool_allocator_alloc,
                             .deallocate = pool_allocator_free,
                             .context = &alloc};

  assert(object_create(&int_obj, sizeof(int), test_int_constr, test_destr,
                       &pool_ctx) == SUCCESS);
  assert(object_destroy(&int_obj) == SUCCESSFUL_COMPLETION);
  assert(int_obj.mem_ctx == NULL);
  assert(int_obj.construct == NULL);
  assert(int_obj.destruct == NULL);
  assert(int_obj.mem_ctx == NULL);

  object_control default_obj;
  assert(object_create(&default_obj, sizeof(void *), NULL, NULL, &pool_ctx) ==
         SUCCESS);
  assert(object_destroy(&default_obj) == SUCCESSFUL_COMPLETION);
  assert(default_obj.mem_ctx == NULL);
  assert(default_obj.construct == NULL);
  assert(default_obj.destruct == NULL);

  free(memory);
}
int main() {
  test_create();
  test_destroy();
  return 0;
}
