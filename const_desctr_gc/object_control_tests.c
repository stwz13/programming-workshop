#include "object_control.h"
#include <assert.h>
#include <string.h>

void *test_int_constr(pool_allocator *alloc) {
  void *obj = pool_alloc(alloc);
  memset(obj, 0, sizeof(int));
  return obj;
}

void test_destr(pool_allocator *alloc, void *obj) { pool_free(alloc, obj); }

void test_create() {
  void *memory = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, memory, 1024, 64);

  object_control int_obj;

  assert(object_create(&int_obj, sizeof(int), test_int_constr, NULL,
                       &allocator) == SUCCESS);

  assert(int_obj.allocator == &allocator);
  assert(*(int *)int_obj.object == 0);
  assert(int_obj.object != NULL);

  assert(object_destroy(&int_obj) == SUCCESS);

  object_control default_obj;
  pool_allocator *null_allocator = NULL;

  assert(object_create(&default_obj, sizeof(void *), NULL, NULL,
                       null_allocator) == MEMORY_ALLOC_ERROR);

  assert(object_create(&default_obj, sizeof(void *), NULL, NULL, &allocator) ==
         SUCCESS);

  assert(default_obj.allocator == &allocator);
  assert(default_obj.object != NULL);

  assert(object_destroy(&default_obj) == SUCCESS);

  object_control *null_obj = NULL;
  assert(object_create(null_obj, sizeof(void *), NULL, NULL, &allocator) ==
         MEMORY_ALLOC_ERROR);

  free(memory);
}

void test_destroy() {
  void *memory = malloc(1024);
  pool_allocator alloc;
  init_pool_allocator(&alloc, memory, 1024, 64);

  int count_of_destr = 0;
  object_control int_obj;

  assert(object_create(&int_obj, sizeof(int), test_int_constr, test_destr,
                       &alloc) == SUCCESS);
  assert(object_destroy(&int_obj) == SUCCESSFUL_COMPLETION);
  assert(int_obj.allocator == NULL);
  assert(int_obj.construct == NULL);
  assert(int_obj.destruct == NULL);
  assert(int_obj.allocator == NULL);

  object_control default_obj;
  assert(object_create(&default_obj, sizeof(void *), NULL, NULL, &alloc) ==
         SUCCESS);
  assert(object_destroy(&default_obj) == SUCCESSFUL_COMPLETION);
  assert(default_obj.allocator == NULL);
  assert(default_obj.construct == NULL);
  assert(default_obj.destruct == NULL);
  assert(default_obj.allocator == NULL);

  free(memory);
}
int main() {
  test_create();
  test_destroy();
  return 0;
}
