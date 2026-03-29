#ifndef BENCHMARK_ALGORITHM_H
#define BENCHMARK_ALGORITHM_H

#include "../main.h"
#include "../helpers/swap.h"

    // a "decorator" for timing a sorting algoritm 
    // to use this we do timer(sorting_wrapper())      -> this returns the time of execution 
    void bubbleSort(ArrPtr* arr, unsigned int n);
    void insertionSort(ArrPtr* arr, unsigned int n);




#endif