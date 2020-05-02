#include <time.h>


/////////////////////////
// Function prototypes //
/////////////////////////

void insertionSort(int arr[], int n);

void mergeSort(int arr[], int left, int right);

void quickSort(int arr[], int low, int high);

void merge(int arr[], int left, int middle, int right);

void swap(int * a, int * b);

int partition(int arr[], int low, int high);

void heapify(int arr[], int n, int i);

void heapSort(int arr[], int n);


//////////////////////
// Global variables //
//////////////////////

clock_t start, end;
double cpu_time_used;