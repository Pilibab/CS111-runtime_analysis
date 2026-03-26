#ifndef BENCHMARK_ALGORITHM_H
#define BENCHMARK_ALGORITHM_H

#include <time.h>
#include <stdbool.h>
#include "../helpers/array_gen.h"
#include "../tests/validation.h"

    // a "decorator" for timing a sorting algoritm 
    // to use this we do timer(sorting_wrapper())      -> this returns the time of execution 
    int benchmark_algorithm(void (*func_ptr)());

    struct BenchMark {
        clock_t runtime;
        bool is_sorted;
        // ArrPtr sortedArr;
    };


#endif