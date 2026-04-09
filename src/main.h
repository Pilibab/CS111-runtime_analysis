#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "type.h"
#include "./helpers/array_gen.h"
#include "./algorithms/algorithm.h"
#include "./benchmark/benchmark.h"


void report_n_runtime(
    int num_algs, 
    int total_run, 
    unsigned int num_sizes,
    ArrPtr arr, 
    bool is_sorted,

    // these file is strictly for writing data in a csv for easier visualization 
    FILE *avg_fp,     // for averages CSV
    FILE *runs_fp     // for detailed runs CSV
);


typedef struct {
    char *name;
    SortFunc func;
} Algorithm;

#endif