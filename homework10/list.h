/**
 * CS 2110 - Fall 2017 - Homework #10
 *
 * Do not modify this file!
 *
 * list.h
 */

#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

/**************************
 ** Datatype definitions **
 **************************/

/* Forward declaration
 * Don't know what a forward declaration is?
 * Consult the fountain of knowledge:
 * http://en.wikipedia.org/wiki/Forward_declaration
 */

struct _list_node;

/* Given to you for free, however you better know how to do this come time for
 * the final exam!
 * The list struct. Has a head pointer.
 */
typedef struct _list
{
    // Head pointer either points to a node with data or if the list is
    // empty NULL
    struct _list_node *head;
    // Tail pointer either points to a node with data or if the list is
    // empty NULL
    struct _list_node *tail;
    // Size of the list
    int size;
} list;

/* Given to you for free, However you better know how to do this come time for
 * the final exam!
 * A function pointer type that points to a function that takes in a void* and
 * returns nothing, call it list_op
 */
typedef void (*list_op)(void*);

/* A function pointer type that points to a function that takes in a void* and
 * a void ** (used to pass back a pointer to the newly allocated data) and returns
 * a boolean indicating success or failure, call it list_copy
 */
typedef bool (*list_copy)(const void *, void **);

/* A function pointer type that points to a function that takes in two void* and
 * returns an int, call it list_eq
 */
typedef int (*list_eq)(const void*, const void*);

/*********************************************
** Prototypes for list library functions.  **
**                                          **
** For more details on their functionality, **
** check list.c.                           **
**********************************************/

/* Creating */
list *create_list(void);
list *shallow_copy_list(list *);
list *deep_copy_list(list *, list_copy, list_op);

/* Adding */
bool push_front(list *, void *);
bool push_back(list *, void *);
bool add(list *, int index, void *);

/* Querying List */
bool front(list *, void **);
bool back(list *, void **);
bool get(list *, int, void **);
bool size(list *, int *);
bool contains(list *, void *, list_eq, void **);

/* Removing */
bool pop_front(list *, void **);
bool pop_back(list *, void **);
bool list_remove(list *, int, void **);
void empty_list(list *, list_op);

/* Traversal */
bool traverse(list *, list_op);

/* Mutators */
bool reverse(list *);
bool concat(list *, list *);

#endif
