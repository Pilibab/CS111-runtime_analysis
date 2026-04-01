#ifndef TYPE_H
#define TYPE_H

    // The actual data being sorted
    typedef unsigned long int ArrElement;

    // The pointer to the array of data
    typedef ArrElement* ArrPtr;

    typedef void (*SortFunc)(ArrPtr, unsigned int);

#endif