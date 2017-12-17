#ifndef TESTS_H
#define TESTS_H

#include "array_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define HISTORY_SIZE 100
#define NUM_TESTS 12

#define TERM_RED     "\x1b[31m"
#define TERM_GREEN   "\x1b[32m"
#define TERM_RESET   "\x1b[0m"

typedef struct __malloc_info {
    int successful_malloc_calls;
    int count;
    size_t last_called_size[HISTORY_SIZE];
    void* calls[HISTORY_SIZE];
} malloc_info;

typedef struct _person {
    char* name;
    int age;
} person;

typedef struct _student_test {
    int (*tester)(void);
    char* name;
    int value;
    bool passed;
} student_test;

void* __wrap_malloc (size_t size);
void* __wrap_calloc(size_t nitems, size_t size);
void* __wrap_realloc(void *ptr, size_t size);
void __wrap_free(void *ptr);

void cleanup(malloc_info* info);
bool in_last_n(malloc_info* info, size_t val, int n);
bool cleaned(malloc_info* info);

extern void* __real_malloc (size_t size);
extern void __real_free(void *ptr);

array_list *ta_create_list();

// tests
int test_create_list();
int test_create_list_fail_second();
int test_create_list_fail_first();
int test_add_null();
int test_add_1();
int test_add_9();
int test_add_10();
int test_add_11();
int test_add_11_fail();
int test_add_20();
int test_shallow_copy();
int test_shallow_copy_fail();
int test_destroy();

#endif //TESTS_H
