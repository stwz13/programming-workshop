#include "assert.h"
#include "pool_allocator.h"
#include <stdio.h>

void test_init_allocator() {
  pool_allocator *null_allocator = NULL;
  int *null_buffer = NULL;
  assert(init_pool_allocator(null_allocator, null_buffer, sizeof(null_buffer),
                             8) == MEMORY_ALLOCATION_ERROR);

  pool_allocator allocator;
  double double_buffer[15];
  assert(init_pool_allocator(&allocator, null_buffer, sizeof(double_buffer),
                             8) == MEMORY_ALLOCATION_ERROR);
  assert(init_pool_allocator(null_allocator, &double_buffer,
                             sizeof(double_buffer),
                             8) == MEMORY_ALLOCATION_ERROR);

  assert(init_pool_allocator(&allocator, &double_buffer, sizeof(double_buffer),
                             8) == SUCCESSFUL_COMPLETION);

  int *malloc_buffer = malloc(1024);
  assert(init_pool_allocator(&allocator, malloc_buffer, 1024, 32) ==
         SUCCESSFUL_COMPLETION);

  uint8_t small_buffer[8];
  assert(init_pool_allocator(&allocator, &small_buffer, sizeof(small_buffer),
                             32) == MEMORY_SIZE_ERROR);
  free(malloc_buffer);
}

void test_alloc() {
  pool_allocator allocator;
  uint8_t *buffer = malloc(1024 * 1024);
  init_pool_allocator(&allocator, buffer, 1024 * 1024, 512);

  int count_of_blocks = allocator.count_of_blocks;

  float *float_array[count_of_blocks];
  for (int i = 0; i < count_of_blocks; i++) {

    float_array[i] = pool_alloc(&allocator);

    assert(float_array[i] != NULL);
  }
  assert(allocator.head_of_free_blocks == NULL);

  int *int_array = pool_alloc(&allocator);
  assert(int_array == NULL);

  free(buffer);
}

void test_free() {
  pool_allocator allocator;
  uint8_t *buffer = malloc(32);
  assert(init_pool_allocator(&allocator, buffer, 32, 16) ==
         SUCCESSFUL_COMPLETION);

  int *null_ptr = NULL;
  int *array_beyound_buffer = malloc((sizeof(int)));

  assert(pool_free(&allocator, null_ptr) == MEMORY_ALLOCATION_ERROR);

  assert(pool_free(&allocator, array_beyound_buffer) == BEYOND_BUFFER);
  void *ptr1 = pool_alloc(&allocator);
  assert(ptr1 != NULL);
  assert(pool_free(&allocator, ptr1 + 1) == NOT_AT_THE_BEGINNING_OF_BLOCK);

  assert(pool_free(&allocator, ptr1) == SUCCESSFUL_COMPLETION);

  void *ptr2 = pool_alloc(&allocator);

  assert(ptr2 != NULL);

  assert(allocator.head_of_free_blocks != NULL);

  assert(ptr1 == ptr2);

  pool_free(&allocator, ptr2);

  free(buffer);
}
int main() {
  test_init_allocator();
  test_alloc();
  test_free();

  return 0;
}
