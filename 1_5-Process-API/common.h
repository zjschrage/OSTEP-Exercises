#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

typedef void (*Action)(void);

void zackFork(Action child, Action parent)
{
    printf("PID: %d\n", (int)getpid());
    int rc = fork();  

    if (rc < 0)
    {
        printf("Fork failed\n");
    }
    else if (rc == 0)
    {
        printf("Child process %d!\n", (int)getpid());
        if (child != NULL)
            child();
        printf("Child process terminated\n");
    }
    else
    {
        printf("Parent process %d! Child PID: %d\n", (int)getpid(), rc);
        if (parent != NULL)
            parent();
        printf("Parent process terminated\n");
    }
}