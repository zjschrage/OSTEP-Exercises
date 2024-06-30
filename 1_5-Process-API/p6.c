#include "common.h"

/*
    Now write a program that uses wait() to wait for the child process
    to finish in the parent. What does wait() return? What happens if
    you use wait() in the child?
*/



int main(int argc, char* argv[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Fork Failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child waiting for pid %d\n", -1);
        waitpid(-1, NULL, 0);
        printf("Child done\n");
    }
    else
    {
        printf("Parent waiting for pid %d\n", pid);
        waitpid(pid, NULL, 0);
        printf("Parent done\n");
    }
    return 0;
}
