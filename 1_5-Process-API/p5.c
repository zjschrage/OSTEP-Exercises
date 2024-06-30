#include "common.h"

/*
    Now write a program that uses wait() to wait for the child process
    to finish in the parent. What does wait() return? What happens if
    you use wait() in the child?
*/

void child_function()
{
    printf("Child calling wait\n");
    //Will wait on any child process, but this child never spawned one, so execution continues
    wait(NULL);
    printf("Child done calling wait\n");
}

void parent_function()
{
    printf("Parent waiting for child\n");
    //Will wait on the one child process spawned by this parent
    wait(NULL);
    printf("Parent finished waiting for child\n");
}

int main(int argc, char* argv[])
{
    zfork(&child_function, &parent_function);
    return 0;
}
