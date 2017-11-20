/**
 * CS 2110 - Fall 2017 - Homework #10
 *
 * @author Jingbo Wang
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return false if
 * the function returns a bool).
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/* The node struct. Has a next pointer, and data. */
/* DO NOT MODIFY THIS STRUCTURE */
/* Only this file should deal with the node struct */
typedef struct _list_node
{
    struct _list_node *next;
    void *data;
} node;

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked list. */
static node *create_node(void *data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void *data)
{
  node *ptr = malloc(sizeof(node));
  if (ptr == NULL)
  {
    return NULL;
  }
  ptr->next = NULL;
  ptr->data = data;
  return ptr;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head and tail to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new list or NULL on failure
  */
list *create_list(void)
{
  list *ptr = malloc(sizeof(list));
  if (ptr == NULL)
  {
    return NULL;
  }
  ptr->head = NULL;
  ptr->tail = NULL;
  ptr->size = 0;
  return ptr; 
}

/** shallow_copy_list
  *
  * Creates a shallow copy of the list. This means a new list structure and
  * nodes should be created, but each node will point to the same data as the
  * list passed in.
  *
  * if malloc fails or the list is NULL, return NULL to indicate failure. If
  * any memory allocations failures occur, your code must not leak memory. That
  * is, if create_node() returns NULL, you must go back and free any nodes
  * you've allocated so far and the new list.
  *
  * @param listToCopy the list to shallow copy
  * @return a pointer to the new list or NULL on failure
  */
list *shallow_copy_list(list *listToCopy)
{
  // if malloc fails or the list is NULL, return NULL to indicate failure
  int flag = 0;

  // a new list structure
  list *ptr = create_list();
  if (listToCopy == NULL || ptr == NULL)
  {
    free(ptr);
    return NULL;
  }

  node *cur = listToCopy->head;
  for (int i = 0; i < listToCopy->size; i++)
  {
    if (!push_back(ptr, cur->data))
    {
      flag = 1;
      break;
    }
    cur = cur->next;
  }

  if (flag)
  {
    node *cur = ptr->head;
    node *next;
    while (cur != NULL)
    {
      next = cur->next;
      free(cur);
      cur = next;
    }
    free(ptr);
    return NULL;
  }

  return ptr;

}

/** deep_copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any structure must copy
  * EVERYTHING!
  *
  * If listToCopy or copyFunc is NULL, return NULL. For memory allocations
  * failures, including if copyFunc() returns false (indicating a memory
  * allocation failure), your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must go back
  * and free all data in the new list, nodes in the new list, and the new list
  * itself.
  *
  * @param listToCopy A pointer to the list structure to make a copy of
  * @param copyFunc A function pointer to a function that makes a copy of the
  *                 data that's being used in this list, allocating space for
  *                 every part of that data on the heap. This is some function
  *                 you must write yourself for testing, tailored specifically
  *                 to whatever context you're using the list for in your test.
  *                 If copyFunc returns false for any element, deep_copy_list()
  *                 should return NULL.
  * @param freeFunc function used to free the nodes' data in the case of a
  *                 memory allocation failure when copying (see above)
  * @return The list structure created by copying the old one, or NULL on
  *         failure
  */
list *deep_copy_list(list *listToCopy, list_copy copyFunc, list_op freeFunc)
{
  // If listToCopy or copyFunc is NULL, return NULL
  int flag = 0;

  // a new list structure
  list *ptr = create_list();
  if (listToCopy == NULL || ptr == NULL || copyFunc == NULL)
  {
    free(ptr);
    return NULL;
  }

  node *cur = listToCopy->head;
  for (int i = 0; i < listToCopy->size; i++)
  {
    void *newData;
    bool copy = copyFunc(cur->data, &newData);
    if (!copy)
    {
      flag = 1;
      break;
    }
    if (!push_back(ptr, newData))
    {
      flag = 1;
      break;
    }
    cur = cur->next;
  }

  if (flag)
  {
    node *cur = ptr->head;
    node *next;
    while (cur != NULL)
    {
      next = cur->next;
      freeFunc(cur->data);
      free(cur);
      cur = next;
    }
    free(ptr);
    return NULL;
  }

  return ptr;
}

/** push_front
  *
  * Adds the element at the front of the list.
  *
  * @param listToPrependTo a pointer to the list structure.
  * @param data the data to add to the list.
  * @return false if the list is NULL, true if successful.
  */
bool push_front(list *listToPrependTo, void *data)
{
    if (listToPrependTo == NULL)
    {
      return false;
    }
    node *n = create_node(data);
    if (n == NULL)
    {
      return false;
    }
    if (listToPrependTo->size == 0)
    {
      listToPrependTo->head = n;
      listToPrependTo->tail = n;
      listToPrependTo->size = 1;
    }
    else
    {
      node *oldHead = listToPrependTo->head;
      n->next = oldHead;
      listToPrependTo->head = n;
      listToPrependTo->size++;
    }
    return true;
}

/** push_back
  *
  * Adds the element to the back of the list.
  *
  * @param listToAppendTo a pointer to the list structure.
  * @param data the data to add to the list.
  * @return false if the list is NULL, true if successful.
  */
bool push_back(list *listToAppendTo, void *data)
{
    if (listToAppendTo == NULL)
    {
      return false;
    }
    node *n = create_node(data);
    if (n == NULL)
    {
      return false;
    }
    if (listToAppendTo->size == 0)
    {
      listToAppendTo->head = n;
      listToAppendTo->tail = n;
      listToAppendTo->size = 1;
    }
    else
    {
      node *oldTail = listToAppendTo->tail;
      oldTail->next = n;
      listToAppendTo->tail = n;
      listToAppendTo->size++;
    }
    return true;
}

/** add
  *
  * Add the element at the specified index in the list. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the list,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the list,
  * you should be able to add to index 2 but no further.
  *
  * @param listToAddTo a pointer to the list structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the list
  * @return false if the index is out of bounds or the list is NULL
  *         (do not add the data in this case)
  *         otherwise return true
  */
bool add(list *listToAddTo, int index, void *data)
{
    if (listToAddTo == NULL || index < 0 || index > listToAddTo->size)
    {
      return false;
    }
    if (index == 0)
    {
      return push_front(listToAddTo, data);
    }
    else if (index == listToAddTo->size)
    {
      return push_back(listToAddTo, data);
    }
    
    node *cur = listToAddTo->head;
    node *previous;
    for (int i = 0; i < index; i++)
    {
      previous = cur;
      cur = cur->next;
    }
    node *n = create_node(data);
    if (n == NULL)
    {
      return false;
    }
    previous->next = n;
    n->next = cur;
    listToAddTo->size++;
    return true; 
}

/** front
  *
  * Gets the data at the front of the list
  * If the list is empty or the list is NULL, return false.
  *
  * @param listToGetFrontOf a pointer to the list
  * @param dataOut A pointer to a pointer used to return the data at the first
  *                node in the list or NULL on failure.
  * @return false if dataOut is NULL or the list is NULL or empty, true if
  *         successful.
  */
bool front(list *listToGetFrontOf, void **dataOut)
{
    if (dataOut == NULL || listToGetFrontOf == NULL || listToGetFrontOf->size == 0)
    {
      //*dataOut = NULL;
      return false;
    }
    node *front = listToGetFrontOf->head;
    *dataOut = front->data;
    return true;
}

/** back
  *
  * Gets the data at the back of the list
  * If the list is empty or the list is NULL, return false.
  *
  * @param listToGetBackOf a pointer to the list
  * @param dataOut A pointer to a pointer used to return the data at the last
  *                node in the list or NULL on failure.
  * @return false if dataOut is NULL or the list is NULL or empty, true
  *         otherwise
  */
bool back(list *listToGetBackOf, void **dataOut)
{
    if (dataOut == NULL || listToGetBackOf == NULL || listToGetBackOf->size == 0)
    {
      //*dataOut = NULL;
      return false;
    }
    node *back = listToGetBackOf->tail;
    *dataOut = back->data;
    return true;
}

/** get
  *
  * Gets the data at the specified index in the list
  *
  * @param listToGetDataFrom a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the list or NULL on failure.
  * @return false if dataOut is NULL or index is out of range of the list or
  *         the list is NULL, true otherwise
  */
bool get(list *listToGetDataFrom, int index, void **dataOut)
{
    if (listToGetDataFrom == NULL || dataOut == NULL || index < 0 || index >= listToGetDataFrom->size)
    {
      //*dataOut = NULL;
      return false;
    }
    node *cur = listToGetDataFrom->head;
    for (int i = 0; i < index; i++)
    {
      cur = cur->next;
    }
    *dataOut = cur->data;
    return true;
}

/** size
  *
  * Gets the size of the list
  *
  * if the list is NULL, return false.
  *
  * @param listToGetSizeOf a pointer to the list structure
  * @param A pointer used to return the size of the list, set to -1 on NULL list
  * @return false if sizeOut is NULL or list is NULL, true otherwise
  */
bool size(list *listToGetSizeOf, int *sizeOut)
{
    if (listToGetSizeOf == NULL || sizeOut == NULL)
    {
      return false;
    }

    *sizeOut = listToGetSizeOf->size;
    return true;
}

/** contains
  *
  * Traverses the list, trying to see if the list contains some data.
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * comparator says is equal. For instance, if you have a list of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 24, you could create a new
  * person struct (<NULL>, 24) with a comparator that returns 0 if age == 24 and
  * pass that into this function as "data" along with comparator. contains()
  * would then return (Nick, 24) In other words, data will be something with
  * value equality to what is in the list, but not necessarily something with
  * reference equality. Value equality will be defined by comparator.
  *
  * If there are multiple pieces of data in the list which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param listToSearch a pointer to the list structure
  * @param data The data, to see if it exists in the list
  * @param comparator A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers. Think of
  *                a comparator's compare function from Java.
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the list or NULL on failure
  * @return false if dataOut is NULL, list is NULL, comparator is NULL, or the
  *               list does not contain data, else true
  */
bool contains(list *listToSearch, void *data, list_eq comparator, void **dataOut)
{
    if (dataOut == NULL || listToSearch == NULL || comparator == NULL || listToSearch->size == 0)
    {
      //*dataOut = NULL;
      return false;
    }

    node *cur = listToSearch->head;
    for (int i = 0; i < listToSearch->size; i++)
    {
      if (!comparator(cur->data, data))
      {
        *dataOut = cur->data;
        return true;
      }
      cur = cur->next;
    }
    *dataOut = NULL;
    return false;
}


/** pop_front
  *
  * Removes the node at the front of the list, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the list.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                node or NULL on failure
  * @return false if dataOut is NULL or the list is NULL or empty, else true
  */
bool pop_front(list *listToPopFrom, void **dataOut)
{
    if (dataOut == NULL || listToPopFrom == NULL || listToPopFrom->size == 0)
    {
      //*dataOut = NULL;
      return false;
    }

    node *head = listToPopFrom->head;
    listToPopFrom->head = head->next;
    listToPopFrom->size--;
    *dataOut = head->data;
    if (listToPopFrom->size == 0)
    {
      listToPopFrom->tail = NULL;
    }
    free(head);
    return true;
}

/** pop_back
  *
  * Removes the node at the back of the list, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the list.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                node or NULL on failure
  * @return false if dataOut is NULL or the list is NULL or empty, else true
  */
bool pop_back(list *listToPopFrom, void **dataOut)
{
    if (dataOut == NULL || listToPopFrom == NULL || listToPopFrom->size == 0)
    {
      //*dataOut = NULL;
      return false;
    }

    if (listToPopFrom->size == 1)
    {
      pop_front(listToPopFrom, dataOut);
    }

    node *tail = listToPopFrom->tail;
    node *beforeTail = listToPopFrom->head;
    for (int i = 1; i < listToPopFrom->size-1; i++)
    {
      beforeTail = beforeTail->next;
    }
    listToPopFrom->tail = beforeTail;
    listToPopFrom->size--;
    *dataOut = tail->data;
    free(tail);
    return true;
}

/** list_remove
  *
  * Removes the data from the specified index in the list
  *
  * @param listToRemoveFrom a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *                specified index in the list or NULL on failure
  * @return false if dataOut is NULL or list is NULL or index is out of range
  *         of the list, else true
  */
bool list_remove(list *listToRemoveFrom, int index, void **dataOut)
{
    if (listToRemoveFrom == NULL || dataOut == NULL || index < 0 || index >= listToRemoveFrom->size)
    {
      return false;
    }
    if (index == 0)
    {
      return pop_front(listToRemoveFrom, dataOut);
    }
    else if (index == listToRemoveFrom->size-1)
    {
      return pop_back(listToRemoveFrom, dataOut);
    }
    
    node *cur = listToRemoveFrom->head;
    node *previous;
    for (int i = 0; i < index; i++)
    {
      previous = cur;
      cur = cur->next;
    }
    *dataOut = cur->data;
    
    previous->next = cur->next;
    cur->next = NULL;
    listToRemoveFrom->size--;
    free(cur);
    return true;
}


/** empty_list
  *
  * Empties the list. After this is called, the list should be empty.
  * This does not free the list struct itself, just all nodes and data within.
  * Make sure to check that listToEmpty and freeFunc are not NULL before using
  * them.
  *
  * @param listToEmpty a pointer to the list structure
  * @param freeFunc function used to free the nodes' data.
  */
void empty_list(list *listToEmpty, list_op freeFunc)
{
  if (listToEmpty != NULL && freeFunc != NULL)
  {
    node *cur = listToEmpty->head;
    node *next;
    while (cur != NULL)
    {
      next = cur->next;
      freeFunc(cur->data);
      free(cur);
      cur = next;
    }
  }
  listToEmpty->size = 0;
  listToEmpty->head = NULL;
  listToEmpty->tail = NULL;
}

/** traverse
  *
  * Traverses the list, calling a function on each node's data.
  *
  * @param listToTraverse a pointer to the list structure
  * @param doFunc a function that does something to each node's data.
  * @return true if the traversal was a success, false otherwise
  *         (listToTraverse1 or doFunc is null)
  */
bool traverse(list *listToTraverse, list_op doFunc)
{
    if (listToTraverse == NULL || doFunc == NULL)
    {
      return false;
    }

    node *cur = listToTraverse->head;
    node *next;
    while (cur != NULL)
    {
      next = cur->next;
      doFunc(cur->data);
      cur = next;
    }

    return true;
}

/** reverse
  *
  * Reverses the singly linked list in place.
  *
  * @param listToReverse to append to.
  * @return true if the operation was a success, false otherwise (listToReverse
  *         was NULL)
  */
bool reverse(list *listToReverse)
{
    if (listToReverse == NULL)
    {
      return false;
    }

    node *previous = listToReverse->head;
    node *cur = previous->next; 
    node *next = cur->next;
    while (cur != listToReverse->tail)
    {
      if (previous == listToReverse->head)
      {
        previous->next = NULL;
      }
      if (next == listToReverse->tail)
      {
        next->next = cur;
      }
      cur->next = previous;

      previous = cur;
      cur = next;
      next = next->next;
    }

    node *temp = listToReverse->head;

    listToReverse->head = listToReverse->tail;
    listToReverse->tail = temp;

    return true;;
}

/** concat
  *
  * Concatinates firstList and secondList. This function should append
  * secondList to the end of firstList.
  *
  * NOTE: this function will effectively empty lastList onto firstList which
  *       means that lastList will be empty (head == tail == NULL and size == 0)
  *       at the end of the function and firstList will contain all the elements
  *       from both lists. Be sure to update the size, head, and tail pointers
  *       accordingly.
  *
  * example: if firstList is a->b->c and second list is d->e->f
  * after the function call, firstList will be a->b->c->d->e->f and
  * secondList will be empty.
  *
  *
  * @param firstList to append to.
  * @param secondList the list to append to firstList
  * @return true if the operation was a success, false otherwise (firstList or
  *         secondList is null)
  */
bool concat(list *firstList, list *lastList)
{
  if (firstList == NULL || lastList == NULL)
  {
    return false;
  }
  firstList->tail->next = lastList->head;
  firstList->tail = lastList->tail;
  firstList->size += lastList->size;

  lastList->head = NULL;
  lastList->tail = NULL;
  lastList->size = 0;
  return true;
}
