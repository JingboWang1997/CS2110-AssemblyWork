#include <stdlib.h>
#include <stdio.h>

// Basic function pointer example

int add(int, int);
int subtract(int, int);
int multiply(int, int);
int divide(int, int);

// op is an fp to a function that takes in two ints and returns an int
int (*op)(int, int);

int main(int argc, char **argv)
{
    op = add;
    printf("sum is %d\n", op(10,5));

    // NOTE we are using &func which is equivalent to func
    op = &subtract;
    printf("difference is %d\n", op(100, 1));

    op = multiply;
    // NOTE (*func_pointer)(params) is equivalent to func_pointer(params)
    printf("product is %d\n",(*op)(5, 10));

    op = &divide;
    printf("quotient is %d\n", op(100, 2));

    // Showing &func and func are the same
    printf("&add is %p\n", &add);
    printf("add is  %p\n", add);

}

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}