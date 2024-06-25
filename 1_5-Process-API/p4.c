#include <ctype.h>

#include "common.h"

/*
    Write a program that calls fork() and then calls some form of
    exec() to run the program /bin/ls. See if you can try all of the
    variants of exec(), including (on Linux) execl(), execle(),
    execlp(), execv(), execvp(), and execvpe(). Why do
    you think there are so many variants of the same basic call?
*/

typedef enum ExecFlavor
{
    L, LP, LE,
    V, VP, VE

} ExecFlavor;

static ExecFlavor exec_flavor = L;

void child_function()
{
    char* path = "/bin/ls";
    char* program = "ls";
    char* args[2] = {program, NULL};
    char* env[2] = {"HOME=/home", "MY_FLAG=flag"};

    switch (exec_flavor)
    {
        case L:  execl(path, args[0], args[1]);        break;
        case LP: execlp(program, args[0], args[1]);    break;
        case LE: execle(path, args[0], args[1], env);  break;
        case V:  execv(path, args);                    break;
        case VP: execvp(program, args);                break;
        case VE: execve(path, args, env);              break;
    }
}

void parent_function()
{
    wait(NULL);
}

int chars_match(char test, char target)
{
    return (test == target || test == (char)(toupper(target)));
}

void handle_input(int argc, char* argv[])
{
    const char list = 'l';
    const char vector = 'v';
    const char prog = 'p';
    const char env = 'e';

    int isList = 1;
    int isName = 0;
    int hasEnv = 0;

    if (argc < 2)
    {
        printf("Missing Args: lvpe\n");
        exit(1);
    }

    char* arg = argv[1];
    for (int i = 0; i < strlen(arg); i++)
    {
        if (chars_match(arg[i], list))         isList = 1;
        else if (chars_match(arg[i], vector))  isList = 0;
        else if (chars_match(arg[i], prog))    isName = 1;
        else if (chars_match(arg[i], env))     hasEnv = 1;
    }

    if (isList)
    {
        if (isName) exec_flavor = LP;
        else if (hasEnv) exec_flavor = LE;
        else exec_flavor = L;
    }
    else
    {
        if (isName) exec_flavor = VP;
        else if (hasEnv) exec_flavor = VE;
        else exec_flavor = V;
    }
    printf("Running flavor %d\n", exec_flavor);
}

int main(int argc, char* argv[])
{
    supress_output = 1;
    handle_input(argc, argv);
    zfork(&child_function, &parent_function);
}