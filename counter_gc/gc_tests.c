#include "assert.h"
#include "gc.h"

void *pool_alloc_test(size_t size, void *context) {
  return pool_alloc((pool_allocator *)context);
}

void pool_free_test(void *ptr, void *context) {
  pool_free((pool_allocator *)context, ptr);
}

void test_create_ref() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, sizeof(ref_count_t));

  memory_context null_context;
  null_context.allocate = NULL;
  null_context.deallocate = NULL;
  null_context.context = NULL;

  memory_context mem_cntxt;
  mem_cntxt.allocate = pool_alloc_test;
  mem_cntxt.deallocate = pool_free_test;
  mem_cntxt.context = &allocator;

  ref_count_t *new_ref;
  void *new_object1 = pool_alloc(&allocator);

  assert(ref_create(&new_ref, null_context, new_object1) == ALLOCATION_ERROR);
  assert(ref_create(&new_ref, mem_cntxt, new_object1) == SUCCESSFUL_COMPLETION);

  assert(new_ref->count = 1);
  assert(new_ref->dependent_refs == NULL);

  assert(new_ref->object == new_object1);

  assert(ref_reduce(&new_ref) == SUCCESSFUL_COMPLETION);
  assert(new_ref == NULL);
  ref_count_t *null_ref;
  void *null_object = NULL;

  assert(ref_create(&null_ref, mem_cntxt, null_object) == ALLOCATION_ERROR);

  assert(ref_create(NULL, mem_cntxt, null_object) == ALLOCATION_ERROR);

  free(buffer);
}

void test_ref_increase() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, sizeof(ref_count_t));

  memory_context mem_cntxt;
  mem_cntxt.allocate = pool_alloc_test;
  mem_cntxt.deallocate = pool_free_test;
  mem_cntxt.context = &allocator;

  assert(ref_increase(NULL) == ALLOCATION_ERROR);

  void *object = pool_alloc(&allocator);
  ref_count_t *ref_object;
  assert(ref_create(&ref_object, mem_cntxt, object) == SUCCESSFUL_COMPLETION);

  assert(ref_increase(ref_object) == SUCCESSFUL_COMPLETION);
  assert(ref_object->count == 2);

  ref_reduce(&ref_object);
  assert(ref_object->count == 1);

  assert(ref_reduce(&ref_object) == SUCCESSFUL_COMPLETION);
  assert(ref_object == NULL);

  free(buffer);
}

void test_ref_add_dependent_obj() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, sizeof(ref_count_t));

  memory_context mem_cntxt;
  mem_cntxt.allocate = pool_alloc_test;
  mem_cntxt.deallocate = pool_free_test;
  mem_cntxt.context = &allocator;

  void *object1 = pool_alloc(&allocator);
  void *object2 = pool_alloc(&allocator);

  ref_count_t *new_ref1;
  ref_count_t *new_ref2;

  assert(ref_create(&new_ref1, mem_cntxt, object1) == SUCCESSFUL_COMPLETION);
  assert(ref_create(&new_ref2, mem_cntxt, object2) == SUCCESSFUL_COMPLETION);
  assert(new_ref1->count == 1);

  assert(ref_add_dependent_obj(NULL, &new_ref2) == ALLOCATION_ERROR);
  assert(ref_add_dependent_obj(new_ref1, NULL) == ALLOCATION_ERROR);

  assert(ref_add_dependent_obj(new_ref1, &new_ref2) == SUCCESSFUL_COMPLETION);
  assert(new_ref1->count == 2);

  free(buffer);
}

void test_reduce() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, sizeof(ref_count_t));

  memory_context mem_cntxt;
  mem_cntxt.allocate = pool_alloc_test;
  mem_cntxt.deallocate = pool_free_test;
  mem_cntxt.context = &allocator;

  assert(ref_reduce(NULL) == ALLOCATION_ERROR);

  void *new_object1 = pool_alloc(&allocator);
  ref_count_t *new_ref1;

  assert(ref_create(&new_ref1, mem_cntxt, new_object1) ==
         SUCCESSFUL_COMPLETION);

  assert(new_ref1->count == 1);
  assert(new_ref1->object == new_object1);

  assert(ref_increase(new_ref1) == SUCCESSFUL_COMPLETION);
  assert(new_ref1->count == 2);

  ref_increase(new_ref1);

  assert(new_ref1->count == 3);
  assert(ref_reduce(&new_ref1) == SUCCESSFUL_COMPLETION);
  assert(new_ref1->count == 2);

  assert(ref_reduce(&new_ref1) == SUCCESSFUL_COMPLETION);

  assert(new_ref1->count == 1);

  ref_count_t *new_ref2;
  void *new_object2 = pool_alloc(&allocator);
  assert(ref_create(&new_ref2, mem_cntxt, new_object2) ==
         SUCCESSFUL_COMPLETION);

  assert(ref_add_dependent_obj(new_ref1, &new_ref2) == SUCCESSFUL_COMPLETION);
  assert(new_ref1->count == 2);

  assert(ref_reduce(&new_ref1) == SUCCESSFUL_COMPLETION);
  assert(ref_reduce(&new_ref1) == SUCCESSFUL_COMPLETION);

  assert(new_ref1 == NULL);
  assert(new_ref2 != NULL);

  assert(ref_reduce(&new_ref2) == SUCCESSFUL_COMPLETION);
  assert(new_ref2 == NULL);

  free(buffer);
}

int main() {
  test_create_ref();
  test_ref_increase();
  test_reduce();
  test_ref_add_dependent_obj();
  return 0;
}
