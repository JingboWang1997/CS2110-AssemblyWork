#include "array_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define UNUSED_PARAMETER(x) (void)(x)

 /*
  * We will be using the same tester as you, if you pass all the test cases
  * with NO memory leaks, you will receive a 100. Point allocations per test
  * case will be decided soon. Run valgrind once you are passing all the tests.
  */

/*
 * Make sure to run the tests with valgrind to check for memory leaks
 * Here are some commands that should help:
 ******************
 * make run-tests *
 ******************
 * - runs the test cases WITHOUT valgrind
 *********************
 * make run-valgrind *
 *********************
 * - runs the test cases WITH valgrind
 **************
 * make debug *
 **************
 * - runs the tests with gdb
 ***************
 * make submit *
 ***************
 * - generates the tar file you should submit to t^2
 */

/*
 * Creates an array_list with a backing array of size INIT_BACKING_SIZE.
 * on failure returns NULL
 * @returns the newly created array_list or NULL on malloc failures.
 */
array_list *create_list() {
    array_list *ptr = malloc(sizeof(array_list));
    if (ptr == NULL)
    {
      return NULL;
    }
    ptr->backing_size = INIT_BACKING_SIZE;
    ptr->size = 0;
    ptr->backing_array = malloc(INIT_BACKING_SIZE * sizeof(void *));
    if (ptr->backing_array == NULL)
    {
      free(ptr);
      return NULL;
    }
    return ptr;
}

/*
 * Adds the given data to the end of the array list.
 * If the array list is full (no new elements can fit in the backing array),
 * make sure to resize the array and copy the data over and update backing_size
 * of the array_list.
 * When resizing the array, the new backing size should be the
 * BACKING_GROWTH_FACTOR * current backing_size.
 * If malloc fails during a resize, return false but do not modify or free the
 * existing backing_array.
 * @param ar the array_list to add to
 * @param data the data to add to the array_list
 * @returns true if the data item could be added to the list successfuly, otherwise
 * return false
 */
bool add_to_array_list(array_list *ar, void *data) {
    if (ar->size < ar->backing_size)
    {
      ar->backing_array[ar->size] = data;
      ar->size += 1;
      return true;
    }
    else
    {
      //resize
      array_list *newTemp = malloc(sizeof(array_list));
      if (newTemp == NULL)
      {
        return false;
      }
      newTemp->backing_size = ar->backing_size * BACKING_GROWTH_FACTOR;
      newTemp->size = 0;
      newTemp->backing_array = malloc(ar->backing_size * BACKING_GROWTH_FACTOR);
      if (newTemp->backing_array == NULL)
      {
        free(newTemp);
        return false;
      }

      //copy over
      for (int i = 0; i < ar->size; i++) {
        newTemp->backing_array[i] = ar->backing_array[i];
      }
      newTemp->size = ar->size;
      newTemp->backing_size = ar->backing_size * BACKING_GROWTH_FACTOR;

      //free old
      free(ar->backing_array);
      free(ar);

      //add element
      newTemp->backing_array[newTemp->size] = data;
      newTemp->size += 1;
      *ar = *newTemp;
    }
    return true;
}


/*
 * Creates a shallow copy of the data in the backing_array.
 * This means creating an array that contains the same pointers as the backing
 * array.
 * NOTE: the array returned by this method should only contain size number
 * of elements (i.e it should not include the garbage values in the invalid
 * part of the backing array).
 * @param ar the array_list to copy
 * @param out_ar the pointer used to return the shallow copy of the array
 * to the caller. You should set the out_ptr to NULL on failure.
 * @returns true if the shallow copy succeeded, false otherwise.
 */
bool shallow_copy(array_list *ar, void ***out_ar) {
    void **array = malloc(ar->size * sizeof(void *));
    if (array == NULL) 
    {
      if (out_ar != NULL)
      {
        *out_ar = NULL;
        return false;
      }
    }

    for (int i = 0; i < ar->size; i++)
    {
      array[i] = ar->backing_array[i];
    }

    *out_ar = array;
    return true;
}

/*
 * Destroys the array_list.
 * This function should free all of the data in the backing array and all the
 * data used by the array_list itself.
 * You can assume free_func will not be NULL
 * @param ar the array_list to destroy
 * @param free_func the free function used to free the data of the array_list
 */
void destroy(array_list *ar, op free_func) {
  if (ar != NULL)
  {
    for (int i = 0; i < ar->size; i++)
    {
      free_func(ar->backing_array[i]);
    }
    free(ar->backing_array);
    free(ar);
  }
}

