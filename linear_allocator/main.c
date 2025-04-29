#include "linear_allocator.h"
#include <assert.h>

#define TEST_BUFFER_SIZE 1024

void test_allocator_initialization() {
    char buffer[TEST_BUFFER_SIZE];
    linear_allocator allocator;
    
    assert(linear_allocator_init(NULL, buffer, TEST_BUFFER_SIZE) == LINEAR_ALLOC_INVALID_ARG);
    assert(linear_allocator_init(&allocator, NULL, TEST_BUFFER_SIZE) == LINEAR_ALLOC_INVALID_ARG);
    assert(linear_allocator_init(&allocator, buffer, 0) == LINEAR_ALLOC_INVALID_ARG);
    assert(linear_allocator_init(&allocator, buffer, TEST_BUFFER_SIZE) == LINEAR_ALLOC_SUCCESS);
}

void test_simple_allocation() {
    char buffer[TEST_BUFFER_SIZE];
    linear_allocator allocator;
    linear_allocator_init(&allocator, buffer, TEST_BUFFER_SIZE);
    
    int* int_ptr = (int*)linear_alloc(&allocator, sizeof(int));
    assert(int_ptr != NULL);
    *int_ptr = 42;
    assert(*int_ptr == 42);
    
    double* double_ptr = (double*)linear_alloc(&allocator, sizeof(double));
    assert(double_ptr != NULL);
    *double_ptr = 3.14;
    assert(*double_ptr == 3.14);
}

void test_allocation_boundaries() {
    char buffer[TEST_BUFFER_SIZE];
    linear_allocator allocator;
    linear_allocator_init(&allocator, buffer, TEST_BUFFER_SIZE);
    
    assert(linear_alloc(NULL, 10) == NULL);
    assert(linear_alloc(&allocator, 0) == NULL);
    
    void* full_alloc = linear_alloc(&allocator, TEST_BUFFER_SIZE);
    assert(full_alloc != NULL);
    assert(linear_alloc(&allocator, 1) == NULL);
}

void test_allocator_reset() {
    char buffer[TEST_BUFFER_SIZE];
    linear_allocator allocator;
    linear_allocator_init(&allocator, buffer, TEST_BUFFER_SIZE);
    
    int* ptr1 = (int*)linear_alloc(&allocator, sizeof(int));
    assert(ptr1 != NULL);
    
    linear_reset(&allocator);
    
    char* ptr2 = (char*)linear_alloc(&allocator, TEST_BUFFER_SIZE);
    assert(ptr2 != NULL);
    assert(ptr2 == buffer);
}

void test_sequential_allocation() {
    char buffer[TEST_BUFFER_SIZE];
    linear_allocator allocator;
    linear_allocator_init(&allocator, buffer, TEST_BUFFER_SIZE);
    
    size_t block_size = 32;
    size_t blocks_count = TEST_BUFFER_SIZE / block_size;
for (size_t i = 0; i < blocks_count; i++) {
        void* block = linear_alloc(&allocator, block_size);
        assert(block != NULL);
    }
    
    assert(linear_alloc(&allocator, 1) == NULL);
    
    linear_reset(&allocator);
    
    void* after_reset = linear_alloc(&allocator, block_size);
    assert(after_reset != NULL);
}

int main() {
    test_allocator_initialization();
    test_simple_allocation();
    test_allocation_boundaries();
    test_allocator_reset();
    test_sequential_allocation();
    
    return 0;
}
