#include <clock.h>


double timer(void (*sort_wrapper)(void)) 
{
    struct timespec time; 
    clock_t start = clock;
    (*sort_wrapper)();
    clock_t end = clock();
    
    return (double)(end - start) / CLOCKS_PER_SEC;
}