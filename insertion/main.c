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

/* Repeatedly takes the first element from the unsorted sublist and percolates it backwards until it is at the correct place in the sorted sublist */
void insertion_sort(size_t len, int *arr) {
  for(size_t unsorted=1; unsorted<len; unsorted++){
	 bool hit_start = false;
	 for(size_t i=unsorted-1; !hit_start; i--) {
		if(arr[i]>arr[i+1]) swap(arr, i, i+1); 
		hit_start = (i==0);
	 }
  }
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
  insertion_sort(len, arr);
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
