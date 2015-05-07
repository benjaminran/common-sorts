#ifndef HEAP_H
#define HEAP_H

/* Notes
 * This is a maxheap.
 */

typedef struct heap heap;
struct heap {
  int *arr;
  int size;
};

heap *construct_heap(int *arr, int size);

int delete_max(heap *heap);

void print_heap(heap *heap);

#endif
