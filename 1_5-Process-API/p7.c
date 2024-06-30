#include "common.h"

/*
    Write a program that creates a child process, and then in the child
    closes standard output (STDOUT FILENO). What happens if the child
    calls printf() to print some output after closing the descriptor?
*/

void child_function()
{
    printf("Child: Before Closing STDOUT_FILENO\n");
    close(STDOUT_FILENO);
    printf("Child: After Closing STDOUT_FILENO\n");
}

void parent_function()
{
    wait(NULL);
    printf("Parent: After Waiting for Child\n");
}

int main(int argc, char* argv[])
{
    supress_output = 1;
    zfork(&child_function, &parent_function);
    return 0;
}