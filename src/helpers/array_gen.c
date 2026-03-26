# include "array_gen.h"

/**
 * Function that "returns" an array of size N
 * params:
 *      n:              length of the array
 *      starting_val:   start filling up the array from this val
 */
ArrPtr generate_array(int n, int starting_val) {
    // Allocate memory for N ArrElementegers
    ArrPtr arr = malloc(n * sizeof(ArrElement));
    
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

void shuffle(ArrPtr arr, int n) {
    if (n > 1) {
        for (int i = n - 1; i > 0; i--) {
            // Pick a random index from 0 to i
            int j = rand() % (i + 1);
            
            // Swap arr[i] with the element at random index j
            ArrElement temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
}