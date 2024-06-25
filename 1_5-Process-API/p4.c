#include "common.h"

/*
    Write a program that calls fork() and then calls some form of
    exec() to run the program /bin/ls. See if you can try all of the
    variants of exec(), including (on Linux) execl(), execle(),
    execlp(), execv(), execvp(), and execvpe(). Why do
    you think there are so many variants of the same basic call?
*/

void child_function()
{
    char* path = "/bin/ls";
    char* program = "ls";
    char* args[2] = {program, NULL};
    char* env[2] = {"HOME=/home", "MY_FLAG=flag"};

    //Only the first will execute since the first exec will overwrite program memory
    //Rearrange these and recompile to change the exec flavor
    execl(path, args[0], args[1]);
    execlp(program, args[0], args[1]);
    execle(path, args[0], args[1], env);
    execv(path, args);
    execvp(program, args);
    execve(path, args, env);
}

void parent_function()
{
    wait(NULL);
}

int main(int argc, char* argv[])
{
    supress_output = 1;
    zfork(&child_function, &parent_function);
}