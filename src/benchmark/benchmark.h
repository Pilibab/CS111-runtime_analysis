#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "../type.h"
#include "../helpers/array_gen.h"
#include "../tests/validation.h"

    struct BenchMark {
        double runtime;
        bool is_sorted;
        // ArrPtr sortedArr;
    };

    // a "decorator" for timing a sorting algoritm 
    // to use this we do timer(sorting_wrapper())      -> this returns the time of execution 
    struct BenchMark benchmark_algorithm( 
        // void (*sort)(int arrLen, ArrPtr array), 
        SortFunc func, 
        unsigned int arrLen, 
        ArrPtr originalArray
    );

#endif