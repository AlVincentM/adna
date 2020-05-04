#include "sort.h"
#include <stdio.h>

/**
 * [insertionSort description]
 * @author Al Vincent
 */
void insertionSort(void) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = *(temp_array + i);
        j = i - 1;

        while (j >= 0 && *(temp_array + j) > key) {
            *(temp_array + (j + 1)) = *(temp_array + j);
            j = j - 1;
        }
        *(temp_array + (j + 1)) = key;
    }
}

/**
 * [merge description]
 * @author Al Vincent
 * @param  left   [description]
 * @param  middle [description]
 * @param  right  [description]
 */
void merge(int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int left_arr[n1], right_arr[n2];

    for (i = 0; i < n1; i++)
    {
        left_arr[i] = *(temp_array + (left + i));
    }

    for (j = 0; j < n2; j++)
    {
        right_arr[j] = *(temp_array + (middle + 1 + j));
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j])
        {
            *(temp_array + k) = left_arr[i];
            i++;
        }
        else {
            *(temp_array + k) = right_arr[j];
            j++;
        }

        k++;
    }

    while(i < n1) {
        *(temp_array + k) = left_arr[i];
        i++;
        k++;
    }

    while (j < n2) {
        *(temp_array + k) = right_arr[j];
        j++;
        k++;
    }
}

/**
 * [mergeSort description]
 * @author Al Vincent
 * @param  left  [description]
 * @param  right [description]
 */
void mergeSort(int left, int right) {
    if (left < right)
    {
        int middle =  left + (right - left) / 2;

        mergeSort(left, middle);
        mergeSort(middle + 1, right);

        merge(left, middle, right);
    }
}

/**
 * [swap description]
 * @author Al Vincent
 * @param  a [description]
 * @param  b [description]
 */
void swap(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}