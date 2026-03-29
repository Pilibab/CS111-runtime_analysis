#include "benchmark.h"


struct BenchMark benchmark_algorithm( 
    void (*sort)(int arrLen, ArrPtr array), 
    ArrElement startvalue,
    int arrLen, 
    ArrPtr originalArray
) 
{
    bool isSorted = false;
    clock_t runtime = 0;

    // allocate space based on number of elements * size of each element
    ArrPtr workingCopy = malloc(arrLen * sizeof(ArrElement));

    if (workingCopy == NULL) return (struct BenchMark){0, false}; 

    // Copy the data over, this allow us to perform chain benchmarking for each algorithm  
    memcpy(workingCopy, originalArray, arrLen * sizeof(ArrElement));


    // perform benchmark
    clock_t start = clock();
    (*sort)(arrLen, workingCopy);
    clock_t end = clock();
    
    // get total run time 
    runtime = (double)(end - start) / CLOCKS_PER_SEC;

    // note that this test would fail if say [1,3,4,5] 
    // since the test expect an arrangement of incrementation by 1
    if (validate_sort(workingCopy, arrLen, startvalue)) {
        isSorted = true;
    }

    free(workingCopy);
    
    return (struct BenchMark){runtime, isSorted};
}


// struct BenchMark handle_benchmark(){} 