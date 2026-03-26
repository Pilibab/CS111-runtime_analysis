#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>

// a "decorator" for timing a sorting algoritm 
// to use this we do timer(sorting_wrapper())      -> this returns the time of execution 
int timer(void (*func_ptr)());


#endif