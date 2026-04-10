#include "algorithm.h"


// Median-of-three pivot selection
ArrElement median_of_three(ArrPtr arr, unsigned int low, unsigned int high) {
    unsigned int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);

    return arr[mid]; // median value
}

// Hoare partition scheme
unsigned int partition(ArrPtr arr, unsigned int low, unsigned int high) {
    ArrElement pivot = median_of_three(arr, low, high);

    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(&arr[i], &arr[j]);
    }
}

// Tail-recursive optimized Quick Sort
void quickSortRecursive(ArrPtr arr, unsigned int low, unsigned int high) {
    while (low < high) {
        unsigned int pi = partition(arr, low, high);

        // Recurse on smaller side FIRST (limits stack depth)
        if (pi - low < high - pi) {
            quickSortRecursive(arr, low, pi);
            low = pi + 1; // tail recursion elimination
        } else {
            quickSortRecursive(arr, pi + 1, high);
            high = pi;
        }
    }
}

void handle_quickSort(ArrPtr arr, unsigned int size) {
    if (arr == NULL || size < 2) return;
    quickSortRecursive(arr, 0, size - 1);
}