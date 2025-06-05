#ifndef GC_MARK_SWEEP_H
#define GC_MARK_SWEEP_H

#define GC_SUCCESS 0
#define GC_ALLOCATION_ERROR -1
#define MAX_OBJECTS 1000

typedef struct gc_object gc_object;
typedef struct gc_reference gc_reference;

struct gc_reference {
  gc_object *to;
  gc_reference *next;
};

struct gc_object {
  void *object;
  int marked;
  gc_reference *references;
  gc_object *next;
};

typedef struct {
  gc_object *head;
  int object_count;
  gc_object *roots[MAX_OBJECTS];
  int root_count;
} gc_heap;

gc_object *gc_create_object(gc_heap *heap, void *object);
int gc_add_reference(gc_object *from, gc_object *to);
void gc_mark(gc_object *root);
void gc_collect(gc_heap *heap);

int gc_add_root(gc_heap *heap, gc_object *obj);
int gc_remove_root(gc_heap *heap, gc_object *obj);

#endif
