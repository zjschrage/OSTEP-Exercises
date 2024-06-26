#include "common.h"

/*
    Write a program that calls fork(). Before calling fork(), have the
    main process access a variable (e.g., x) and set its value to something (e.g., 100).
    What value is the variable in the child process?
    What happens to the variable when both the child and parent change
    the value of x?
*/

static int x = 100;

void x_manipulator(int* x, int add)
{
    int old = *x;
    *x += add;
    printf("Incremented x from (%d) to (%d)\n", old, *x);
}

void child_function()
{
    x_manipulator(&x, 23);
}

void parent_function()
{
    wait(NULL);
    printf("Parent finished waiting for child\n");
    x_manipulator(&x, 29);
}

int main(int argc, char* argv[])
{
    zfork(&child_function, &parent_function);
    return 0;
}
