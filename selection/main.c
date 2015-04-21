#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int NUM_TESTS = 1000;
int MAX_LEN = 1000;

/* Iteratively selects the next element to add to the sorted sublist */
void selection_sort(size_t len, int *arr) {
  for(size_t unsorted=0; unsorted<len-1; unsorted++) {
	 size_t min_i = unsorted;
	 int min = arr[unsorted];
	 for(size_t i=unsorted; i<len; i++) {
		if(arr[i]<min) {
		  min_i = i;
		  min = arr[i];
		}
	 }
	 arr[min_i] = arr[unsorted];
	 arr[unsorted] = min;
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
  selection_sort(len, arr);
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
