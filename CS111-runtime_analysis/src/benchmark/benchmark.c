#include "benchmark.h"


struct BenchMark benchmark_algorithm( 
    SortFunc func, 
    unsigned int arrLen, 
    ArrPtr workingArray
) 
{
    double start = clock();
    func(workingArray, arrLen);
    double end = clock();

    double runtime = (double)(end - start) / CLOCKS_PER_SEC;

    bool is_sorted = validate_sort(workingArray, arrLen);

    return (struct BenchMark){runtime, is_sorted};
}


// struct BenchMark handle_benchmark(){} 