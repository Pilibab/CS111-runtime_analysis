#include "validation.h"

/**
 * Validates that an array is an increasing sequence starting at X.
 * Rules:
 * 1. arr[0] must be X
 * 2. Every element must be exactly 1 greater than the previous.
 */
bool validate_sort(ArrPtr arr, int n, ArrElement x) {
    if (arr == NULL || n <= 0) return false;

    // Starts at X
    if (arr[0] != x) {
        printf("Test Failed: Expected start %lu, got %lu\n", x, arr[0]);
        return false;
    }

    // Continuity (prev - next == -1)
    for (int i = 1; i < n; i++) {
        // Checking if (previous - current) is -1
        // Note: Using long casting to avoid unsigned underflow wrap-around during the check
        if ((long)arr[i-1] - (long)arr[i] != -1) {
            printf("Test Failed at index %d: %lu and %lu are not sequential\n", i, arr[i-1], arr[i]);
            return false;
        }
    }

    return true;
}