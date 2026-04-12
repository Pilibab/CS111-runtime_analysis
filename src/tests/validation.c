#include "validation.h"


void run_array_gen_tests(ArrPtr my_arr, ArrElement N, ArrElement X) {
    // Run the validation
    if (validate_sort(my_arr, N)) {
        printf("PASS: Sequence is correct, starts at %lu, and has %lu elements.\n", X, N);
    } else {
        printf("FAIL: Sequence logic is broken.\n");
    }

}

void run_array_shuffle_test(ArrPtr my_arr,ArrElement N, ArrElement X){
    // Run the validation
    if (validate_shuffle(my_arr, N, X)) {
        printf("PASS: Sequence is shuffled correctly, starts at %lu, and has %lu elements.\n", X, N);
    } else {
        printf("FAIL: Sequence order is broken.\n");
    }

}


// To test only the generation logic
// gcc src/helpers/array_gen.c tests/test_gen.c -o test_logic
// ./test_logic
int main() {
    int N = 1000;
    ArrElement X = 50;

    printf("--- Running Array Generation Tests ---\n");

    
    ArrPtr my_arr = generate_sequencial_array(N, X); 
    run_array_gen_tests(my_arr, N, X);

    printf("--- Running Array Shuffle Tests ---\n");

    shuffle(my_arr, N);
    run_array_shuffle_test(my_arr, N, X);
    
    ArrPtr arr = generate_random_array(100);
    for (int i = 0; i < 100; i++)
    {
        printf("%lu ", arr[i]);
    }
    free(my_arr); // Always free after testing!
}
