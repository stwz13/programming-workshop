#include "gc_mark_sweep.h"
#include <stdlib.h>
#include <string.h>

static gc_reference *create_reference(gc_object *to) {
  gc_reference *ref = malloc(sizeof(gc_reference));
  if (!ref)
    return NULL;
  ref->to = to;
  ref->next = NULL;
  return ref;
}

gc_object *gc_create_object(gc_heap *heap, void *object) {
  if (!heap || heap->object_count >= MAX_OBJECTS)
    return NULL;

  gc_object *new_obj = malloc(sizeof(gc_object));
  if (!new_obj)
    return NULL;

  new_obj->object = object;
  new_obj->marked = 0;
  new_obj->references = NULL;
  new_obj->next = heap->head;
  heap->head = new_obj;
  heap->object_count++;
  return new_obj;
}

int gc_add_reference(gc_object *from, gc_object *to) {
  if (!from || !to)
    return GC_ALLOCATION_ERROR;

  gc_reference *ref = create_reference(to);
  if (!ref)
    return GC_ALLOCATION_ERROR;

  ref->next = from->references;
  from->references = ref;
  return GC_SUCCESS;
}

int gc_mark(gc_object *obj) {
  if (!obj || obj->marked)
    return GC_ALLOCATION_ERROR;

  obj->marked = 1;
  gc_reference *ref = obj->references;
  while (ref) {
    gc_mark(ref->to);
    ref = ref->next;
  }
}

int gc_add_root(gc_heap *heap, gc_object *obj) {
  if (!heap || !obj || heap->root_count >= MAX_OBJECTS)
    return GC_ALLOCATION_ERROR;

  heap->roots[heap->root_count++] = obj;
  return GC_SUCCESS;
}

int gc_remove_root(gc_heap *heap, gc_object *obj) {
  if (!heap || !obj)
    return GC_ALLOCATION_ERROR;

  for (int i = 0; i < heap->root_count; i++) {
    if (heap->roots[i] == obj) {
      heap->roots[i] = heap->roots[--heap->root_count];
      return GC_SUCCESS;
    }
  }
  return GC_ALLOCATION_ERROR;
}

static void gc_sweep(gc_heap *heap) {
  gc_object **current = &heap->head;
  while (*current) {
    if (!(*current)->marked) {
      gc_object *unreached = *current;
      *current = unreached->next;

      gc_reference *ref = unreached->references;
      while (ref) {
        gc_reference *next = ref->next;
        free(ref);
        ref = next;
      }

      free(unreached->object);
      free(unreached);
      heap->object_count--;
    } else {
      (*current)->marked = 0;
      current = &(*current)->next;
    }
  }
}

int gc_collect(gc_heap *heap) {
  if (!heap)
    return GC_ALLOCATION_ERROR;

  gc_object *obj = heap->head;
  while (obj) {
    obj->marked = 0;
    obj = obj->next;
  }

  for (int i = 0; i < heap->root_count; i++) {
    if (heap->roots[i]) {
      gc_mark(heap->roots[i]);
    }
  }

  gc_sweep(heap);
}
