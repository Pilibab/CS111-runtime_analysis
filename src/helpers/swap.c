#include "swap.h"

void swap(ArrElement *a, ArrElement *b) {
    ArrElement temp = *a;
    *a = *b;
    *b = temp;
}