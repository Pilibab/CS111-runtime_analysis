// this will be used to initialize all test files 
#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../helpers/array_gen.h"

    bool validate_sort(unsigned long int* arr, int n, unsigned long int x) ;
    void run_array_gen_tests(unsigned long int* my_arr,unsigned int N, unsigned long int X);
    bool validate_shuffle(unsigned long int* arr, int n, unsigned long int start_v);
    void run_array_shuffle_test(unsigned long int* my_arr,unsigned int N, unsigned long int X);
#endif 