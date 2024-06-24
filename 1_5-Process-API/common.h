#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define ZPRINTF(fmt, ...)                           \
    do {                                            \
        char outputBuffer[BUFFER_SIZE];             \
        sprintf(outputBuffer, fmt, ##__VA_ARGS__);  \
        if (!supressOutput)                         \
            printf("%s", outputBuffer);             \
    } while (0)

typedef void (*Action)(void);

static int supressOutput = 0;

static void zackFork(Action child, Action parent)
{
    ZPRINTF("PID: %d\n", (int)getpid());
    int rc = fork();  

    if (rc < 0)
    {
        perror("Fork failed");
    }
    else if (rc == 0)
    {
        ZPRINTF("Child process %d!\n", (int)getpid());
        if (child != NULL)
            child();
        ZPRINTF("Child process terminated\n");
    }
    else
    {
        ZPRINTF("Parent process %d! Child PID: %d\n", (int)getpid(), rc);
        if (parent != NULL)
            parent();
        ZPRINTF("Parent process terminated\n");
    }
}