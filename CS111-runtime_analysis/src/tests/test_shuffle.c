#include "validation.h"

// this can also be used to say do {shuffling} while(!bool validate_shuffle) 
bool validate_shuffle(ArrPtr arr, ArrElement n, ArrElement start_v) {
    // num of elements that are still in their original position 
    ArrElement elementInPlace = 0; 

    for (int i = 0; i < n; i++) {
        // If the value is exactly what it would be in a sorted array
        if (arr[i] == (start_v + i)) {
            elementInPlace++;
        }
    }

    // If more than 10% of the elements stayed exactly where they were, 
    // something is likely wrong with the random seed or the loop logic.
    if (elementInPlace > (n * 0.1)) { 
        printf("no of element in place: %lu out of %lu\n", elementInPlace, n);
        return false; 
    }

    return true;
}