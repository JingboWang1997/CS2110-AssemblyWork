#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Here we are going to write some functions to support a list that stores
 * person data (name, age)
 */
struct person {
    char *name;
    int age;
};

/* Example functions given to you. If you want to truly grasp these concepts,
 * try writing your own structs and functions as well!
 */

// Create a new person
struct person *create_person(const char *name, int age) {
    struct person *p = (struct person*) malloc(sizeof(struct person));
    p->name = malloc(strlen(name) + 1);

    if (!p->name) {
        return NULL;
    }

    strcpy(p->name, name);
    p->age = age;
    return p;
}

static int print_count;
static char *last_printed;

// Print a person
void print_person(void *data) {
    struct person *p = (struct person*) data;
    ++print_count;
    last_printed = p->name;
    printf("%s, %d\n", p->name, p->age);
}

// Copy a person
bool copy_person(const void *data, void **data_out) {
    struct person *p = (struct person*) data;
    struct person *result = create_person(p->name, p->age);

    // If malloc() failed in create_person(), don't bother returning NULL
    // through data_out
    if (result) {
        *data_out = result;
    }

    return !!result;
}

// Free a person
void free_person(void *data) {
    // This is safe because we should only be passing in person struct pointers
    struct person *p = (struct person*) data;
    // free any malloc'd pointers contained in the person struct (just name)
    free(p->name);
    // Now free the struct itself; this takes care of non-malloc'd data, like age.
    free(p);
}

// Compare people by age
int person_age_comp(const void *data1, const void *data2) {
    struct person *p1 = (struct person*) data1;
    struct person *p2 = (struct person*) data2;
    return p1->age - p2->age;
}

// Compare people by name
int person_name_comp(const void *data1, const void *data2) {
    struct person *p1 = (struct person*) data1;
    struct person *p2 = (struct person*) data2;
    return strcmp(p1->name, p2->name);
}

// Tell if a person is age 50
int is_age_50(const void *data) {
    struct person *p = (struct person*) data;
    return p->age == 50;
}

// Tell if a person is 23 or older
int is_age_23_or_greater(const void *data) {
    struct person *p = (struct person*) data;
    return p->age >= 23;
}

/* This main function does a little testing. Like all good CS Majors, you should
 * test your code here. There is no substitute for testing and you should be
 * sure to test for all edge cases, like calling empty_list on an empty list.
 */
int main(void) {
    int list_size;
    struct person *ptemp;

    printf("\nTEST CASE 1\nAn empty list should have size 0:\n");
    list *d1 = create_list();
    list_size = -1;
    assert(size(d1, &list_size));
    assert(0 == list_size);
    printf("Size: %d\n", list_size);
    assert(!d1->head);

    printf("\nTEST CASE 2\nAfter adding one element, size should be 1:\n");
    push_front(d1, create_person("Andrew", 26));
    list_size = -1;
    assert(size(d1, &list_size));
    printf("Size: %d\n", list_size);
    assert(list_size == 1);

    printf("\nTEST CASE 3\nTraversal should print the one element:\n");
    print_count = 0;
    last_printed = NULL;
    assert(traverse(d1, print_person));
    assert(!strcmp(last_printed, "Andrew") && print_count == 1);

    printf("\nTEST CASE 4\nThe one element should be the front and back:\n");
    print_count = 0;
    last_printed = NULL;
    struct person *andy = NULL;
    assert(front(d1, (void **)&andy));
    print_person(andy);
    assert(!strcmp(last_printed, "Andrew") && print_count == 1);

    print_count = 0;
    andy = NULL;
    assert(back(d1, (void **) &andy));
    print_person(andy);
    assert(!strcmp(last_printed, "Andrew") && print_count == 1);

    printf("\nTEST CASE 5\nAndrew should be contained in the list:\n");
    struct person *andrew = create_person("Andrew", 50);
    ptemp = NULL;
    printf("Andrew %s in list\n", contains(d1, andrew, person_name_comp,
           (void **)&ptemp) ? "is" : "isn\'t");
    assert(ptemp->age == 26);

    printf("\nTEST CASE 6\nCollin should not be contained in the list:\n");
    struct person *collin = create_person("Collin", 23);
    ptemp = NULL;
    printf("Collin %s in list\n", contains(d1, collin, person_name_comp,
           (void **)&ptemp) ? "is" : "isn\'t");
    assert(!contains(d1, collin, person_name_comp, (void **)&ptemp));

    printf("\nTEST CASE 7\nPop Andrew from the front...\n");
    ptemp = NULL;
    assert(pop_front(d1, (void **)&ptemp));
    assert(size(d1, &list_size));
    assert(!list_size);
    assert(!person_name_comp(andrew, ptemp));
    printf("Success!\n");
    free_person(ptemp);

    printf("\nTEST CASE 8\nAdd Collin, pop from the back...\n");
    add(d1, 0, collin);
    assert(size(d1, &list_size));
    assert(list_size == 1);
    ptemp = NULL;
    assert(list_remove(d1, 0, (void **)&ptemp));
    assert(ptemp == collin);
    list_size = -1;
    assert(size(d1, &list_size));
    printf("Size is %d\n", list_size);
    list_size = -1;
    assert(size(d1, &list_size));
    assert(!list_size);
    printf("Success!\n");

    // Free these people because we are done using them
    free_person(andrew);
    andrew = NULL;
    free_person(collin);
    collin = NULL;

    printf("\nTEST CASE 9\nThere should be 7 elements in this list:\n");
    list *d2 = create_list();
    assert(push_front(d2, create_person("Nick", 23)));
    assert(push_front(d2, create_person("Henry", 21)));
    assert(push_front(d2, create_person("Marie", 22)));
    assert(push_front(d2, create_person("Clayton", 24)));
    assert(push_front(d2, create_person("Andrew", 25)));
    assert(push_front(d2, create_person("Brandon", 28)));
    assert(push_front(d2, create_person("Leahy", 66)));
    list_size = -1;
    assert(size(d2, &list_size));
    printf("Size: %d\n", list_size);
    list_size = -1;
    assert(size(d2, &list_size));
    assert(list_size == 7);

    printf("\nTEST CASE 10\nFront should be last element pushed to front (Leahy):\n");
    assert(front(d2, (void **)&ptemp));
    print_person(ptemp);
    struct person *leahy = create_person("Leahy", 67);
    assert(!person_name_comp(leahy, ptemp));
    assert(ptemp->age == 66);

    printf("\nTEST CASE 11\nLast element pushed (Nick):\n");
    assert(get(d2, 6, (void **)&ptemp));
    print_person(ptemp);
    struct person *nick = create_person("Nick", 23);
    assert(!person_name_comp(nick, ptemp));
    assert(ptemp->age == 23);

    printf("\nTEST CASE 12\nThe person at index 2 should be Andrew:\n");
    assert(get(d2, 2, (void **)&ptemp));
    print_person(ptemp);
    struct person *andrew1 = create_person("Andrew", 25);
    assert(!person_name_comp(andrew1, ptemp));
    assert(ptemp->age == 25);

    printf("\nTEST CASE 13\nThere should be someone age 24 in the list:\n");
    struct person *person24 = create_person("", 24);
    assert(contains(d2, person24, person_age_comp, (void **)&ptemp));
    print_person(ptemp);
    assert(!strcmp(ptemp->name, "Clayton"));

    printf("\nTEST CASE 14\nThere should be nobody age 30 in the list:\n");
    struct person *person30 = create_person("", 30);
    assert(!contains(d2, person30, person_age_comp, (void **)&ptemp));
    if(ptemp) {
        printf("Found: ");
        print_person(ptemp);
    } else {
        printf("Success!\n");
    }
    assert(!ptemp);

    // Clean up temporary people
    free_person(leahy);
    free_person(nick);
    free_person(andrew1);
    free_person(person24);
    free_person(person30);

    printf("\nTEST CASE 15\nPopping front twice leaves a size 5 list:\n");
    struct person* return_person;

    pop_front(d2, (void **) &return_person);
    free_person(return_person);
    return_person = NULL;
    pop_front(d2, (void **) &return_person);
    free_person(return_person);
    return_person = NULL;
    assert(size(d2, &list_size));
    printf("Size: %d\n", list_size);
    assert(list_size == 5);

    printf("\nTEST CASE 16\nPrint the 5 elements from the list:\n");
    print_count = 0;
    last_printed = NULL;
    assert(true == traverse(d2, print_person));
    assert(print_count == 5);
    assert(!strcmp(last_printed, "Nick"));

    // Empty the list now that we're done with it
    empty_list(d2, free_person);
    assert(size(d2, &list_size));
    assert(!list_size);

    printf("\nTEST CASE 20\nLet's try making a  deep copy of a list of 4 people:\n");
    list *d3 = create_list();
    push_front(d3, create_person("Baijun", 20));
    push_front(d3, create_person("Brandi", 21));
    push_front(d3, create_person("Patrick", 19));
    push_front(d3, create_person("Shayan", 22));
    printf("Original:\n");
    traverse(d3, print_person);
    printf("Copy:\n");
    list *d4 = deep_copy_list(d3, copy_person, free_person);
    print_count = 0;
    last_printed = NULL;
    traverse(d4, print_person);
    assert(print_count == 4);
    assert(!strcmp(last_printed, "Baijun"));

    printf("\nTEST CASE 21\nAfter emptying first list, second should persist:\n");
    empty_list(d3, free_person);
    print_count = 0;
    last_printed = NULL;
    traverse(d4, print_person);
    assert(print_count == 4);
    assert(!strcmp(last_printed, "Baijun"));
    empty_list(d4, free_person);
    assert(size(d4, &list_size));
    assert(!list_size);

    printf("\nTEST CASE 22\n shallow copy test, both data pointers should be the same\n");

    list *d5 = create_list();
    push_front(d5, create_person("quavo", 23));
    push_front(d5, create_person("offset", 24));
    push_front(d5, create_person("takeoff", 23));
    list *d6 = shallow_copy_list(d5);

    struct person *temp_1, *temp_2;
    for(int i = 0; i < 3; i++)
    {
        get(d5, i, (void **) &temp_1);
        get(d6, i, (void **) &temp_2);
        assert(temp_1 == temp_2);
    }

    // delete the original list
    empty_list(d5, free_person);

    // since the data d6 points to has already been freed, we cannot call
    // empty_list on it since it will double free the data. We can pop the
    // front of the list and safely ignore the data values each pop returns.

    void *Data;
    while(pop_front(d6, &Data));
    //NOTE: do not call empty on d6 since it is a shallow copy, the data has
    // already been freed
    printf("\nTEST CASE 23\n reverse test\n");
    list *d7 = create_list();
    struct person *temp_3;
    struct person *gucci = create_person("Radric Davis", 37);
    struct person *zaytoven = create_person("Xavier Lamar Dotson", 37);
    struct person *mikeWillMadeIt = create_person("Michael Len Williams", 28);

    push_back(d7, gucci);
    push_back(d7, zaytoven);
    push_back(d7, mikeWillMadeIt);

    reverse(d7);


    get(d7,0, (void **) &temp_3);
    assert(temp_3 == mikeWillMadeIt);

    get(d7, 1, (void **) &temp_3);
    assert(temp_3 == zaytoven);

    get(d7, 2, (void **) &temp_3);
    assert(temp_3 == gucci);
    empty_list(d7, free_person);


    printf("\nTEST CASE 24\n concat test\n");
    list *d8 = create_list();
    list *d9 = create_list();
    struct person *temp_4;
    int temp_size = 0;
    struct person *travisScott = create_person("Jacques Webster", 37);
    struct person *swaeLee = create_person("Khalif Malik Ibn Shaman Brown", 24);
    struct person *slimJxmmi = create_person("Aaquil Brow", 28);
    struct person *lilYatchy = create_person("Miles Parks McCollum", 20);
    struct person *youngThug = create_person("Jeffery Lamar Williams", 26);

    push_back(d8, travisScott);
    push_back(d8, swaeLee);
    push_back(d8, slimJxmmi);

    push_back(d9, lilYatchy);
    push_back(d9, youngThug);

    assert(true == concat(d8, d9));

    size(d9, &temp_size);
    assert(0 == temp_size);
    assert(NULL == d9->head);
    assert(NULL == d9->tail);

    size(d8, &temp_size);
    assert(5 == temp_size);

    front(d8, (void **) &temp_4);
    assert(travisScott == temp_4);

    back(d8, (void **) &temp_4);
    assert(youngThug == temp_4);

    get(d8,0, (void **) &temp_4);
    assert(temp_4 == travisScott);

    get(d8,1, (void **) &temp_4);
    assert(temp_4 == swaeLee);

    get(d8,2, (void **) &temp_4);
    assert(temp_4 == slimJxmmi);

    get(d8,3, (void **) &temp_4);
    assert(temp_4 == lilYatchy);

    get(d8,4, (void **) &temp_4);
    assert(temp_4 == youngThug);


    empty_list(d8, free_person);


    printf("\nTEST CASE 25\nPassing in null lists to functions should return 0...\n");
    assert(NULL == shallow_copy_list(NULL));
    assert(NULL == deep_copy_list(NULL, NULL, NULL));
    assert(false == push_front(NULL, NULL));
    assert(false == push_back(NULL, NULL));
    assert(false == add(NULL, 0, NULL));
    assert(false == front(NULL, NULL));
    assert(false == back(NULL, NULL));
    assert(false == size(NULL, NULL));
    assert(false == contains(NULL, NULL, NULL, NULL));
    assert(false == pop_front(NULL, NULL));
    assert(false == pop_back(NULL, NULL));
    assert(false == list_remove(NULL, 0, NULL));
    assert(false == traverse(NULL, NULL));
    assert(false == reverse(NULL));
    assert(false == concat(NULL, NULL));
    printf("Success!\n");

    // TODO
    printf("\nMake sure to write more test cases as well in test.c! "
            "The ones given are NOT comprehensive.\n"
            "Also test using valgrind. No credit will be given to functions "
            "with memory leaks or memory errors.\n");

    // Clean up any malloc'd structures leftover to prevent memory leaks
    free(d1);
    free(d2);
    free(d3);
    free(d4);
    free(d5);
    free(d6);
    free(d7);
    free(d8);
    free(d9);
    return 0;
}
