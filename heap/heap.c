#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "heap.h"

int parent_index(int index) {
  return index/2;
}

int left_child(int index) {
  return 2 * index;
}

int right_child(int index) {
  return 2 * index + 1;
}

bool is_root(int index) {
  return (index==1);
}

bool is_leaf(heap *heap, int index) {
  return left_child(index) > heap->size;
}

void swap(int *arr, int a, int b) {
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

void sink(heap *heap, int index) {
  if(is_leaf(heap, index)) return;
  int *arr = heap->arr;
  int left = left_child(index);
  int right = right_child(index);
  if(right>heap->size) { // only one child
	 if(arr[index]<arr[left]) swap(arr, index, left);
	 // no need to sink further: is leaf
  }
  else { // normal case: two children
	 if(arr[left]>arr[right]) { // left child is bigger than right
		if(arr[index]<arr[left]){
		  swap(arr, index, left);
		  sink(heap, left);
		}
	 }
	 else { // right child is bigger than left
		if(arr[index]<arr[right]) {
		  swap(arr, index, right);
		  sink(heap, right);
		}
	 }
  }
}

void swim(heap *heap, int index) {
  if(is_root(index)) return;
  int *arr = heap->arr;
  int parent = parent_index(index);
  if(arr[index]>arr[parent]) {
	 swap(arr, index, parent);
  }
  swim(heap, parent);
}

heap *construct_heap(int *arr, int size) {
  // Initialize heap
  heap *heap = malloc(sizeof(heap));
  int *heap_arr = calloc(size+1, sizeof(int));
  heap->arr = heap_arr;
  heap->size = size;
  // Set up heap array
  heap_arr[0] = 0;
  for(int i=0; i<size; i++) heap_arr[i+1] = arr[i];
  // Iteratively put each next element in the array into heap order
  for(int in_heap=1; in_heap<=size; in_heap++) {
	 int to_add = in_heap + 1;
	 swim(heap, to_add);
  }
  // Finished
  return heap;
}

int delete_max(heap *heap) {
  int max = heap->arr[1];
  swap(heap->arr, 1, heap->size);
  heap->size--;
  sink(heap, 1);
  return max;
}

void print_heap(heap *heap) {
  for(int i=1; i<=heap->size; i++) { // just print the array
	 printf((i<heap->size) ? "%d " : "%d\n", heap->arr[i]);
  }
}
