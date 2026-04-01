#include "main.h"

// Define a type for our sorting functions to make the code readable


// Create the list of algorithms you want to test
Algorithm my_algs[] = {
    {"Selection Sort", selectionSort},
    {"Bubble Sort",    bubbleSort},
    {"Insertion Sort", insertionSort},
    // Add the others here...
};
unsigned int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
int num_sizes = 6;


int main(int argc, char *argv[]) {

    int num_algs = 3; // Update this as you add more

    int N, choice_action, choice_generation; 
    int starting_val;
    ArrPtr arr;

    printf("Select action:\n");
    printf("\t[1] perform benchmark for {10, 100, 1000, 10000, 100000, 1000000} for all algoritm\n");
    printf("\t[2] Perform benchmark for N size array for all algorithm\n");
    scanf("%d", &choice_action); // Added the missing scanf

    if (choice_action == 1) 
    {
        for (int n = 0 ; n < num_sizes; n++) {
            arr = generate_random_array(sizes[n]);
            report_n_runtime(num_algs, 5, sizes[n], arr,false);
        }
    } else if (choice_action == 2) 
        {

        printf("Enter the length of the array: ");
        scanf(" %d", &N);

        printf("Select generation method: \n");
        printf("\t[1] Uniformly Random Integers [0, MAX_RANGE]\n");
        printf("\t[2] Increasing Sequence\n");
        printf("Enter choice: ");
        scanf("%d", &choice_generation);

        if (choice_generation == 1) {
            // random generation
            arr = generate_random_array(N);
            // report_n_runtime(num_algs, 5,10, false);

        } else if (choice_generation == 2) {
            printf("Enter starting value (X): ");
            scanf("%d", &starting_val);

            arr = generate_sequencial_array(N, starting_val);
        }
    }

    return 0;
}

// creates a report of 5 runs at n run time 
// note: this will only run once for a value of n 
void report_n_runtime(
    int num_algs, 
    int total_run, 
    unsigned int num_sizes,
    ArrPtr arr, 
    bool is_sorted
) {
    printf("\nResult of Experiment for %s Input, N=%d\n", is_sorted ? "Sorted" : "Random", num_sizes);

    // Header Row
    // %-18s = Left-aligned string, 18 characters wide
    printf("%-18s", "Algorithm");
    for (int run = 1; run <= total_run; run++) {
        printf("  Run %d   ", run);
    }
    printf(" |  Avg Time\n");
    
    printf("----------------------------------------------------------------------------------------\n");

    // Table Body
    for (int a = 0; a < num_algs; a++) {
        printf("%-18s", my_algs[a].name);
        
        double sum_time = 0;

        for (int run = 1; run <= total_run; run++) {
            struct BenchMark test = benchmark_algorithm(my_algs[a].func, num_sizes, arr);
            
            // Assuming test.runtime is now a double (seconds)
            printf("  %.6fs", test.runtime);
            sum_time += test.runtime;
        }

        double avg = sum_time / total_run;
        printf(" |  \033[1;32m%.6fs\033[0m\n", avg); // \033[1;32m makes the average green in most terminals
    }
};

