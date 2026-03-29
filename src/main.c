#include "main.h"


int main(int argc, char *argv[]) {
    unsigned int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
    int num_sizes = 6;

    int N, choice; 
    int starting_val;
    ArrPtr arr;

    printf("Enter the length of the array: ");
    scanf(" %d", &N);


    // TODO ask if array is incremental or uniformly random at range [0, max_range]
    printf("Select generation method: \n");
    printf("\t[1] Uniformly Random Integers [0, MAX_RANGE]\n");
    printf("\t[2] Increasing Sequence\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // random generation
        arr = generate_random_array(N);
    } else if (choice == 2) {
        printf("Enter starting value (X): ");
        scanf("%d", &starting_val);

        arr = generate_sequencial_array(N, starting_val);

    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }


    printf("\n sample array: ");
    for (int i = 0; i < 10; i++) {
        printf(" %lu", arr[i]);
    }

    

    return 0;
}

