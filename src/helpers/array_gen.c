# include "array_gen.h"

/**
 * Function that "returns" an array of size N
 * params:
 *      n:              length of the array
 *      starting_val:   start filling up the array from this val
 */
unsigned long int* generate_array(int n, int starting_val) {
    // Allocate memory for N unsigned long integers
    unsigned long int* arr = malloc(n * sizeof(unsigned long int));
    
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Fill the array 
    for (int i = 0; i < n; i++) {
        arr[i] = starting_val + i;
    }

    // Return the pointer to the first element
    return arr;
}

void shuffle(unsigned long int *arr, int n) {
    if (n > 1) {
        for (int i = n - 1; i > 0; i--) {
            // Pick a random index from 0 to i
            int j = rand() % (i + 1);
            
            // Swap arr[i] with the element at random index j
            unsigned long int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
}