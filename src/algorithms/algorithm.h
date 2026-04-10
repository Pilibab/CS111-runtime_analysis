#ifndef BENCHMARK_ALGORITHM_H
#define BENCHMARK_ALGORITHM_H

#include "../type.h"

#include "../helpers/swap.h"

    // a "decorator" for timing a sorting algoritm 
    // to use this we do timer(sorting_wrapper())      -> this returns the time of execution 
    void bubbleSort(ArrPtr arr, unsigned int n);
    void insertionSort(ArrPtr arr, unsigned int n);
    void selectionSort(ArrPtr arr, unsigned int n);

    void heapify(ArrPtr arr, unsigned int n, unsigned int i);
    void heapSort(ArrPtr arr, unsigned int n);

    void merge(ArrPtr arr, unsigned int left, unsigned int mid, unsigned int right);
    void mergeSortRecursive(ArrPtr arr, unsigned int left, unsigned int right);
    void handle_mergeSort(ArrPtr arr, unsigned int size); 

    // void handle_quickSort(ArrPtr arr, unsigned int size);
    // void quickSortRecursive(ArrPtr arr, unsigned int low, unsigned int high);
    // unsigned int partition(ArrPtr arr, unsigned int low, unsigned int high) ;

    ArrElement median_of_three(ArrPtr arr, unsigned int low, unsigned int high);
    unsigned int partition(ArrPtr arr, unsigned int low, unsigned int high);
    void quickSortRecursive(ArrPtr arr, unsigned int low, unsigned int high);
    void handle_quickSort(ArrPtr arr, unsigned int size) ;
#endif