#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


#include "../helpers/array_gen.h"

// To test only the generation logic
// gcc src/helpers/array_gen.c tests/test_gen.c -o test_logic
// ./test_logic
bool validate_increasing_sequence(unsigned long int* arr, int n, unsigned long int x) ;
void run_array_gen_tests();

void run_array_gen_tests() {
    int N = 1000;
    unsigned long int X = 50;

    printf("--- Running Array Generation Tests ---\n");

    
    unsigned long int* my_arr = generate_array(N, X); 

    // 2. Run the validation
    if (validate_increasing_sequence(my_arr, N, X)) {
        printf("PASS: Sequence is correct, starts at %lu, and has %d elements.\n", X, N);
    } else {
        printf("FAIL: Sequence logic is broken.\n");
    }

    free(my_arr); // Always free after testing!
}

/**
 * Validates that an array is an increasing sequence starting at X.
 * Rules:
 * 1. arr[0] must be X
 * 2. Every element must be exactly 1 greater than the previous.
 */
bool validate_increasing_sequence(unsigned long int* arr, int n, unsigned long int x) {
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

int main() {
    run_array_gen_tests();
}

// this can also be used to say do {shuffling} while(!bool validate_shuffle) 
bool validate_shuffle(unsigned long int* arr, int n, unsigned long int start_v) {
    // num of elements that are still in their original position 
    unsigned int elementInPlace; 

    for (int i = 0; i < n; i++) {
        // If the value is exactly what it would be in a sorted array
        if (arr[i] == (start_v + i)) {
            elementInPlace++;
        }
    }

    // If more than 10% of the elements stayed exactly where they were, 
    // something is likely wrong with the random seed or the loop logic.
    if (elementInPlace > (n * 0.1)) { 
        return false; 
    }

    return true;
}