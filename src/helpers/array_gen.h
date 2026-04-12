#ifndef ARRAY_GEN_H
#define ARRAY_GEN_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../type.h"
#include "swap.h"

#define MAX_RANGE 1000000UL
    ArrPtr generate_random_array(unsigned int N);
    ArrPtr generate_sequencial_array(unsigned int n, ArrElement starting_val);
    void shuffle(ArrPtr arr, int n);                    // modify the array (shuffles it)

#endif