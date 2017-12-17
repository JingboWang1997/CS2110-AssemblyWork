#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>

// the initial size of the backing array upon array_list creation
#define INIT_BACKING_SIZE 10
// the multiplier used to determine the new size of the backing array if you
// run out of space in the current backing array.
// A more detailed description on how to find the new backing size when
// growing the array is in array_list.c
#define BACKING_GROWTH_FACTOR 2

typedef struct _array_list {
    // The max number of elements the backing_array can hold (referred to as N in the pdf)
    unsigned int backing_size;
    // The number of elements in the array list (sometimes referred to as S
    // in the pdf)
    unsigned int size;
    // The array that holds the data
    void **backing_array;
} array_list;

// function pointer that takes in a void pointer and returns nothing.
typedef void (*op)(void *);

// See the array_list.c file for more information about these functions.
array_list *create_list();
bool add_to_array_list(array_list *, void *);
bool shallow_copy(array_list *, void ***);
void destroy(array_list *,op);

#endif //ARRAY_LIST_H
