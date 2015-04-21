#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int NUM_TESTS = 1000;
int MAX_LEN = 1000;

void swap(int *arr, size_t a, size_t b) {
  int tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}

size_t partition(int *arr, size_t low, size_t high) {
  size_t high_edge = high-1;// outside the edges, elements are on the correct side of the pivot
  size_t low_edge = low;
  size_t pivot = low;
  bool looking_high = true;
  while(true) {
	 if(looking_high) {
		while(true) {
		  if(high_edge==pivot) return pivot;
		  if(arr[high_edge]<arr[pivot]) {
			 swap(arr, high_edge, pivot);
			 low_edge = pivot + 1;
			 pivot = high_edge;
			 break;
		  }
		  else {
			 high_edge--;
		  }
		}
	 }
	 else { // looking low
		while(true) {
		  if(low_edge==pivot) return pivot;
		  if(arr[low_edge]>arr[pivot]) {
			 swap(arr, low_edge, pivot);
			 high_edge = pivot - 1;
			 pivot = low_edge;
			 break;
		  }
		  else {
			 low_edge++;
		  }
		}
	 }
	 looking_high = !looking_high;
  }
}

/* Recursively partitions the array (moves all elements less than the pivot to the left of the pivot and vice versa) then sorts both sides of the partition. A single element is sorted by definition */
void quick_sort(int *arr, size_t low, size_t high) {
  int n = high - low; // interval to sort is [low, high)
  if(n<=1) return;
  size_t pivot = partition(arr, low, high);
  quick_sort(arr, low, pivot);
  quick_sort(arr, pivot+1, high);
}

int *new_array(size_t len) {
  int *arr = calloc(len, sizeof(int));
  for(size_t i=0; i<len; i++) arr[i] = rand();
  return arr;
}

void print_array(size_t len, int *arr) {
  puts("print_array:");
  for(size_t i=0; i<len; i++) printf("  %d\n", arr[i]);
}

bool arr_eq(size_t len, int *a, int *b) {
  for(size_t i=0; i<len; i++) if(a[i]!=b[i]) return false;
  return true;
}

int *arr_cp(size_t len, int *arr) {
  int *cp = calloc(len, sizeof(int));
  return memcpy(cp, arr, len*sizeof(int));
}

int int_cmp(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

bool test(size_t len) {
  int *arr = new_array(len);
  int *arr_sys = arr_cp(len, arr);
  quick_sort(arr, 0, len);
  qsort(arr_sys,len, sizeof(int), int_cmp); 
  //print_array(len, arr);
  //print_array(len, arr_sys);
  return arr_eq(len, arr, arr_sys);
}

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;
  int successes = 0;
  int failures = 0;
  for(int i=0; i<NUM_TESTS; i++) {
	 if(test((rand() % (MAX_LEN-1)) + 1)) successes++;
	 else failures++;
  }
  printf("%d tests were successful.\n%d tests failed.\n", successes, failures);
}
