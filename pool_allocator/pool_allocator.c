#include "pool_allocator.h"

int init_pool_allocator(pool_allocator *allocator, void *buffer,
                        size_t buffer_size, size_t block_size) {
  if (!allocator || !buffer)
    return MEMORY_ALLOCATION_ERROR;

  if (buffer_size < block_size || block_size < sizeof(memory_block))
    return MEMORY_SIZE_ERROR;

  allocator->block_size = block_size;
  allocator->buffer = buffer;
  allocator->count_of_blocks = buffer_size / block_size;
  allocator->head_of_free_blocks = NULL;

  uint8_t *blocks = buffer;

  for (int i = 0; i < allocator->count_of_blocks; i++) {

    memory_block *curr_block = (memory_block *)(blocks + i * block_size);

    curr_block->next_block = allocator->head_of_free_blocks;
    allocator->head_of_free_blocks = curr_block;
  }

  return SUCCESSFUL_COMPLETION;
}

void *pool_alloc(pool_allocator *allocator) {
  if (!allocator || !allocator->head_of_free_blocks)
    return NULL;

  memory_block *selected_block = allocator->head_of_free_blocks;
  allocator->head_of_free_blocks = selected_block->next_block;

  return (void *)((uint8_t *)selected_block);
}

int pool_free(pool_allocator *allocator, void *ptr) {
  if (!allocator || !ptr)
    return MEMORY_ALLOCATION_ERROR;

  uint8_t *curr_address = ptr;
  uint8_t *begin = allocator->buffer;
  uint8_t *end = begin + allocator->count_of_blocks * allocator->block_size;

  if (!(begin <= curr_address && curr_address < end))
    return BEYOND_BUFFER;

  if ((curr_address - begin) % allocator->block_size != 0)
    return NOT_AT_THE_BEGINNING_OF_BLOCK;

  memory_block *curr_block = (memory_block *)curr_address;
  curr_block->next_block = allocator->head_of_free_blocks;
  allocator->head_of_free_blocks = curr_block;

  return SUCCESSFUL_COMPLETION;
}
