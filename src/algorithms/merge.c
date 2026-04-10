#include "algorithm.h"

void merge(ArrPtr arr, unsigned int left, unsigned int mid, unsigned int right) {
    unsigned int i, j, k;
    unsigned int n1 = mid - left + 1;
    unsigned int n2 = right - mid;

    // Create temporary arrays using the ArrElement type
    ArrElement *leftArr = (ArrElement*)malloc(n1 * sizeof(ArrElement));
    ArrElement *rightArr = (ArrElement*)malloc(n2 * sizeof(ArrElement));

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements
    while (i < n1) {
        arr[k] = leftArr[i++];
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j++];
        k++;
    }

    free(leftArr);
    free(rightArr);
}

// Internal recursive function
void mergeSortRecursive(ArrPtr arr, unsigned int left, unsigned int right) {
    if (left < right) {
        unsigned int mid = left + (right - left) / 2;

        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/**
 * handle_mergeSort
 * This matches the SortFunc typedef: void (*SortFunc)(ArrPtr, unsigned int)
 * @param arr: The array pointer
 * @param size: The number of elements in the array
 */
void handle_mergeSort(ArrPtr arr, unsigned int size) {
    if (arr == NULL || size < 2) {
        return;
    }
    // Call the recursive function with 0 and n-1
    mergeSortRecursive(arr, 0, size - 1);
}