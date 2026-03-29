// this will be used to initialize all test files 
#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../helpers/array_gen.h"
#include "../type.h"




    bool validate_sort(ArrPtr arr, ArrElement n, ArrElement x) ;
    void run_array_gen_tests(ArrPtr my_arr,ArrElement N, ArrElement X);
    bool validate_shuffle(ArrPtr arr, ArrElement n, ArrElement start_v);
    void run_array_shuffle_test(ArrPtr my_arr, ArrElement N, ArrElement X);
#endif 