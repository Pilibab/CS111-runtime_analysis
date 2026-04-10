#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "type.h"
#include "./helpers/array_gen.h"
#include "./algorithms/algorithm.h"
#include "./benchmark/benchmark.h"

typedef struct {
    char *name;
    SortFunc func;
} Algorithm;

void   write_array_line(FILE *fp, ArrPtr arr, unsigned int n);

ArrPtr report_n_runtime(
    int num_algs,
    int total_run,
    unsigned int n,
    ArrPtr arr,
    bool is_sorted
);

#endif