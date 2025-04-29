#include "linear_allocator.h"
#include <stdint.h>

int linear_allocator_init(linear_allocator* allocator, void* buffer, size_t buffer_size) {
    if (!allocator || !buffer || buffer_size == 0) {
        return LINEAR_ALLOC_INVALID_ARG;
    }
    
    allocator->buffer = buffer;
    allocator->buffer_size = buffer_size;
    allocator->offset = 0;
    
    return LINEAR_ALLOC_SUCCESS;
}

void* linear_alloc(linear_allocator* allocator, size_t size) {
    if (!allocator || size == 0) {
        return NULL;
    }
    
    if (allocator->offset + size > allocator->buffer_size) {
        return NULL;
    }
    
    void* ptr = (uint8_t*)allocator->buffer + allocator->offset;
    allocator->offset += size;
    
    return ptr;
}

void linear_reset(linear_allocator* allocator) {
    if (allocator) {
        allocator->offset = 0;
    }
}