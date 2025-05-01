#include "array.h"

int arraylist_init(array_list *list, pool_allocator *alloc) {
  if (!list || !alloc)
    return ALLOCATION_ERROR;
  if (alloc->block_size < DEFAULT_CAPACITY * sizeof(void *))
    return MEMORY_SIZE_ERROR;
  list->allocator = alloc;
  list->capacity = DEFAULT_CAPACITY;
  list->length = 0;
  list->head_of_elements = pool_alloc(alloc);

  if (!list->head_of_elements)
    return ALLOCATION_ERROR;

  for (int i = 0; i < list->capacity; i++) {
    list->head_of_elements[i] = NULL;
  }
  return SUCCESSFUL_RESULT;
}

int arraylist_expand(array_list *list) {
  if (!list)
    return ALLOCATION_ERROR;
  if (list->allocator->block_size < list->capacity * 2)
    return MEMORY_SIZE_ERROR;
  list->capacity = list->capacity * 2;

  void **new_head_of_elements = pool_alloc(list->allocator);
  if (!new_head_of_elements)
    return ALLOCATION_ERROR;

  memcpy(new_head_of_elements, list->head_of_elements,
         list->length * (sizeof(void *)));

  for (int i = list->length; i < list->capacity; i++) {
    list->head_of_elements[i] = NULL;
  }
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
    memmove(&list->head_of_elements[index + 1], &list->head_of_elements[index],
            (list->length - index) * sizeof(void *));
  }

  list->head_of_elements[index] = data;
  list->length++;
  return SUCCESSFUL_RESULT;
}

void *arraylist_get(array_list *list, size_t index) {
  if (!list || index >= list->length)
    return NULL;

  return list->head_of_elements[index];
}

int arraylist_del(array_list *list, size_t index) {
  if (!list)
    return ALLOCATION_ERROR;
  if (index >= list->length)
    return BEYOND_LIST_LENGTH;
  memmove(&list->head_of_elements[index], &list->head_of_elements[index + 1],
          (list->length - index - 1) * sizeof(void *));
  list->head_of_elements[list->length - 1] = NULL;
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

  return SUCCESSFUL_RESULT;
}
