#include "algorithm.h"

// To heapify a subtree rooted with node i.
// n is size of heap, i is the index of the root of the subtree.
void heapify(ArrPtr arr, unsigned int n, unsigned int i) {
    unsigned int largest = i;
    unsigned int l = 2 * i + 1; // left child index
    unsigned int r = 2 * i + 2; // right child index

    // If left child is larger than root
    // Note: Since l is unsigned, it's always >= 0, so we only check l < n
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        ArrElement temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
// This now matches the SortFunc signature: void (ArrPtr, unsigned int)
void heapSort(ArrPtr arr, unsigned int n) {
    if (n <= 1) return;

    // Build heap (rearrange array)
    // We use a signed loop counter for i because it needs to go below 0
    for (int i = (int)n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, (unsigned int)i);
    }

    // One by one extract an element from heap
    for (unsigned int i = n - 1; i > 0; i--) {
        // Move current root to end
        ArrElement temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
