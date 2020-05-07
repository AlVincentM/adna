#ifndef SORT_H

#include <time.h>

#include "util.h"

#endif


/////////////////////////
// Function prototypes //
/////////////////////////

extern void insertionSort(void);

extern void mergeSort(int left, int right);

// extern void quickSort(int arr[], int low, int high);
extern void quickSort(int low, int high);

extern void merge(int left, int middle, int right);

extern void swap(int *a, int *b);

// extern int partition(int arr[], int low, int high);
extern int partition(int low, int high);

extern void heapify(int n, int i);

extern void heapSort();