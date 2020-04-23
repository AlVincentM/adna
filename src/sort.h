#include <time.h>


// function prototypes

void insertionSort(int arr[], int n);

void mergeSort(int arr[], int left, int right);

void merge(int arr[], int left, int middle, int right);


// global variables

clock_t start, end;
double cpu_time_used;