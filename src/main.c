#include "main.h"

// Create the list of algorithms you want to test
Algorithm my_algs[] = {
    {"Selection Sort", selectionSort},
    {"Bubble Sort",    bubbleSort},
    {"Insertion Sort", insertionSort},
    {"Merge Sort", handle_mergeSort},
    {"Quick Sort", handle_quickSort},
    {"Heap Sort", heapSort},
};
// unsigned int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
// int num_sizes = 6;

unsigned int sizes[] = {1000000};
int num_sizes = 1;
int main(int argc, char *argv[]) {

    srand(time(NULL));  // seed once
    int num_algs = 6; // !Update this as you add more

    int N, choice_action, choice_generation; 

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
            FILE *show_sorted = fopen("sorted/before_after.txt","w");
            if (!avg_fp || !runs_fp || !show_sorted) {
                printf("Error opening files\n");
                return 1;
            }

            // CSV headers
            fprintf(avg_fp, "N,Selection Sort,Bubble Sort,Insertion Sort,Merge Sort,Quick Sort,Heap Sort\n");
            fprintf(runs_fp, "InputType,N,Algorithm,Run,Time\n");



            for (int n = 0 ; n < num_sizes; n++) {

                report_n_runtime(
                    num_algs, 
                    5, 
                    sizes[n], 
                    true, 
                    avg_fp, 
                    runs_fp,
                    show_sorted
                );
            }

            fclose(avg_fp);
            fclose(show_sorted);
            fclose(runs_fp);

        }   else if (choice_arr_type == 2) {
            FILE *avg_fp = fopen("random/average_results.csv", "w");
            FILE *runs_fp = fopen("random/detailed_runs.csv", "w");
            FILE *show_sorted = fopen("random/before_after.txt","w");


            if (!avg_fp || !runs_fp || !show_sorted) {
                printf("Error opening files\n");
                return 1;
            }

            // CSV headers
            fprintf(avg_fp, "N,Selection Sort,Bubble Sort,Insertion Sort,Merge Sort,Quick Sort,Heap Sort\n");
            fprintf(runs_fp, "InputType,N,Algorithm,Run,Time\n");

            for (int n = 0 ; n < num_sizes; n++) {

                report_n_runtime(
                    num_algs, 
                    5, 
                    sizes[n], 
                    false, 
                    avg_fp, 
                    runs_fp,
                    show_sorted
                );
            }

            fclose(avg_fp);
            fclose(runs_fp);
            fclose(show_sorted);
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

        report_n_runtime(
                num_algs, 
                5, 
                N, 
                (choice_generation == 2), // true if Increasing Sequence
                stdout, // Sending CSV output to terminal for a quick look
                stdout, 
                stdout
            );
    }
    return 0;
}

// creates a report of 5 runs at n run time 
// note: this will only run once for a value of n 
void report_n_runtime(
    int num_algs, 
    int total_run, 
    unsigned int num_sizes,
    bool is_sorted,

    // these file is strictly for writing data in a csv for easier visualization 
    FILE *avg_fp,     // for averages CSV
    FILE *runs_fp,     // for detailed runs CSV
    FILE *sample_sorted 
) {
    ArrPtr master_arr = NULL;

    if (is_sorted) {
        // !================================
        ArrElement starting_val = 0;
        printf("Enter starting value (X): ");
        scanf("%ld", &starting_val);

        master_arr = generate_sequencial_array(num_sizes, starting_val);
    }

    fprintf(avg_fp, "%d,", num_sizes);
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
            ArrPtr workingCopy = NULL;
            ArrPtr originalRef = NULL;

            if (is_sorted) {
                workingCopy = malloc(num_sizes * sizeof(ArrElement));
                memcpy(workingCopy, master_arr, num_sizes * sizeof(ArrElement));
                originalRef = master_arr; // Log from the template
            } else {
                ArrPtr temp = generate_random_array(num_sizes);
                workingCopy = malloc(num_sizes * sizeof(ArrElement));
                memcpy(workingCopy, temp, num_sizes * sizeof(ArrElement));
                originalRef = temp; // originalRef now points to a unique, unsorted block
            }
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
            // print only if the array is 100 elem justification if it 
            // if it works for small sze array it will work for large array 
            if (num_sizes <= 10000 && a == num_algs - 1 && run == total_run) {

                fprintf(sample_sorted, "========================================\n");
                fprintf(sample_sorted, "Input Type: %s\n", is_sorted ? "Sorted" : "Random");
                fprintf(sample_sorted, "N = %d\n\n", num_sizes);

                fprintf(sample_sorted, "Original:\n");
                for (unsigned int i = 0; i < num_sizes; i++) {
                    fprintf(sample_sorted, "%ld ", originalRef[i]);
                }

                fprintf(sample_sorted, "\n\nSorted (%s):\n", my_algs[a].name);
                for (unsigned int i = 0; i < num_sizes; i++) {
                    fprintf(sample_sorted, "%ld ", workingCopy[i]);
                }

                fprintf(sample_sorted, "\n========================================\n\n");
            }

            free(workingCopy);
            // Free the temporary random array created in the 'else' block
            if (!is_sorted) {
                free(originalRef); 
            }

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
    fprintf(avg_fp, "\n");
    if (is_sorted && master_arr != NULL) {
        free(master_arr); // Free the template once at the very end
    }
};

