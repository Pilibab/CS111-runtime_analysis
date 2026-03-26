// this will be used to initialize all test files 
#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../helpers/array_gen.h"
#include "../main.h"


    bool validate_sort(ArrPtr arr, int n, ArrElement x) ;
    void run_array_gen_tests(ArrPtr my_arr,unsigned int N, ArrElement X);
    bool validate_shuffle(ArrPtr arr, int n, ArrElement start_v);
    void run_array_shuffle_test(ArrPtr my_arr,unsigned int N, ArrElement X);
#endif 