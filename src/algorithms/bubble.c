#include "algorithm.h"
void bubbleSort(ArrPtr arr, unsigned int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        // Last i elements are already in place, so the loop will only num n - i - 1 times
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}