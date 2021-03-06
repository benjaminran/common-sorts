#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int NUM_TESTS = 1000;
int MAX_LEN = 1000;

void ms_merge(int *arr, size_t low, size_t mid, size_t high) {
  size_t low_i = 0;
  size_t high_i = mid-low;
  size_t out_i = low;
  int *tarr = calloc(high-low, sizeof(int));
  memcpy(tarr, &(arr[low]), (high-low)*sizeof(int));
  while(true) {
	 if(tarr[low_i]<tarr[high_i]) {
		arr[out_i] = tarr[low_i];
		low_i++;
		out_i++;
		if(low_i==mid-low) {
		  for( ; high_i<high-low; high_i++){
			 arr[out_i] = tarr[high_i];
			 out_i++;
		  }
		  break;
		}
	 }
	 else {
		arr[out_i] = tarr[high_i];
		high_i++;
		out_i++;
		if(high_i==high-low) {
		  for( ; low_i<mid-low; low_i++) {
			 arr[out_i] = tarr[low_i];
			 out_i++;
		  }
		  break;
		}
	 }
  }
}

/* Recursively splits the input in half, sorts both halves, then merges the two halves into a single sorted output. Subarrays of one element are sorted. */
void merge_sort(int *arr, size_t low, size_t high) {
  size_t n = high - low; // range to sort is [low, high)
  if(n==1) return;
  size_t mid = (high+low) / 2;
  merge_sort(arr, low, mid);
  merge_sort(arr, mid, high);
  ms_merge(arr, low, mid, high);
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
  merge_sort(arr, 0, len);
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
