#include "tests.h"

malloc_info call_info;
int free_count = 0;
int invalid_free = 0;

student_test tests[NUM_TESTS] = {
    {test_create_list,              "test_create_list",                 10, false},
    {test_create_list_fail_second,  "test_create_list_fail_second",     5, false},
    {test_create_list_fail_first,   "test_create_list_fail_first",      5, false},
    {test_add_null,                 "test_add_null",                    5, false},
    {test_add_9,                    "test_add_9",                       7, false},
    {test_add_10,                   "test_add_10",                      7, false},
    {test_add_11,                   "test_add_11",                      7, false},
    {test_add_11_fail,              "test_add_11_fail",                 7, false},
    {test_add_20,                   "test_add_20",                      7, false},
    {test_shallow_copy,             "test_shallow_copy",                10, false},
    {test_shallow_copy_fail,        "test_shallow_copy_fail",           10, false},
    {test_destroy,                  "test_destroy",                     20, false},
};

int main() {
    printf("starting tests\n");

    for(int i = 0; i < NUM_TESTS; i++) {
        // reset malloc calls object
        memset(&call_info, 0, sizeof(malloc_info));
            
        pid_t pid = fork();

        // parent
        if(pid) {
            int status;
            waitpid(pid, &status, 0);
            if(!status) {
                tests[i].passed = true;
            }

        // child
        } else {
            tests[i].tester();
            exit(0);
        }

    }
    printf("done with tests\n");
    FILE* f = fopen("gradelog.json", "w");
    fprintf(f, "[");
    for(int i = 0; i < NUM_TESTS; i++) {
        fprintf(f,"{\"test_name\":\"%s\", \"test_passed\":%s, \"test_total\":%d, \"test_score\":%d}%s\n",
            tests[i].name, 
            tests[i].passed ? "true" : "false", 
            tests[i].value,
            tests[i].passed ? tests[i].value : 0,
            i + 1 == NUM_TESTS ? "" : ",");
    }
    fprintf(f,"]");
    fclose(f);
    
}

void* __wrap_calloc(size_t nitems, size_t size) {
    fprintf(stderr, "don't use calloc\n");
    return NULL;
}

void *__wrap_realloc(void *ptr, size_t size) {
    fprintf(stderr, "don't use realloc\n");
    return NULL;
}

void* __wrap_malloc (size_t size) {
    //printf("malloc(%zd)\n", size);
    call_info.last_called_size[call_info.count++ % HISTORY_SIZE] = size;
    if(call_info.successful_malloc_calls-- <= 0) {
        //printf("malloc call failed\n");
        return NULL;
    } else {
        //printf("malloc call succeeded\n");
        void* ptr = __real_malloc(size);
        call_info.calls[(call_info.count - 1) % HISTORY_SIZE] = ptr;
        return ptr;
    }
}

void __wrap_free(void *ptr) {
    //printf("free(0x%p)\n", ptr);
    free_count++;
    bool found = false;
    for(int i = 0; i < HISTORY_SIZE; i++) {
        if(call_info.calls[i] == ptr) {
            call_info.calls[i] = NULL;
            found = true;
            break;
        }
    }
    if(!found) {
        invalid_free++;
        fprintf(stderr, "tried to free invalid pointer 0x%p", ptr);
    } else {
        __real_free(ptr);
    }
}

void cleanup(malloc_info* info) {
    for(int i = 0; i < HISTORY_SIZE; i++) {
        if(info->calls[i] != NULL) __real_free(info->calls[i]);
    }
    memset(info, 0, sizeof(malloc_info));
    free_count = 0;
}

bool cleaned(malloc_info* info) {
    for(int i = 0; i < HISTORY_SIZE; i++) {
        if(info->calls[i] != NULL) return false;
    }
    return true;
}

bool in_last_n(malloc_info* info, size_t val, int n) {
    // for(int i = 0; i < 10; i++) {
    //     printf("i:%zd\n", info->last_called_size[i]);
    // }
    int count = info->count;
    for(int i = count - 1; i >= count - n && i >= 0; i--) {
        if(info->last_called_size[i % HISTORY_SIZE] == val) return true;
    }
    return false;
}

person* create_person(char* name, int age) {
    person* p = malloc(sizeof(person));
    char* n = malloc(strlen(name)+1);
    if(p == NULL || n == NULL) {
        fprintf(stderr, "create_person(%s,%d) malloc failed.\n", name, age);
        fprintf(stderr, "You probably ran out of mallocs, make sure your code is efficient\n");
    }
    strcpy(n,name);

    p->name = n;
    p->age = age;
    return p;
}

void free_person(void* a) {
    person* p = a;
    free(p->name);
    free(p);
}

int person_equals(void* a, void* b) {
    if(a == b) return 0;
    if(a == NULL || b == NULL) return 1;
    person* aa = (person*)a;
    person* bb = (person*)b;
    int name_eq = strcmp(aa->name, bb->name);
    if(name_eq) {
        return name_eq;
    } else {
        return bb->age - aa->age;
    }
}

array_list *ta_create_list() {
    array_list* arr_struct = malloc(sizeof(array_list));
    if(arr_struct == NULL) {
        return NULL;
    }

    void** arr_backing = malloc(sizeof(void*)*INIT_BACKING_SIZE);
    if(arr_backing == NULL) {
        free(arr_struct);
        return NULL;
    }

    arr_struct->backing_size = INIT_BACKING_SIZE;
    arr_struct->size = 0;
    arr_struct->backing_array = arr_backing;
    return arr_struct;
}

// normal create_list with no malloc failures
int test_create_list() {
    printf("[%sFAIL%s] test_create_list()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 2;
    free_count = 0;
    invalid_free = 0;

    // test create_list
    array_list* list = create_list();
    assert(list != NULL);
    assert(list->backing_size == INIT_BACKING_SIZE);
    assert(list->size == 0);
    assert(call_info.count == 2);
    assert(free_count == 0);
    assert(invalid_free == 0);
    assert(in_last_n(&call_info, sizeof(array_list), 2) == true);
    assert(in_last_n(&call_info, sizeof(void*)*INIT_BACKING_SIZE, 2) == true);

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 2);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_create_list()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// bad create_list, 2nd malloc call fails
int test_create_list_fail_second() {
    printf("[%sFAIL%s] test_create_list_fail_second()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 1;
    free_count = 0;
    invalid_free = 0;

    // test create_list
    array_list* list = create_list();
    assert(list == NULL);
    assert(free_count == 1);
    assert(invalid_free == 0);
    assert(call_info.count == 2);
    assert(cleaned(&call_info) == true);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_create_list_fail_second()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// bad create_list, 1st malloc call fails
int test_create_list_fail_first() {
    printf("[%sFAIL%s] test_create_list_fail_first()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 0;
    free_count = 0;
    invalid_free = 0;

    // test create_list
    array_list* list = create_list();
    assert(list == NULL);
    assert(free_count == 0);
    assert(invalid_free == 0);
    assert(cleaned(&call_info) == true);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_create_list_fail_first()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

//add null (should be ok)
int test_add_null() {
    printf("[%sFAIL%s] test_add_null()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 2;
    free_count = 0;
    invalid_free = 0;

    array_list* list = ta_create_list();
    assert(call_info.count == 2);
    void** curr_back = list->backing_array;


    assert(add_to_array_list(list, NULL) == true);
    assert(list->backing_size == INIT_BACKING_SIZE);
    assert(list->size == 1);
    assert(list->backing_array == curr_back);
    assert(call_info.count == 2);
    assert(free_count == 0);
    assert(invalid_free == 0);
    assert(list->backing_array[0] == NULL);

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 2);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_add_null()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// add 1 real
int test_add_1() {
    printf("[%sFAIL%s] test_add_1()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 2;
    free_count = 0;
    invalid_free = 0;

    array_list* list = ta_create_list();
    assert(call_info.count == 2);
    void** curr_back = list->backing_array;


    assert(add_to_array_list(list, (void*)(uintptr_t)1) == true);
    assert(list->backing_size == INIT_BACKING_SIZE);
    assert(list->size == 1);
    assert(list->backing_array == curr_back);
    assert(call_info.count == 2);
    assert(free_count == 0);
    assert(invalid_free == 0);
    assert((uintptr_t)list->backing_array[0] == (uintptr_t)1);

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 2);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_add_1()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// add 9 real
int test_add_9() {
    printf("[%sFAIL%s] test_add_9()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 2;
    free_count = 0;
    invalid_free = 0;

    array_list* list = ta_create_list();
    assert(call_info.count == 2);
    void** curr_back = list->backing_array;

    // insertions should change anything but size
    for(int i = 0; i < 9; i++) {
        assert(add_to_array_list(list, (void*)(uintptr_t)i) == true);
        assert(list->backing_size == INIT_BACKING_SIZE);
        assert(list->size == i+1);
        assert(list->backing_array == curr_back);
        assert(call_info.count == 2);
        assert(free_count == 0);
        assert(invalid_free == 0);
    }

    // check list
    for(int i = 0; i < 9; i++) {
        assert((uintptr_t)list->backing_array[i] == (uintptr_t)i);
    }

    assert(list->backing_size == INIT_BACKING_SIZE);
    assert(list->size == 9);
    assert(list->backing_array == curr_back);
    assert(call_info.count == 2);
    assert(free_count == 0);
    assert(invalid_free == 0);

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 2);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_add_9()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// add 10 real
int test_add_10() {
    printf("[%sFAIL%s] test_add_10()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 2;
    free_count = 0;
    invalid_free = 0;

    array_list* list = ta_create_list();
    assert(call_info.count == 2);
    void** curr_back = list->backing_array;

    // insertions should change anything but size
    for(int i = 0; i < 10; i++) {
        assert(add_to_array_list(list, (void*)(uintptr_t)i) == true);
        assert(list->backing_size == INIT_BACKING_SIZE);
        assert(list->size == i+1);
        assert(list->backing_array == curr_back);
        assert(call_info.count == 2);
        assert(free_count == 0);
        assert(invalid_free == 0);
    }

    // check list
    for(int i = 0; i < 10; i++) {
        assert((uintptr_t)list->backing_array[i] == (uintptr_t)i);
    }

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 2);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_add_10()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// add 11 real
int test_add_11() {
    printf("[%sFAIL%s] test_add_11()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 3;
    free_count = 0;
    invalid_free = 0;

    array_list* list = ta_create_list();
    assert(call_info.count == 2);
    void** curr_back = list->backing_array;

    // 10 insertions, no expand
    for(int i = 0; i < 10; i++) {
        assert(add_to_array_list(list, (void*)(uintptr_t)i) == true);
        assert(list->backing_size == INIT_BACKING_SIZE);
        assert(list->size == i+1);
        assert(list->backing_array == curr_back);
        assert(call_info.count == 2);
        assert(free_count == 0);
        assert(invalid_free == 0);
    }

    // 11th add, should expand
    assert(add_to_array_list(list, (void*)(uintptr_t)10) == true);

    assert(list->backing_size == INIT_BACKING_SIZE * BACKING_GROWTH_FACTOR);
    assert(in_last_n(&call_info, sizeof(void*) * (INIT_BACKING_SIZE * BACKING_GROWTH_FACTOR), 1) == true);
    assert(list->size == 11);
    assert(list->backing_array != curr_back);
    assert(call_info.count == 3);
    assert(free_count == 1);
    assert(invalid_free == 0);

    // check list
    for(int i = 0; i < 11; i++) {
        assert((uintptr_t)list->backing_array[i] == (uintptr_t)i);
    }

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 3);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_add_11()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// add 11 failure
int test_add_11_fail() {
    printf("[%sFAIL%s] test_add_11_fail()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 2;
    free_count = 0;
    invalid_free = 0;

    array_list* list = ta_create_list();
    assert(call_info.count == 2);
    void** curr_back = list->backing_array;

    // 10 insertions, no expand
    for(int i = 0; i < 10; i++) {
        assert(add_to_array_list(list, (void*)(uintptr_t)i) == true);
        assert(list->backing_size == INIT_BACKING_SIZE);
        assert(list->size == i+1);
        assert(list->backing_array == curr_back);
        assert(call_info.count == 2);
        assert(free_count == 0);
        assert(invalid_free == 0);
    }

    // 11th add, should expand (but expand fails)
    assert(add_to_array_list(list, (void*)(uintptr_t)10) == false);

    // backing should not be expanded
    assert(list->backing_size == INIT_BACKING_SIZE);
    assert(in_last_n(&call_info, sizeof(void*) * (INIT_BACKING_SIZE * BACKING_GROWTH_FACTOR), 1) == true);
    assert(list->size == 10);
    assert(list->backing_array == curr_back);
    assert(call_info.count == 3);
    assert(free_count == 0);
    assert(invalid_free == 0);

    // check list
    for(int i = 0; i < 10; i++) {
        assert((uintptr_t)list->backing_array[i] == (uintptr_t)i);
    }

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 2);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_add_11_fail()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// add 20
int test_add_20() {
    printf("[%sFAIL%s] test_add_20()\n", TERM_RED, TERM_RESET);

    call_info.successful_malloc_calls = 3;
    free_count = 0;
    invalid_free = 0;

    array_list* list = ta_create_list();
    assert(call_info.count == 2);
    void** curr_back = list->backing_array;

    // 10 insertions, no expand
    for(int i = 0; i < 10; i++) {
        assert(add_to_array_list(list, (void*)(uintptr_t)i) == true);
        assert(list->backing_size == INIT_BACKING_SIZE);
        assert(list->size == i+1);
        assert(list->backing_array == curr_back);
        assert(call_info.count == 2);
        assert(free_count == 0);
        assert(invalid_free == 0);
    }

    // 11th add, should expand
    assert(add_to_array_list(list, (void*)(uintptr_t)10) == true);

    assert(list->backing_size == INIT_BACKING_SIZE * BACKING_GROWTH_FACTOR);
    assert(in_last_n(&call_info, sizeof(void*) * (INIT_BACKING_SIZE * BACKING_GROWTH_FACTOR), 1) == true);
    assert(list->size == 11);
    assert(list->backing_array != curr_back);
    assert(call_info.count == 3);
    assert(free_count == 1);
    assert(invalid_free == 0);

    curr_back = list->backing_array;

    // 9 more insertions, (total of 20))
    for(int i = 11; i < 20; i++) {
        assert(add_to_array_list(list, (void*)(uintptr_t)i) == true);
        assert(list->backing_size == INIT_BACKING_SIZE * BACKING_GROWTH_FACTOR);
        assert(list->size == i+1);
        assert(list->backing_array == curr_back);
        assert(call_info.count == 3);
        assert(free_count == 1);
        assert(invalid_free == 0);
    }

    // check list
    for(int i = 0; i < 20; i++) {
        assert((uintptr_t)list->backing_array[i] == (uintptr_t)i);
    }

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 3);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_add_20()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// shallow copy
int test_shallow_copy() {
    printf("[%sFAIL%s] test_shallow_copy()\n", TERM_RED, TERM_RESET);
    call_info.successful_malloc_calls = 3;
    free_count = 0;
    invalid_free = 0;

    // setup array list with backing array of size 40
    // 2 malloc calls
    array_list* list = malloc(sizeof(array_list));
    memset(list, 0, sizeof(array_list));

    list->backing_array = malloc(sizeof(void*)*40);
    memset(list->backing_array, 0, sizeof(void*)*40);
    list->backing_size = 40;

    //add 21 items to backing array
    for(int i = 0; i <= 20; i++) {
        list->backing_array[i] = (void*)(uintptr_t)i;
        list->size++;
    }

    // save state before calling shallow_copy
    array_list before = {0,0,NULL};
    before.backing_size = list->backing_size;
    before.size = list->size;
    before.backing_array = list->backing_array;

    // actual shallow copy tests
    void** out_data;

    // failed shallow copies
    assert(shallow_copy(NULL, &out_data) == false);
    assert(shallow_copy(list, NULL) == false);

    // successful

    // should call malloc exactly once
    assert(shallow_copy(list, &out_data) == true);

    // arraylist should not have changed
    assert(before.size == list->size);
    assert(before.backing_size == list->backing_size);
    assert(before.backing_array == list->backing_array);

    // check malloc and free calls
    assert(free_count == 0);
    assert(invalid_free == 0);
    assert(call_info.count == 3);
    assert(in_last_n(&call_info,  sizeof(void*)*before.size, 1) == true);

    // check backing array
    assert(list->backing_array != out_data);
    for(int i = 0; i <= 20; i++) {
        assert(out_data[i] == list->backing_array[i]);
    }

    free(out_data);
    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 3);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_shallow_copy()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

// shallow copy fail
int test_shallow_copy_fail() {
    printf("[%sFAIL%s] test_shallow_copy_fail()\n", TERM_RED, TERM_RESET);
    call_info.successful_malloc_calls = 2;
    free_count = 0;
    invalid_free = 0;

    // setup array list with backing array of size 40
    // 2 malloc calls
    array_list* list = malloc(sizeof(array_list));
    memset(list, 0, sizeof(array_list));

    list->backing_array = malloc(sizeof(void*)*40);
    memset(list->backing_array, 0, sizeof(void*)*40);
    list->backing_size = 40;

    //add 21 items to backing array
    for(int i = 0; i <= 20; i++) {
        list->backing_array[i] = (void*)(uintptr_t)i;
        list->size++;
    }

    // save state before calling shallow_copy
    array_list before = {0,0,NULL};
    before.backing_size = list->backing_size;
    before.size = list->size;
    before.backing_array = list->backing_array;

    // actual shallow copy tests
    void** out_data;

    // failed shallow copies
    assert(shallow_copy(NULL, &out_data) == false);
    assert(shallow_copy(list, NULL) == false);
    assert(shallow_copy(list, &out_data) == false);

    // arraylist should not have changed
    assert(before.size == list->size);
    assert(before.backing_size == list->backing_size);
    assert(before.backing_array == list->backing_array);

    // check malloc and free calls
    assert(free_count == 0);
    assert(invalid_free == 0);
    assert(call_info.count == 3);
    assert(in_last_n(&call_info,  sizeof(void*)*before.size, 1) == true);

    free(list->backing_array);
    free(list);

    assert(cleaned(&call_info) == true);
    assert(free_count == 2);
    assert(invalid_free == 0);

    cleanup(&call_info);
    printf("\b\r[%sPASS%s] test_shallow_copy_fail()\n", TERM_GREEN, TERM_RESET);

    return 0;
}

int test_destroy() {
    printf("[%sFAIL%s] test_destroy()\n", TERM_RED, TERM_RESET);
    call_info.successful_malloc_calls = 46;
    free_count = 0;
    invalid_free = 0;

    // setup array list with backing array of size 40
    // 2 malloc calls
    array_list* list = malloc(sizeof(array_list));
    memset(list, 0, sizeof(array_list));

    list->backing_array = malloc(sizeof(void*)*40);
    memset(list->backing_array, 0, sizeof(void*)*40);
    list->backing_size = 40;

    //add 21 (42 malloc calls)
    for(int i = 0; i <= 20; i++) {
        char temp_name[50];
        sprintf(temp_name, "stuff:%d", i);
        person* p = create_person(temp_name, i);
        list->backing_array[i] = p;
        list->size++;
    }

    // destroy

    // actual destroy tests
    destroy(list, free_person);
    assert(free_count == 44);
    assert(invalid_free == 0);
    assert(call_info.count == 44);
    assert(cleaned(&call_info) == true);

    printf("\b\r[%sPASS%s] test_destroy()\n", TERM_GREEN, TERM_RESET);

    return 0;
}
