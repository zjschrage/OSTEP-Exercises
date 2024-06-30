#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define ZPRINTF(fmt, ...)                            \
    do {                                             \
        char output_buffer[BUFFER_SIZE];             \
        sprintf(output_buffer, fmt, ##__VA_ARGS__);  \
        if (!supress_output)                         \
            printf("%s", output_buffer);             \
    } while (0)

typedef void (*Action)(void);

static int supress_output = 0;

static void zfork(Action child, Action parent)
{
    ZPRINTF("PID: %d\n", (pid_t)getpid());
    pid_t rc = fork();  

    if (rc < 0)
    {
        perror("Fork failed");
    }
    else if (rc == 0)
    {
        ZPRINTF("Child process %d!\n", (pid_t)getpid());
        if (child != NULL)
            child();
        ZPRINTF("Child process terminated\n");
    }
    else
    {
        ZPRINTF("Parent process %d! Child PID: %d\n", (pid_t)getpid(), rc);
        if (parent != NULL)
            parent();
        ZPRINTF("Parent process terminated\n");
    }
}