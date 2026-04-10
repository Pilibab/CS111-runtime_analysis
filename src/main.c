#include "main.h"

Algorithm my_algs[] = {
    {"Selection Sort", selectionSort},
    {"Bubble Sort",    bubbleSort},
    {"Insertion Sort", insertionSort},
    {"Merge Sort",     handle_mergeSort},
    {"Quick Sort",     handle_quickSort},
    {"Heap Sort",      heapSort},
};
unsigned int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
int num_sizes = 6;

/* ---------------------------------------------------------------
 * write_array_line()
 * Writes all N elements on a single space-separated line.
 * --------------------------------------------------------------- */
void write_array_line(FILE *fp, ArrPtr arr, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        fprintf(fp, "%lu", arr[i]);
        if (i < n - 1) fprintf(fp, " ");
    }
    fprintf(fp, "\n");
}

int main(int argc, char *argv[]) {

    int num_algs = 6;
    int N, choice_action, choice_generation;
    ArrPtr arr;

    printf("Select action:\n");
    printf("\t[1] Perform benchmark for {10, 100, 1000, 10000, 100000, 1000000} for all algorithms\n");
    printf("\t[2] Perform benchmark for N size array for all algorithms\n");
    scanf("%d", &choice_action);

    /* ============================================================
     * CHOICE 1 – Full benchmark over all preset N values
     * ONE .txt file for the whole run, partitioned by N
     * ============================================================ */
    if (choice_action == 1) {

        int choice_arr_type;
        printf("Perform benchmark on type ____ array:\n");
        printf("\t[1] Sorted inputs\n");
        printf("\t[2] Random inputs\n");
        scanf("%d", &choice_arr_type);

        bool is_sorted_input;
        ArrElement starting_val = 0;

        if (choice_arr_type == 1) {
            is_sorted_input = true;
            printf("Enter starting value (X): ");
            scanf(" %ld", &starting_val);
        } else if (choice_arr_type == 2) {
            is_sorted_input = false;
        } else {
            return 0;
        }

        const char *label = is_sorted_input ? "sorted" : "random";

        /* Open the single output file for the entire run */
        char filename[64];
        snprintf(filename, sizeof(filename), "output_%s.txt", label);
        FILE *out_fp = fopen(filename, "w");
        if (!out_fp) {
            printf("[Warning] Could not open output file: %s\n", filename);
            return 1;
        }

        for (int n = 0; n < num_sizes; n++) {

            if (is_sorted_input)
                arr = generate_sequencial_array(sizes[n], starting_val);
            else
                arr = generate_random_array(sizes[n]);

            /* Save original before any sorting */
            ArrPtr original = malloc(sizes[n] * sizeof(ArrElement));
            if (!original) { printf("Memory allocation failed.\n"); return 1; }
            memcpy(original, arr, sizes[n] * sizeof(ArrElement));

            /* Run benchmark and print terminal table */
            ArrPtr sorted = report_n_runtime(num_algs, 5, sizes[n], arr, is_sorted_input);

            /* Write partition for this N into the single file */
            fprintf(out_fp, "=== N=%u ===\n", sizes[n]);
            fprintf(out_fp, "Unsorted: ");
            write_array_line(out_fp, original, sizes[n]);
            fprintf(out_fp, "Sorted  : ");
            write_array_line(out_fp, sorted, sizes[n]);
            fprintf(out_fp, "\n");

            free(sorted);
            free(original);
            free(arr);
        }

        fclose(out_fp);
        printf("\n[Output] Written to %s\n", filename);

    /* ============================================================
     * CHOICE 2 – Single user-specified N
     * ONE .txt file with one partition for the chosen N
     * ============================================================ */
    } else if (choice_action == 2) {

        printf("Enter the length of the array: ");
        scanf(" %d", &N);

        printf("Select generation method:\n");
        printf("\t[1] Uniformly Random Integers [0, MAX_RANGE]\n");
        printf("\t[2] Increasing Sequence\n");
        printf("Enter choice: ");
        scanf("%d", &choice_generation);

        bool is_sorted_input;

        if (choice_generation == 1) {
            arr = generate_random_array(N);
            is_sorted_input = false;
        } else if (choice_generation == 2) {
            ArrElement starting_val;
            printf("Enter starting value (X): ");
            scanf(" %ld", &starting_val);
            arr = generate_sequencial_array(N, starting_val);
            is_sorted_input = true;
        } else {
            printf("Invalid choice.\n");
            return 1;
        }

        /* Keep a pristine copy of the original */
        ArrPtr original = malloc(N * sizeof(ArrElement));
        if (!original) { printf("Memory allocation failed.\n"); return 1; }
        memcpy(original, arr, N * sizeof(ArrElement));

        /* Print runtime table to terminal */
        printf("\n%-18s  %s\n", "Algorithm", "Runtime");
        printf("------------------------------------------\n");

        ArrPtr first_sorted = NULL;

        for (int a = 0; a < num_algs; a++) {

            ArrPtr work = malloc(N * sizeof(ArrElement));
            if (!work) { printf("Memory allocation failed.\n"); return 1; }
            memcpy(work, original, N * sizeof(ArrElement));

            clock_t t_start = clock();
            my_algs[a].func(work, (unsigned int)N);
            clock_t t_end   = clock();
            double elapsed  = (double)(t_end - t_start) / CLOCKS_PER_SEC;

            printf("%-18s  %.6f s\n", my_algs[a].name, elapsed);

            if (a == 0) {
                first_sorted = work; /* keep first result for file output */
            } else {
                free(work);
            }
        }

        printf("------------------------------------------\n");

        /* Write ONE output file with ONE partition */
        const char *label = is_sorted_input ? "sorted" : "random";
        char filename[64];
        snprintf(filename, sizeof(filename), "output_%s.txt", label);

        FILE *out_fp = fopen(filename, "w");
        if (!out_fp) {
            printf("[Warning] Could not open output file: %s\n", filename);
        } else {
            fprintf(out_fp, "=== N=%d ===\n", N);
            fprintf(out_fp, "Unsorted: ");
            write_array_line(out_fp, original, (unsigned int)N);
            fprintf(out_fp, "Sorted  : ");
            write_array_line(out_fp, first_sorted, (unsigned int)N);
            fprintf(out_fp, "\n");
            fclose(out_fp);
            printf("\n[Output] Written to %s\n", filename);
        }

        free(first_sorted);
        free(original);
        free(arr);
    }

    return 0;
}

/* ==============================================================
 * report_n_runtime()
 * Runs each algorithm 5 times and prints the runtime table to
 * the terminal. Returns a sorted copy of the array (from the
 * first algorithm's last run) for file output — caller must free.
 * ============================================================== */
ArrPtr report_n_runtime(
    int num_algs,
    int total_run,
    unsigned int n,
    ArrPtr arr,
    bool is_sorted
) {
    printf("\nResult of Experiment for %s Input, N=%u\n",
           is_sorted ? "Sorted" : "Random", n);
    printf("%-18s", "Algorithm");
    for (int run = 1; run <= total_run; run++) printf("  Run %-5d", run);
    printf(" |  Avg Time\n");
    printf("--------------------------------------------------------------------------------------------\n");

    ArrPtr first_sorted = NULL;

    for (int a = 0; a < num_algs; a++) {

        printf("%-18s", my_algs[a].name);

        double sum_time = 0;

        for (int run = 1; run <= total_run; run++) {

            ArrPtr work = malloc(n * sizeof(ArrElement));
            if (!work) { printf("allocation failed\n"); return NULL; }
            memcpy(work, arr, n * sizeof(ArrElement));

            struct BenchMark test = benchmark_algorithm(my_algs[a].func, n, work);

            printf("  %.6fs", test.runtime);
            sum_time += test.runtime;
            if (!test.is_sorted) printf("(ERR)");

            if (a == 0 && run == total_run) {
                first_sorted = work; /* keep for file output */
            } else {
                free(work);
            }
        }

        double avg = sum_time / total_run;
        printf(" |  %.6fs\n", avg);
    }

    printf("\n");
    return first_sorted;
}