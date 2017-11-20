#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/* Obtained from StackOverflow -- not portable, so might not work on your terminal */
/* https://stackoverflow.com/questions/1961209/making-some-text-in-printf-appear-in-green-and-red */
/* Works on mine in Ubuntu 16.04 */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#ifndef NDEBUG
    #define TEST_ASSERT(condition, condition_text) ( { \
    int retval; retval = (condition) ? 1 : \
            fprintf(stderr, "\033[31m[ERR] Assertion failed at %s:%d inside function %s with condition (%s)\n", __FILE__, __LINE__, __FUNCTION__, condition_text) && 0; retval; } )
#else
    #define TEST_ASSERT(condition) ((void) 0)
#endif

typedef void (*test)(void);

typedef struct {
    test t;
    char* name;
} test_s;

typedef enum { CS2110, CS2340, CS1332, CS1331 } Class;

typedef struct {
  int id;
  char* fname;
  char* lname;
  Class class;
  float gpa;
} Student;

int last_student_printed = 0;

Student* create_student(int id, const char* fname, const char* lname, Class class, float gpa) {
    Student* s = malloc(sizeof(Student));
    if (!s) { return NULL; }
    s->fname = malloc(strlen(fname) + 1);
    if (!s->fname) { return NULL; }
    strcpy(s->fname, fname);
    s->lname = malloc(strlen(lname) + 1);
    if (!s->lname) { return NULL; }
    strcpy(s->lname, lname);
    s->class = class;
    s->gpa = gpa;
    s->id = id;
    return s;
}

void print_student(void* data) {
    Student* s = (Student*) data;
    last_student_printed = s->id;
    printf(MAGENTA "[TEST] Student (ptr: %p) => id: %d, fname: %s, lname: %s, class: %d, gpa: %f\n", s, s->id, s->fname, s->lname, s->class, s->gpa);
}

bool copy_student(const void* data, void** dataOut) {
    Student* old = (Student*) data;
    Student* new = create_student(old->id, old->fname, old->lname, old->class, old->gpa);
    if (new) {
    *dataOut = new;
    }
    return !!new;
}

void free_student(void* data) {
    Student* toFree = (Student*) data;
    free(toFree->fname);
    free(toFree->lname);
    free(toFree);
    data = NULL;
}

int student_id_comp(const void* data1, const void* data2) {
    if (data1 && data2) {
        Student* s1 = (Student*) data1;
        Student* s2 = (Student*) data2;
        return s1->id - s2->id;
    } else {
    return 1;
    }
}

void test_create_list_makes_sense() {
    list* list = create_list();
    int a = TEST_ASSERT(list->size == 0, "list->size == 0");
    int b = TEST_ASSERT(!list->head, "!list->head");
    int c = TEST_ASSERT(!list->tail, "!list->tail");
    if (a && b && c) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    free(list);
}

void test_front_null_list_null_dataout() {
    int a = TEST_ASSERT(!front(NULL, NULL), "!front(NULL, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_front_null_list() {
    void** dataOut = malloc(sizeof(void**));
    int data = 5;
    *dataOut = &data;
    int a = TEST_ASSERT(!front(NULL, dataOut), "!front(NULL, dataOut) (should have returned false)");
    int b = TEST_ASSERT(!*dataOut, "!*dataOut (*dataOut should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataOut);
}

void test_front_empty_list() {
    void** dataOut = malloc(sizeof(void**));
    list* list = create_list();
    int data = 5;
    *dataOut = &data;
    int a = TEST_ASSERT(!front(list, dataOut), "!front(list, dataOut) (should have returned false)");
    int b = TEST_ASSERT(!*dataOut, "!*dataOut (*dataOut should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataOut);
    free(list);
}

void test_front_empty_list_null_dataout() {
    list* list = create_list();
    int a = TEST_ASSERT(!front(list, NULL), "!front(list, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(list);
}

void test_back_null_list_null_dataout() {
    int a = TEST_ASSERT(!back(NULL, NULL), "!back(NULL, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_back_null_list() {
    void** dataOut = malloc(sizeof(void**));
    int data = 5;
    *dataOut = &data;
    int a = TEST_ASSERT(!back(NULL, dataOut), "!front(NULL, dataOut) (should have returned false)");
    int b = TEST_ASSERT(!*dataOut, "!*dataOut (*dataOut should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataOut);
}

void test_back_empty_list() {
    void** dataOut = malloc(sizeof(void**));
    list* list = create_list();
    int data = 5;
    *dataOut = &data;
    int a = TEST_ASSERT(!back(list, dataOut), "!back(list, dataOut) (should have returned false)");
    int b = TEST_ASSERT(!*dataOut, "!*dataOut (*dataOut should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataOut);
    free(list);
}

void test_back_empty_list_null_dataout() {
    list* list = create_list();
    int a = TEST_ASSERT(!back(list, NULL), "!back(list, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(list);
}

void test_push_front_null_list() {
    int data = 5;
    int a = TEST_ASSERT(!push_front(NULL, (void*) &data), "!push_front(NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_push_front_null_data() {
    list* alist = create_list();
    int a = TEST_ASSERT(push_front(alist, NULL), "!push_front(alist, NULL) (should have returned null)");
    void** dataout = malloc(sizeof(void**));
    int b = TEST_ASSERT(front(alist, dataout), "front(alist, dataout) (should have returned true)");
    int c = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    int d = TEST_ASSERT(alist->size == 1, "alist->size == 1");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist->head);
    free(alist);
    free(dataout);
}

void test_push_front_actual_data() {
    list* alist = create_list();
    Student* s = create_student(4, "Alpha", "Beta", CS1332, 3.1);
    int a = TEST_ASSERT(push_front(alist, s), "push_front(alist, s) (should have returned true)");
    void** dataout = malloc(sizeof(void**));
    int b = TEST_ASSERT(front(alist, dataout), "front(alist, dataout) (should have returned true");
    int c = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int d = TEST_ASSERT(*dataout == s, "*dataout == s");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist->head);
    free(alist);
    free(dataout);
    free_student(s);
}

void test_push_back_null_list() {
    int data = 5;
    int a = TEST_ASSERT(!push_back(NULL, (void*) &data), "!push_back(NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_push_back_null_data() {
    list* alist = create_list();
    int a = TEST_ASSERT(push_back(alist, NULL), "!push_back(alist, NULL) (should have returned null)");
    void** dataout = malloc(sizeof(void**));
    int b = TEST_ASSERT(back(alist, dataout), "back(alist, dataout) (should have returned true)");
    int c = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    int d = TEST_ASSERT(alist->size == 1, "alist->size == 1");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist->tail);
    free(alist);
    free(dataout);
}

void test_push_back_actual_data() {
    list* alist = create_list();
    Student* s = create_student(4, "Alpha", "Beta", CS1332, 3.1);
    int a = TEST_ASSERT(push_back(alist, s), "push_back(alist, s) (should have returned true)");
    void** dataout = malloc(sizeof(void**));
    int b = TEST_ASSERT(back(alist, dataout), "back(alist, dataout) (should have returned true");
    int c = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int d = TEST_ASSERT(*dataout == s, "*dataout == s");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist->tail);
    free(alist);
    free(dataout);
    free_student(s);
}

void test_add_null_list() {
    int data = 5;
    int a = TEST_ASSERT(!add(NULL, 0, (void*) &data), "!add(NULL, 0, (void*) &data) (should have returned false)");
    if (a) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_add_index_greater_than_size() {
    int data = 5;
    list* list = create_list();
    int a = TEST_ASSERT(!add(list, 1, (void*) &data), "!add(NULL, 1, (void*) &data) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(list);
}

void test_add_index_less_than_zero() {
    int data = 5;
    list* list = create_list();
    int a = TEST_ASSERT(!add(list, -1, (void*) &data), "!add(NULL, -1, (void*) &data) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(list);
}

void test_add_null_data_to_empty_list() {
    void** dataout = malloc(sizeof(void**));
    list* list = create_list();
    int a = TEST_ASSERT(add(list, 0, NULL), "add(list, 0, NULL) (should have returned true)");
    int b = TEST_ASSERT(list->size == 1, "list->size == 1");
    int c = TEST_ASSERT(front(list, dataout), "front(list, dataout) (should have returned true)");
    int d = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
    empty_list(list, free_student);
    free(list);
}

void test_add_data_to_front_of_list() {
    void** dataout = malloc(sizeof(void**));
    list* list = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    int a = TEST_ASSERT(add(list, 0, (void*) s), "add(list, 0, (void*) s) (should have returned true)");
    int b = TEST_ASSERT(list->size == 1, "list->size == 1");
    int c = TEST_ASSERT(front(list, dataout), "front(list, dataout) (should have returned true)");
    int d = TEST_ASSERT(*dataout, "*dataOut (should not be NULL)");
    int e = TEST_ASSERT(((Student*) *dataout)->id == s->id, "*dataOut->id == s->id");
    int f = TEST_ASSERT(list->tail, "");
    int g = TEST_ASSERT(list->tail == list->head, "");
    if (a && b && c && d && e && f && g) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
    empty_list(list, free_student);
    free(list);
}

void test_add_data_to_back_of_list() {
    void** dataout = malloc(sizeof(void**));
    list* list = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    add(list, 0, (void*) s);
    int a = TEST_ASSERT(add(list, 1, (void*) s2), "add(list, 1, (void*) s2) (should have returned true)");
    int b = TEST_ASSERT(list->size == 2, "list->size == 2");
    int c = TEST_ASSERT(back(list, dataout), "back(list, dataout) (should have returned true)");
    int d = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int e = TEST_ASSERT(((Student*) *dataout)->id == s2->id, "*dataOut->id == s->id");
    int f = TEST_ASSERT(list->tail, "list->tail (should not be NULL)");
    int g = TEST_ASSERT(list->head, "list->head (should not be NULL)");
    int h = TEST_ASSERT(list->head != list->tail, "list->head != list->tail (head and tail should not be equal)");
    if (a && b && c && d && e && f && g && h) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
    empty_list(list, free_student);
    free(list);
}

void test_add_data_to_middle_of_list() {
    void** dataout = malloc(sizeof(void**));
    list* list = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(list, 0, (void*) s);
    add(list, 1, (void*) s2);
    int a = TEST_ASSERT(add(list, 1, (void*) s3), "add(list, 1, (void*) s3) (should have returned true)");
    int b = TEST_ASSERT(list->size == 3, "list->size == 3");
    int c = TEST_ASSERT(front(list, dataout), "front(list, dataout) (should have returned true)");
    int d = TEST_ASSERT((Student*) *dataout == s, "(Student*) *dataout == s");
    int e = TEST_ASSERT(back(list, dataout), "back(list, dataout) == s2");
    int f = TEST_ASSERT((Student*) *dataout == s2, "(Student*) *dataout == s2");
    traverse(list, print_student);
    printf(CYAN "** Make sure that students are in the order Bob, Henry, Frank. If not, then the test failed, regardless of below. **\n");
    if (a && b && c && d && e && f) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
    empty_list(list, free_student);
    free(list);
}

void test_shallow_copy_list_null_list() {
    int a = TEST_ASSERT(!shallow_copy_list(NULL), "!shallow_copy_list(NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_shallow_copy_list_empty_list() {
    list* alist = create_list();
    list* copied = shallow_copy_list(alist);
    int a = TEST_ASSERT(alist->size == copied->size, "list->size == copied->size");
    int b = TEST_ASSERT(!copied->head, "!copied->head (should be NULL)");
    int c = TEST_ASSERT(!copied->tail, "!copied->tail (should be NULL)");
    if (a && b && c) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(copied);
}

void test_shallow_copy_list_not_empty() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    list* copied = shallow_copy_list(alist);
    int a = TEST_ASSERT(alist->size == copied->size, "list->size == copied->size");
    traverse(alist, print_student);
    printf("\n");
    traverse(copied, print_student);
    printf(CYAN "** Make sure that the pointers of the students with the same ids in the first set and the second set are the same, otherwise the test failed regardless of what it says below. **\n");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    void* data;
    while(pop_front(copied, &data));
    free(alist);
    free(copied);
}

void test_deep_copy_list_null_list() {
    int a = TEST_ASSERT(!deep_copy_list(NULL, copy_student, free_student), "!deep_copy_list(NULL, copy_student, free_student) (should have returned NULL)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_deep_copy_list_null_copy_func() {
    list* alist = create_list();
    int a = TEST_ASSERT(!deep_copy_list(alist, NULL, free_student), "!deep_copy_list(alist, NULL, free_student) (should have returned NULL)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_deep_copy_list_null_free_func() {
    list* alist = create_list();
    int a = TEST_ASSERT(!deep_copy_list(alist, copy_student, NULL), "!deep_copy_list(alist, copy_student, NULL) (should have returned NULL)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_deep_copy_list_empty_list() {
    list* alist = create_list();
    list* copied = deep_copy_list(alist, copy_student, free_student);
    int a = TEST_ASSERT(copied->size == alist->size, "copied->size == alist->size");
    int b = TEST_ASSERT(!copied->head, "!copied->head (should be NULL)");
    int c = TEST_ASSERT(!copied->tail, "!copied->tail (should be NULL)");
    if (a && b && c) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(copied);
}

void test_deep_copy_list_not_empty() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    list* copied = deep_copy_list(alist, copy_student, free_student);
    int a = TEST_ASSERT(copied->size == alist->size, "copied->size == alist->size");
    traverse(alist, print_student);
    printf("\n");
    traverse(copied, print_student);
    printf(CYAN "** Make sure that the pointers of the students with the same ids in the first set and the second set are different, otherwise the test failed regardless of what it says below. **\n");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    empty_list(copied, free_student);
    free(alist);
    free(copied);
}

void test_get_null_list_null_dataout() {
    int a = TEST_ASSERT(!get(NULL, 0, NULL), "!get(NULL, 0, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_get_null_list() {
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(!get(NULL, 0, dataout), "!get(NULL, 0, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
}

void test_get_index_greater_than_size() {
    list* alist = create_list();
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    int a = TEST_ASSERT(!get(alist, 1, dataout), "!get(alist, 1, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(dataout);
}

void test_get_index_equal_to_size() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    add(alist, 0, (void*) s);
    int a = TEST_ASSERT(!get(alist, 1, dataout), "!get(alist, 1, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_get_index_less_than_zero() {
    list* alist = create_list();
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(!get(alist, -1, dataout), "!get(alist, -1, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(dataout);
}

void test_get_valid_index_null_dataout() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    add(alist, 0, (void*) s);
    int a = TEST_ASSERT(!get(alist, 0, NULL), "get(alist, 0, NULL) (should have returned false)");
    if (a) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
}

void test_get_valid_index_valid_dataout() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    void** dataout = malloc(sizeof(void**));
    add(alist, 0, (void*) s);
    int a = TEST_ASSERT(get(alist, 0, dataout), "get(alist, 0, dataout) (should have returned true)");
    int b = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int c = TEST_ASSERT(*dataout == s, "*dataout == s");
    if (a && b && c) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_size_null_list_null_dataout() {
    int a = TEST_ASSERT(!size(NULL, NULL), "!size(NULL, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_size_null_list() {
    int* dataout = malloc(sizeof(int*));
    int a = TEST_ASSERT(!size(NULL, dataout), "!size(NULL, dataout) (should have returned false)");
    int b = TEST_ASSERT(*dataout == -1, "*dataout == -1");
    if (a && b) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
}

void test_size_valid_list_null_dataout() {
    list* alist = create_list();
    int a = TEST_ASSERT(!size(alist, NULL), "!size(alist, NULL) (should have returned failse");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_size_valid_list_valid_dataout() {
    list* alist = create_list();
    int* sizeout = malloc(sizeof(int*));
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    int a = TEST_ASSERT(size(alist, sizeout), "size(alist, sizeout) (should have returned true)");
    int b = TEST_ASSERT(!*sizeout, "!*sizeout (*sizeout should be zero)");
    add(alist, 0, (void*) s);
    int c = TEST_ASSERT(size(alist, sizeout), "size(alist, sizeout) (should have returned true)");
    int d = TEST_ASSERT(*sizeout == 1, "*sizeout == 1");
    if (a && b && c && d) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(sizeout);
}

void test_contains_null_list() {
    Student* comp = create_student(5, "", "", CS1332, 2.8);
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(!contains(NULL, (void*) comp, student_id_comp, dataout), "!contains(NULL, (void*) comp, student_id_comp, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(comp);
    free(dataout);
}

void test_contains_null_comparator() {
    Student* comp = create_student(5, "", "", CS1332, 2.8);
    void** dataout = malloc(sizeof(void**));
    list* alist = create_list();
    int a = TEST_ASSERT(!contains(alist, (void*) comp, NULL, dataout), "!contains(alist, (void*) comp, NULL, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(comp);
    free(dataout);
    free(alist);
}

void test_contains_null_dataout() {
    Student* comp = create_student(5, "", "", CS1332, 2.8);
    list* alist = create_list();
    int a = TEST_ASSERT(!contains(alist, (void*) comp, student_id_comp, NULL), "!contains(alist, (void*) comp, student_id_comp, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(comp);
    free(alist);
}

void test_contains_empty_list() {
    list* alist = create_list();
    Student* comp = create_student(5, "", "", CS1332, 2.8);
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(!contains(alist, (void*) comp, student_id_comp, dataout), "!contains(alist, (void*) comp, student_id_comp, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should have been NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(comp);
    free(alist);
    free(dataout);
}

void test_contains_null_data() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(!contains(alist, NULL, student_id_comp, dataout), "!contains(alist, NULL, student_id_comp, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should have been NULL)");
    if (a && b) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_contains_data_in_list() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    Student* comp = create_student(2, "", "", CS2110, 0.0);
    int a = TEST_ASSERT(contains(alist, comp, student_id_comp, dataout), "contains(alist, comp, student_id_comp, dataout) (should have returned true)");
    int b = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int c = TEST_ASSERT(*dataout == s2, "*dataout == s2");
    if (a && b && c) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free_student(comp);
    free(alist);
    free(dataout);
}

void test_contains_data_not_in_list() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    Student* comp = create_student(5, "", "", CS2110, 0.0);
    int a = TEST_ASSERT(!contains(alist, comp, student_id_comp, dataout), "!contains(alist, comp, student_id_comp, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free_student(comp);
    free(alist);
    free(dataout);
}

void test_pop_front_null_list() {
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    int a = TEST_ASSERT(!pop_front(NULL, dataout), "!pop_front(NULL, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
}

void test_pop_front_null_dataout() {
    list* alist = create_list();
    int a = TEST_ASSERT(!pop_front(alist, NULL), "!pop_front(alist, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_pop_front_empty_list() {
    list* alist = create_list();
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(!pop_front(alist, dataout), "!pop_front(alist, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(dataout);
}

void test_pop_front_valid() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(pop_front(alist, dataout), "pop_front(alist, dataout) (should have returned true)");
    int b = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int c = TEST_ASSERT(*dataout == s, "*dataout == s");
    int d = TEST_ASSERT(alist->size == 2, "alist->size == 2");
    int e = TEST_ASSERT(pop_front(alist, dataout), "pop_front(alist, dataout) (should have returned true)");
    int f = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int g = TEST_ASSERT(*dataout == s2, "*dataout == s2");
    int h = TEST_ASSERT(alist->size == 1, "alist->size == 1");
    int i = TEST_ASSERT(pop_front(alist, dataout), "pop_front(alist, dataout) (should have returned true)");
    int j = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int k = TEST_ASSERT(*dataout == s3, "*dataout == s3");
    int l = TEST_ASSERT(alist->size == 0, "alist->size == 0");
    if (a && b && c && d && e && f && g && h && i && j && k && l) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(s);
    free_student(s2);
    free_student(s3);
    free(dataout);
    free(alist);
}

void test_pop_back_null_list() {
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    int a = TEST_ASSERT(!pop_back(NULL, dataout), "!pop_back(NULL, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);

}

void test_pop_back_null_dataout() {
    list* alist = create_list();
    int a = TEST_ASSERT(!pop_back(alist, NULL), "!pop_back(alist, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_pop_back_empty_list() {
    list* alist = create_list();
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(!pop_back(alist, dataout), "!pop_back(alist, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(dataout);
}

void test_pop_back_valid() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int a = TEST_ASSERT(pop_back(alist, dataout), "pop_back(alist, dataout) (should have returned true)");
    int b = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int c = TEST_ASSERT(*dataout == s3, "*dataout == s3");
    int d = TEST_ASSERT(alist->size == 2, "alist->size == 2");
    int e = TEST_ASSERT(pop_back(alist, dataout), "pop_back(alist, dataout) (should have returned true)");
    int f = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int g = TEST_ASSERT(*dataout == s2, "*dataout == s2");
    int h = TEST_ASSERT(alist->size == 1, "alist->size == 1");
    int i = TEST_ASSERT(pop_back(alist, dataout), "pop_back(alist, dataout) (should have returned true)");
    int j = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int k = TEST_ASSERT(*dataout == s, "*dataout == s");
    int l = TEST_ASSERT(alist->size == 0, "alist->size == 0");
    if (a && b && c && d && e && f && g && h && i && j && k && l) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(s);
    free_student(s2);
    free_student(s3);
    free(dataout);
    free(alist);
}

void test_list_remove_null_list() {
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    int a = TEST_ASSERT(!list_remove(NULL, 0, dataout), "!list_remove(NULL, 0, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(dataout);
}

void test_list_remove_index_greater_than_size() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    int a = TEST_ASSERT(!list_remove(alist, 4, dataout), "!list_remove(alist, 4, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_list_remove_index_equal_to_size() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    int a = TEST_ASSERT(!list_remove(alist, 3, dataout), "!list_remove(alist, 3, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_list_remove_index_less_than_zero() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    int a = TEST_ASSERT(!list_remove(alist, -1, dataout), "!list_remove(alist, -1, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_list_remove_null_dataout() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    int a = TEST_ASSERT(!list_remove(alist, 2, NULL), "!list_remove(alist, 2, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
}

void test_list_remove_empty_list() {
    list* alist = create_list();
    int data = 5;
    void** dataout = malloc(sizeof(void**));
    *dataout = &data;
    int a = TEST_ASSERT(!list_remove(alist, 0, dataout), "!list_remove(alist, 0, dataout) (should have returned false)");
    int b = TEST_ASSERT(!*dataout, "!*dataout (should be NULL)");
    if (a && b) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(dataout);
}

void test_list_remove_from_front_of_list() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    traverse(alist, print_student);
    printf("\n");
    int a = TEST_ASSERT(list_remove(alist, 0, dataout), "list_remove(alist, 0, dataout) (should have returned true)");
    int b = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int c = TEST_ASSERT(*dataout == s, "*dataout == s");
    int d = TEST_ASSERT(alist->size == 2, "alist->size == 2");
    traverse(alist, print_student);
    printf("\n");
    printf(CYAN "** If traversals don't make sense, then the test didn't pass. **\n");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(s);
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_list_remove_from_back_of_list() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    traverse(alist, print_student);
    printf("\n");
    int a = TEST_ASSERT(list_remove(alist, 2, dataout), "list_remove(alist, 2, dataout) (should have returned true)");
    int b = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int c = TEST_ASSERT(*dataout == s3, "*dataout == s3");
    int d = TEST_ASSERT(alist->size == 2, "alist->size == 2");
    traverse(alist, print_student);
    printf("\n");
    printf(CYAN "** If traversals don't make sense, then the test didn't pass. **\n");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(s3);
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_list_remove_from_middle_of_list() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    void** dataout = malloc(sizeof(void**));
    int data = 5;
    *dataout = &data;
    traverse(alist, print_student);
    printf("\n");
    int a = TEST_ASSERT(list_remove(alist, 1, dataout), "list_remove(alist, 1, dataout) (should have returned true)");
    int b = TEST_ASSERT(*dataout, "*dataout (should not be NULL)");
    int c = TEST_ASSERT(*dataout == s2, "*dataout == s2");
    int d = TEST_ASSERT(alist->size == 2, "alist->size == 2");
    traverse(alist, print_student);
    printf("\n");
    printf(CYAN "** If traversals don't make sense, then the test didn't pass. **\n");
    if (a && b && c && d) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free_student(s2);
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_empty_list_null_list() {
    empty_list(NULL, free_student);
    printf(GREEN "[INFO] Passed.\n");
}

void test_empty_list_null_freefunc() {
    list* alist = create_list();
    empty_list(alist, NULL);
    printf(GREEN "[INFO] Passed.\n");
    free(alist);
}

void test_empty_list_empty_list() {
    list* alist = create_list();
    empty_list(alist, free_student);
    int a = TEST_ASSERT(!alist->size, "!alist->size (size should be 0)");
    if (a) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_empty_list_not_empty_list() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    empty_list(alist, free_student);
    int a = TEST_ASSERT(!alist->size, "!alist->size (size should be 0)");
    if (a) {
        printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_traverse_null_list() {
    int a = TEST_ASSERT(!traverse(NULL, print_student), "!traverse(NULL, print_student) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_traverse_null_dofunc() {
    list* alist = create_list();
    int a = TEST_ASSERT(!traverse(alist, NULL), "!traverse(alist, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_traverse_empty_list() {
    list* alist = create_list();
    int a = TEST_ASSERT(traverse(alist, print_student), "traverse(alist, print_student) (should have returned true)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_reverse_null_list() {
    int a = TEST_ASSERT(!reverse(NULL), "!reverse(NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
}

void test_reverse_empty_list() {
    list* alist = create_list();
    int a = TEST_ASSERT(reverse(alist), "reverse(alist) (should have returned true)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_reverse_not_empty_list() {
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    //Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    //add(alist, 2, (void*) s3);
    traverse(alist, print_student);
    printf("\n");
    int a = TEST_ASSERT(reverse(alist), "reverse(alist) (should have returned true)");
    traverse(alist, print_student);
    printf("\n");
    printf(CYAN "** If the traversals aren't reversed, then the test didn't pass. **\n");
    void** dataout = malloc(sizeof(void**));
    get(alist, 1, dataout);
    int b = TEST_ASSERT(*dataout == s, "*dataout == s");
    get(alist, 0, dataout);
    int c = TEST_ASSERT(*dataout == s2, "*dataout == s2");
    if (a && b && c) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(alist);
    free(dataout);
}

void test_concat_null_first_list() {
    list* alist = create_list();
    int a = TEST_ASSERT(!concat(NULL, alist), "!concat(NULL, alist) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_concat_null_last_list() {
    list* alist = create_list();
    int a = TEST_ASSERT(!concat(alist, NULL), "!concat(alist, NULL) (should have returned false)");
    if (a) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
}

void test_concat_empty_first_list_not_empty_second_list() {
    list* blist = create_list();
    list* alist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    int a = TEST_ASSERT(concat(blist, alist), "concat(blist, alist) (should have returned true)");
    int b = TEST_ASSERT(blist->size == 3, "blist->size == 3");
    int c = TEST_ASSERT(alist->size == 0, "alist->size == 0");
    int d = TEST_ASSERT(!alist->head, "!alist->head (should be NULL)");
    int e = TEST_ASSERT(!alist->tail, "!alist->tail (should be NULL)");
    traverse(blist, print_student);
    printf(CYAN "** If traversal doesn't make sense, then test failed. **\n");
    if (a && b && c && d && e) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(blist, free_student);
    free(blist);
    free(alist);
}

void test_concat_not_empty_first_list_empty_second_list() {
    list* alist = create_list();
    list* blist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    int a = TEST_ASSERT(concat(alist, blist), "concat(alist, blist) (should have returned true)");
    int b = TEST_ASSERT(alist->size == 3, "alist->size == 3");
    int c = TEST_ASSERT(blist->size == 0, "blist->size == 0");
    int d = TEST_ASSERT(!blist->head, "!blist->head (should be NULL)");
    int e = TEST_ASSERT(!blist->tail, "!blist->tail (should be NULL)");
    traverse(alist, print_student);
    printf(CYAN "** If traversal doesn't make sense, then test failed. **\n");
    if (a && b && c && d && e) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(blist);
    free(alist);
}

void test_concat_empty_first_list_empty_second_list() {
    list* alist = create_list();
    list* blist = create_list();
    int a = TEST_ASSERT(concat(alist, blist), "concat(alist, blist) (should have returned true)");
    int b = TEST_ASSERT(alist->size == 0, "alist->size == 0");
    int c = TEST_ASSERT(blist->size == 0, "blist->size == 0");
    int d = TEST_ASSERT(!blist->head, "!blist->head (should be null)");
    int e = TEST_ASSERT(!blist->tail, "!blist->tail (should be null)");
    if (a && b && c && d && e) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    free(alist);
    free(blist);
}

void test_concat_not_empty_first_list_not_empty_second_list() {
    list* alist = create_list();
    list* blist = create_list();
    Student* s = create_student(1, "Bob", "Bobberson", CS2110, 4.0);
    Student* s2 = create_student(2, "Frank", "Frankenstein", CS2340, 1.9);
    Student* s3 = create_student(3, "Henry", "Henderson", CS2110, 3.4);
    Student* s4 = create_student(4, "ABob", "ABobberson", CS2110, 4.0);
    Student* s5 = create_student(5, "AFrank", "AFrankenstein", CS2340, 1.9);
    Student* s6 = create_student(6, "AHenry", "AHenderson", CS2110, 3.4);
    add(alist, 0, (void*) s);
    add(alist, 1, (void*) s2);
    add(alist, 2, (void*) s3);
    add(blist, 0, (void*) s4);
    add(blist, 1, (void*) s5);
    add(blist, 2, (void*) s6);
    int a = TEST_ASSERT(concat(alist, blist), "concat(alist, blist) (should have returned true)");
    int b = TEST_ASSERT(alist->size == 6, "alist->size == 6");
    int c = TEST_ASSERT(blist->size == 0, "blist->size == 0");
    int d = TEST_ASSERT(!blist->head, "!blist->head (should be null)");
    int e = TEST_ASSERT(!blist->tail, "!blist->tail (should be null)");
    traverse(alist, print_student);
    printf(CYAN "** If traversal doesn't make sense, then test failed. **\n");
    if (a && b && c && d && e) {
    printf(GREEN "[INFO] All statements passed.\n");
    }
    empty_list(alist, free_student);
    free(blist);
    free(alist);
}

#define NUMTESTS 81

int main() {
    test_s arr[NUMTESTS] = {
    { test_create_list_makes_sense, "test_create_list_makes_sense" },
        { test_front_null_list_null_dataout, "test_front_null_list_null_dataout" },
        { test_front_null_list, "test_front_null_list" },
    { test_front_empty_list, "test_front_empty_list" },
    { test_front_empty_list_null_dataout, "test_front_empty_list_null_dataout" },
    { test_back_null_list_null_dataout, "test_back_null_list_null_dataout" },
        { test_back_null_list, "test_back_null_list" },
    { test_back_empty_list, "test_back_empty_list" },
    { test_back_empty_list_null_dataout, "test_back_empty_list_null_dataout" },
    { test_push_front_null_list, "test_push_front_null_list" },
    { test_push_front_null_data, "test_push_front_null_data" },
    { test_push_front_actual_data, "test_push_front_actual_data" },
        { test_push_back_null_list, "test_push_back_null_list" },
    { test_push_back_null_data, "test_push_back_null_data" },
    { test_push_back_actual_data, "test_push_back_actual_data" },
    { test_add_null_list, "test_add_null_list" },
    { test_add_index_greater_than_size, "test_add_index_greater_than_size" },
    { test_add_index_less_than_zero, "test_add_index_less_than_zero" },
    { test_add_null_data_to_empty_list, "test_add_null_data_to_empty_list" },
    { test_add_data_to_front_of_list, "test_add_data_to_front_of_list" },
    { test_add_data_to_back_of_list, "test_add_data_to_back_of_list" },
    { test_add_data_to_middle_of_list, "test_add_data_to_middle_of_list" },
    { test_shallow_copy_list_null_list, "test_shallow_copy_list_null_list" },
    { test_shallow_copy_list_empty_list, "test_shallow_copy_list_empty_list" },
    { test_shallow_copy_list_not_empty, "test_shallow_copy_list_not_empty" },
    { test_deep_copy_list_null_list, "test_deep_copy_list_null_list" },
    { test_deep_copy_list_null_copy_func, "test_deep_copy_list_null_copy_func" },
    { test_deep_copy_list_null_free_func, "test_deep_copy_list_null_free_func" },
    { test_deep_copy_list_empty_list, "test_deep_copy_list_empty_list" },
    { test_deep_copy_list_not_empty, "test_deep_copy_list_not_empty" },
        { test_get_null_list_null_dataout, "test_get_null_list_null_dataout" },
    { test_get_null_list, "test_get_null_list" },
    { test_get_index_greater_than_size, "test_get_index_greater_than_size" },
    { test_get_index_equal_to_size, "test_get_index_equal_to_size" },
    { test_get_index_less_than_zero, "test_get_index_less_than_zero" },
    { test_get_valid_index_null_dataout, "test_get_valid_index_null_dataout" },
    { test_get_valid_index_valid_dataout, "test_get_valid_index_valid_dataout" },
    { test_size_null_list_null_dataout, "test_size_null_list_null_dataout" },
    { test_size_null_list, "test_size_null_list" },
    { test_size_valid_list_null_dataout, "test_size_valid_list_null_dataout" },
    { test_size_valid_list_valid_dataout, "test_size_valid_list_valid_dataout" },
    { test_contains_null_list, "test_contains_null_list" },
        { test_contains_null_comparator, "test_contains_null_comparator" },
    { test_contains_null_dataout, "test_contains_null_dataout" },
        { test_contains_empty_list, "test_contains_empty_list" },
    { test_contains_null_data, "test_contains_null_data" },
    { test_contains_data_in_list, "test_contains_data_in_list" },
    { test_contains_data_not_in_list, "test_contains_data_not_in_list" },
    { test_pop_front_null_list, "test_pop_front_null_list" },
        { test_pop_front_null_dataout, "test_pop_front_null_dataout" },
    { test_pop_front_empty_list, "test_pop_front_empty_list" },
        { test_pop_front_valid, "test_pop_front_valid_list" },
    { test_pop_back_null_list, "test_pop_back_null_list" },
    { test_pop_back_null_dataout, "test_pop_back_null_dataout" },
    { test_pop_back_empty_list, "test_pop_back_empty_list" },
    { test_pop_back_valid, "test_pop_back_valid" },
        { test_list_remove_null_list, "test_list_remove_null_list" },
    { test_list_remove_index_greater_than_size, "test_list_remove_index_greater_than_size" },
    { test_list_remove_index_equal_to_size, "test_list_remove_index_equal_to_size" },
    { test_list_remove_index_less_than_zero, "test_list_remove_index_less_than_zero" },
    { test_list_remove_null_dataout, "test_list_remove_null_dataout" },
    { test_list_remove_empty_list, "test_list_remove_empty_list" },
    { test_list_remove_from_front_of_list, "test_list_remove_from_front_of_list" },
    { test_list_remove_from_back_of_list, "test_list_remove_from_back_of_list" },
    { test_list_remove_from_middle_of_list, "test_list_remove_from_middle_of_list" },
    { test_empty_list_null_list, "test_empty_list_null_list" },
    { test_empty_list_null_freefunc, "test_empty_list_null_freefunc" },
    { test_empty_list_empty_list, "test_empty_list_empty_list" },
    { test_empty_list_not_empty_list, "test_empty_list_not_empty_list" },
    { test_traverse_null_list, "test_traverse_null_list" },
    { test_traverse_null_dofunc, "test_traverse_null_dofunc" },
    { test_traverse_empty_list, "test_traverse_empty_list" },
    { test_reverse_null_list, "test_reverse_null_list" },
    { test_reverse_empty_list, "test_reverse_empty_list" },
    { test_reverse_not_empty_list, "test_reverse_not_empty_list" },
    { test_concat_null_first_list, "test_concat_null_first_list" },
    { test_concat_null_last_list, "test_concat_null_last_list" },
    { test_concat_empty_first_list_not_empty_second_list, "test_concat_empty_first_list_not_empty_second_list" },
        { test_concat_not_empty_first_list_empty_second_list, "test_concat_not_empty_first_list_empty_second_list" },
    { test_concat_empty_first_list_empty_second_list, "test_concat_empty_first_list_empty_second_list" },
    { test_concat_not_empty_first_list_not_empty_second_list, "test_concat_not_empty_first_list_not_empty_second_list" }
    };
    printf(CYAN "** Make sure to run these tests in Valgrind as well to check for memory leaks. **\n\n");
    for (int i = 0; i < NUMTESTS; i++) {
    printf(BLUE "%s\n", arr[i].name);
    arr[i].t();
    printf("\n");
    }
    printf(WHITE);
    return 0;
}