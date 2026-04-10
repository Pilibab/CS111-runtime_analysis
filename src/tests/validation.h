#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>
#include <stdio.h>
#include "../type.h"

bool validate_sort(ArrPtr arr, ArrElement n);
bool validate_shuffle(ArrPtr arr, ArrElement n, ArrElement start_v);
int  set_direction(ArrElement a, ArrElement b);

#endif