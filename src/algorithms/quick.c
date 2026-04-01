#include "algorithm.h"
// Partition function using unsigned int for indices
unsigned int partition(ArrPtr arr, unsigned int low, unsigned int high) {
    ArrElement p = arr[low];
    unsigned int i = low;
    unsigned int j = high;

    while (i < j) {
        // Find the first element greater than the pivot
        while (arr[i] <= p && i < high) {
            i++;
        }

        // Find the first element smaller than the pivot
        // Note: j > low handles the boundary without underflow
        while (arr[j] > p && j > low) {
            j--;
        }
        
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Swap pivot into its correct sorted position
    swap(&arr[low], &arr[j]);
    return j;
}

// Internal recursive function
void quickSortRecursive(ArrPtr arr, unsigned int low, unsigned int high) {
    if (low < high) {
        unsigned int pi = partition(arr, low, high);

        // Handle underflow for left side: pi - 1
        if (pi > low) {
            quickSortRecursive(arr, low, pi - 1);
        }
        
        quickSortRecursive(arr, pi + 1, high);
    }
}

/**
 * handle_quickSort
 * Matches the SortFunc typedef: void (*SortFunc)(ArrPtr, unsigned int)
 */
void handle_quickSort(ArrPtr arr, unsigned int size) {
    // Safety check for empty or single-element arrays
    if (arr == NULL || size < 2) {
        return;
    }

    // Call the recursive logic with low=0 and high=size-1
    quickSortRecursive(arr, 0, size - 1);
}