#ifndef ARRAY_GEN_H
#define ARRAY_GEN_H

#include <stdlib.h>
#include <stdio.h>
#include "../main.h"
#include "swap.h"

    ArrPtr generate_sequencial_array(int n, int starting_val);
    void shuffle(ArrPtr arr, int n);                    // modify the array (shuffles it)

#endif