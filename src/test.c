#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#define SIZEOF(a) sizeof(a) / sizeof(a[0])
#define MAX_RANGE 10000

void printArr(int arr[], int n) {

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
	printf("Time elapsed: %f ...\n", cpu_time_used);
}

void generateArray(int arr[], int n) {
	for (int i = 0; i < n; ++i)
	{
		arr[i] = rand() % MAX_RANGE + 1;
	}
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);

	int array[n];

    size_t size = SIZEOF(array);

    generateArray(array, size);

	printf("Heap Sort\n");
    // mergeSort(array, 0, size - 1);
    // insertionSort(array, size);
    // quickSort(array, 0, n - 1);
    heapSort(array, size);
    printArr(array, size);
    
    printf("%d\n", n);

    return 0;
}