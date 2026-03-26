#ifndef ARRAY_GEN_H
#define ARRAY_GEN_H

#include <stdlib.h>
#include <stdio.h>

    // The actual data being sorted
    typedef ArrElement ArrElement;

    // The pointer to the array of data
    typedef ArrElement* ArrPtr;
    ArrPtr generate_array(int n, int starting_val);
    void shuffle(ArrPtr arr, int n);                    // modify the array (shuffles it)

#endif