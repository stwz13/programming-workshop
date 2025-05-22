#include "assert.h"
#include "gc.h"

void test_create_ref() {
  void *buffer = malloc(1024);
  pool_allocator *null_allocator = NULL;
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, sizeof(ref_count_t));

  ref_count_t *int_ref;
  int int_data = 15;
  assert(ref_create(&int_ref, null_allocator, &int_data) == ALLOCATION_ERROR);
  assert(ref_create(&int_ref, &allocator, &int_data) == SUCCESSFUL_COMPLETION);

  assert(*(int *)(int_ref->object) == 15);

  assert(int_ref->count = 1);

  assert(ref_reduce(&int_ref) == SUCCESSFUL_COMPLETION);
  assert(int_ref == NULL);

  ref_count_t *null_ref;
  void *null_object = NULL;

  assert(ref_create(&null_ref, &allocator, null_object) == ALLOCATION_ERROR);

  assert(ref_create(NULL, &allocator, null_object) == ALLOCATION_ERROR);

  free(buffer);
}

void test_ref_increase() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, sizeof(ref_count_t));

  assert(ref_increase(NULL) == ALLOCATION_ERROR);

  void *object = pool_alloc(&allocator);
  ref_count_t *ref_object;
  assert(ref_create(&ref_object, &allocator, object) == SUCCESSFUL_COMPLETION);

  assert(ref_increase(ref_object) == SUCCESSFUL_COMPLETION);
  assert(ref_object->count == 2);

  ref_reduce(&ref_object);
  assert(ref_object->count == 1);

  assert(ref_reduce(&ref_object) == SUCCESSFUL_COMPLETION);
  assert(ref_object == NULL);

  free(buffer);
}

void test_reduce() {
  void *buffer = malloc(1024);
  pool_allocator allocator;
  init_pool_allocator(&allocator, buffer, 1024, sizeof(ref_count_t));

  assert(ref_reduce(NULL) == ALLOCATION_ERROR);

  void *void_object = pool_alloc(&allocator);
  ref_count_t *new_ref;
  assert(ref_create(&new_ref, &allocator, void_object) ==
         SUCCESSFUL_COMPLETION);

  assert(new_ref->count == 1);
  assert(ref_reduce(&new_ref) == SUCCESSFUL_COMPLETION);

  int *int_object = pool_alloc(&allocator);
  *int_object = 3;
  ref_count_t *int_ref;

  assert(ref_create(&int_ref, &allocator, int_object) == SUCCESSFUL_COMPLETION);

  assert(int_ref->count == 1);
  assert(*(int *)int_ref->object == 3);

  assert(ref_increase(int_ref) == SUCCESSFUL_COMPLETION);
  assert(int_ref->count == 2);

  ref_increase(int_ref);

  assert(int_ref->count == 3);
  assert(ref_reduce(&int_ref) == SUCCESSFUL_COMPLETION);
  assert(int_ref->count == 2);

  ref_reduce(&int_ref);

  assert(int_ref->count == 1);
  assert(ref_reduce(&int_ref) == SUCCESSFUL_COMPLETION);

  assert(int_ref == NULL);

  free(buffer);
}
int main() {
  test_create_ref();
  test_ref_increase();
  test_reduce();
  return 0;
}
