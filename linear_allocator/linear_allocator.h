#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stddef.h>

#define LINEAR_ALLOC_SUCCESS 0
#define LINEAR_ALLOC_INVALID_ARG -1
#define LINEAR_ALLOC_OUT_OF_MEMORY -2

typedef struct {
    void* buffer;
    size_t buffer_size;
    size_t offset;
} linear_allocator;

int linear_allocator_init(linear_allocator* allocator, void* buffer, size_t buffer_size);
void* linear_alloc(linear_allocator* allocator, size_t size);
int linear_reset(linear_allocator* allocator);

#endif
