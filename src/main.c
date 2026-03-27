#include "main.h"


int main() {
    int N; 
    int starting_val;

    printf("Enter the length of the array: ");
    scanf(" %d", &N);
    printf("Enter the length of the array: ");
    scanf(" %d", &starting_val);

    ArrPtr arr = generate_array(N, starting_val);

    printf("\narray: ");
    for (int i = 0; i < N / 5; i++) {
        printf(" %lu", arr[i]);
    }
    return 0;
}

