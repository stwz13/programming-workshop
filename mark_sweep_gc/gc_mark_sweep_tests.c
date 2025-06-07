#include "gc_mark_sweep.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_cyclic_reference_detection_and_collection() {
  gc_heap heap = {0};

  char *data1 = malloc(10);
  char *data2 = malloc(10);
  strcpy(data1, "A");
  strcpy(data2, "B");

  gc_object *obj1 = gc_create_object(&heap, data1);
  gc_object *obj2 = gc_create_object(&heap, data2);

  assert(obj1 && obj2);
  assert(gc_add_reference(obj1, obj2) == GC_SUCCESS);
  assert(gc_add_reference(obj2, obj1) == GC_SUCCESS);

  gc_collect(&heap);
  assert(heap.object_count == 0);
}

void test_mark_and_collect_without_cycles() {
  gc_heap heap = {0};

  char *root_data = malloc(20);
  strcpy(root_data, "root");
  gc_object *root = gc_create_object(&heap, root_data);
  assert(gc_add_root(&heap, root) == GC_SUCCESS);

  char *child_data = malloc(20);
  strcpy(child_data, "child");
  gc_object *child = gc_create_object(&heap, child_data);
  assert(gc_add_reference(root, child) == GC_SUCCESS);

  gc_collect(&heap);
  assert(heap.object_count == 2);

  gc_remove_root(&heap, root);
  gc_collect(&heap);
  assert(heap.object_count == 0);
}

void test_garbage_cleanup() {
  gc_heap heap = {0};

  char *orphan_data = malloc(30);
  strcpy(orphan_data, "unreachable");
  gc_object *orphan = gc_create_object(&heap, orphan_data);

  gc_collect(&heap);
  assert(heap.object_count == 0);
}

int main() {
  test_cyclic_reference_detection_and_collection();
  test_mark_and_collect_without_cycles();
  test_garbage_cleanup();
  return 0;
}
