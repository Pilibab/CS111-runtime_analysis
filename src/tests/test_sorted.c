#include "validation.h"

/**
 * Validates that an array is an increasing sequence starting at X.
 * Rules:
 * 1. arr[0] must be X
 * 2. Every element must be exactly 1 greater than the previous.
 */
bool validate_sort(ArrPtr arr, ArrElement n) {
    // arr of len 1 || 2 is sorted 
    if (arr == NULL || n <= 2) return false;

    // arr[i-1] < arr[i] => 1
    // arr[i-1] > arr[i] => 2
    int direction = 0;
    
    for (int i = 1; i < n; i++) {
        if (direction == 0) {
            direction = set_direction(arr[i-1], arr[i]);
        } else {
            // If we are Ascending (1), any 'prev > next' is a failure
            if (direction == 1 && arr[i-1] > arr[i]) {
                return false;
            }
            // If we are Descending (2), any 'prev < next' is a failure
            if (direction == 2 && arr[i-1] < arr[i]) {
                return false;
            }
        }
    }   
    return true;
}

int set_direction(
    ArrElement a,   // arr[i-1]
    ArrElement b    // arr[i]
) {
    if (a < b) {
        return 1;

    } else if (a > b) {
        return 2;
    } else return 0;
}