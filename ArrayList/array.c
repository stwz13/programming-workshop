#include "array.h"

int arraylist_init(array_list *list, pool_allocator *alloc,
                   size_t element_size) {
  if (!list || !alloc)
    return ALLOCATION_ERROR;
  if (element_size == 0 || alloc->block_size < DEFAULT_CAPACITY * element_size)
    return MEMORY_SIZE_ERROR;
  list->allocator = alloc;
  list->capacity = DEFAULT_CAPACITY;
  list->length = 0;
  list->element_size = element_size;
  list->head_of_elements = pool_alloc(alloc);

  if (!list->head_of_elements)
    return ALLOCATION_ERROR;

  memset(list->head_of_elements, 0, list->capacity * list->element_size);
  return SUCCESSFUL_RESULT;
}

int arraylist_expand(array_list *list) {
  if (!list)
    return ALLOCATION_ERROR;
  if (list->allocator->block_size < list->element_size * list->capacity * 2)
    return MEMORY_SIZE_ERROR;
  list->capacity = list->capacity * 2;

  void *new_head_of_elements = pool_alloc(list->allocator);
  if (!new_head_of_elements)
    return ALLOCATION_ERROR;

  memcpy(new_head_of_elements, list->head_of_elements,
         list->length * list->element_size);

  memset(new_head_of_elements + list->length * list->element_size, 0,
         (list->capacity - list->length) * list->element_size);

  pool_free(list->allocator, list->head_of_elements);
  list->head_of_elements = new_head_of_elements;
  return SUCCESSFUL_RESULT;
}

int arraylist_add(array_list *list, void *data, size_t index) {
  if (!list || !data)
    return ALLOCATION_ERROR;

  if (index > list->length)
    return BEYOND_LIST_LENGTH;

  if (list->length == list->capacity)
    arraylist_expand(list);
  if (index < list->length) {
    memmove(list->head_of_elements + (index + 1) * list->element_size,
            list->head_of_elements + index * list->element_size,
            (list->length - index) * list->element_size);
  }

  memcpy(list->head_of_elements + index * list->element_size, data,
         list->element_size);
  list->length++;
  return SUCCESSFUL_RESULT;
}

void *arraylist_get(array_list *list, size_t index) {
  if (!list || index >= list->length)
    return NULL;

  return list->head_of_elements + index * list->element_size;
}

int arraylist_del(array_list *list, size_t index) {
  if (!list)
    return ALLOCATION_ERROR;
  if (index >= list->length)
    return BEYOND_LIST_LENGTH;
  memmove(list->head_of_elements + index * list->element_size,
          list->head_of_elements + (index + 1) * list->element_size,
          (list->length - index - 1) * list->element_size);

  memset(list->head_of_elements + (list->length - 1) * list->element_size, 0,
         list->element_size);
  list->length--;
  return SUCCESSFUL_RESULT;
}

int arraylist_free(array_list *list) {
  if (!list)
    return ALLOCATION_ERROR;
  pool_free(list->allocator, list->head_of_elements);

  list->head_of_elements = NULL;
  list->length = 0;
  list->capacity = 0;
  list->allocator = NULL;
  list->element_size = 0;

  return SUCCESSFUL_RESULT;
}
