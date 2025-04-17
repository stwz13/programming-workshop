#include <stdint.h>
#include <stdlib.h>

#define SUCCESSFUL_COMPLETION 0
#define MEMORY_ALLOCATION_ERROR -1
#define MEMORY_SIZE_ERROR -2
#define BEYOND_BUFFER -3

typedef struct memory_block memory_block;

struct memory_block {
  memory_block *next_block;
};

typedef struct {
  void *buffer;
  size_t block_size;
  size_t count_of_blocks;
  memory_block *head_of_free_blocks;
} pool_allocator;

int init_pool_allocator(pool_allocator *allocator, void *buffer,
                        size_t buffer_size, size_t block_size);
void *pool_alloc(pool_allocator *allocator);
int pool_free(pool_allocator *allocator, void *ptr);
