#include "main.h"

// Define a type for our sorting functions to make the code readable


// Create the list of algorithms you want to test
Algorithm my_algs[] = {
    {"Selection Sort", selectionSort},
    {"Bubble Sort",    bubbleSort},
    {"Insertion Sort", insertionSort},
    {"Merge Sort", handle_mergeSort},
    {"Quick Sort", handle_quickSort},
    {"Heap Sort", heapSort},
    // Add the others here...
};
unsigned int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
int num_sizes = 6;


int main(int argc, char *argv[]) {

    int num_algs = 6; // Update this as you add more

    int N, choice_action, choice_generation; 
    ArrPtr arr;

    printf("Select action:\n");
    printf("\t[1] perform benchmark for {10, 100, 1000, 10000, 100000, 1000000} for all algoritm\n");
    printf("\t[2] Perform benchmark for N size array for all algorithm\n");
    scanf("%d", &choice_action); // Added the missing scanf

    if (choice_action == 1) 
    {
        int choice_arr_type = 1;
        printf("Perform benchmark on type ____ array:\n");
        printf("\t[1] sorted inputs\n");
        printf("\t[2] random inputs\n");
        scanf("%d", &choice_arr_type); // Added the missing scanf


        if (choice_arr_type == 1) {

            FILE *avg_fp = fopen("sorted/average_results.csv", "w");
            FILE *runs_fp = fopen("sorted/detailed_runs.csv", "w");

            if (!avg_fp || !runs_fp) {
                printf("Error opening files\n");
                return 1;
            }

            // CSV headers
            fprintf(avg_fp, "N,Selection Sort,Bubble Sort,Insertion Sort,Merge Sort,Quick Sort,Heap Sort\n");
            fprintf(runs_fp, "InputType,N,Algorithm,Run,Time\n");

            ArrElement starting_val = 0;

            printf("Enter starting value (X): ");
            scanf(" %ld", &starting_val);

            for (int n = 0 ; n < num_sizes; n++) {
                arr = generate_sequencial_array(sizes[n], starting_val);

                report_n_runtime(
                    num_algs, 
                    5, 
                    sizes[n], 
                    arr, 
                    true, 
                    avg_fp, 
                    runs_fp
                );
            }

            fclose(avg_fp);
            fclose(runs_fp);
        }   else if (choice_arr_type == 2) {
            FILE *avg_fp = fopen("random/average_results.csv", "w");
            FILE *runs_fp = fopen("random/detailed_runs.csv", "w");

            if (!avg_fp || !runs_fp) {
                printf("Error opening files\n");
                return 1;
            }

            // CSV headers
            fprintf(avg_fp, "N,Selection Sort,Bubble Sort,Insertion Sort,Merge Sort,Quick Sort,Heap Sort\n");
            fprintf(runs_fp, "InputType,N,Algorithm,Run,Time\n");

            for (int n = 0 ; n < num_sizes; n++) {
                arr = generate_random_array(sizes[n]);

                report_n_runtime(
                    num_algs, 
                    5, 
                    sizes[n], 
                    arr, 
                    false, 
                    avg_fp, 
                    runs_fp
                );
            }

            fclose(avg_fp);
            fclose(runs_fp);
        } else return 0; 

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
            ArrElement starting_val;
            printf("Enter starting value (X): ");
            scanf("% ld", &starting_val);

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
    bool is_sorted,

    // these file is strictly for writing data in a csv for easier visualization 
    FILE *avg_fp,     // for averages CSV
    FILE *runs_fp     // for detailed runs CSV
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

            // Allocate fresh copy
            ArrPtr workingCopy = malloc(num_sizes * sizeof(ArrElement));
            if (workingCopy == NULL) {
                printf("allocation failed\n");
                return;
            }

            // Copy original array
            memcpy(workingCopy, arr, num_sizes * sizeof(ArrElement));

            // Benchmark ONLY sorting
            struct BenchMark test = benchmark_algorithm(
                my_algs[a].func, 
                num_sizes, 
                workingCopy
            );

            printf("  %.6fs", test.runtime);
            sum_time += test.runtime;

            // Optional: safety check
            if (!test.is_sorted) {
                printf(" (ERROR)");
            }

            free(workingCopy);

            // logs the time each run 
            fprintf(runs_fp, "%s,%d,%s,%d,%.6f\n",
                is_sorted ? "Sorted" : "Random",
                num_sizes,
                my_algs[a].name,
                run,
                test.runtime
            );
        }

        double avg = sum_time / total_run;
        printf(" |  %.6fs\n", avg);

        // write log for avg
        fprintf(avg_fp, "%.6f", avg);

        if (a < num_algs - 1) {
            fprintf(avg_fp, ",");
        }
    }
};

