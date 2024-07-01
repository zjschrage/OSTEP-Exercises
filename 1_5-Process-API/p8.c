#include "common.h"

/*
    Write a program that creates two children,
    and connects the standard output of one to the standard input of the other,
    using the pipe() system call.
*/

int pipefd[2];

void child_function()
{
    const int max_buffer_size = 1024;
    char buf[max_buffer_size];

    close(pipefd[1]);
    ssize_t bytes_read = read(pipefd[0], &buf, sizeof(buf));
    
    const char* delimiter = "\n";
    char* token = strtok(buf, delimiter);
    while (token != NULL)
    {
        int child_grep_pipe[2];
        const char* pattern = "main";
        printf("Greping for pattern %s in %s with pipe fd read %d write %d\n",
            pattern, token, child_grep_pipe[0], child_grep_pipe[1]);
        
        if (pipe(child_grep_pipe) == -1)
        {
            perror("Pipe Failed");
            exit(EXIT_FAILURE);
        }

        pid_t rc = fork();
        if (rc < 0)
        {
            perror("Fork Failed");
            exit(EXIT_FAILURE);
        }
        else if (rc == 0)
        {
            close(child_grep_pipe[0]);
            dup2(child_grep_pipe[1], STDOUT_FILENO);
            close(child_grep_pipe[1]);
        
            execlp("grep", "grep", pattern, token, NULL);
        }
        else
        {
            close(child_grep_pipe[1]);
            wait(NULL);

            char grep_buf[max_buffer_size];
            ssize_t child_bytes_read = read(child_grep_pipe[0], &grep_buf, sizeof(grep_buf));
            close(child_grep_pipe[0]);
            write(STDOUT_FILENO, grep_buf, child_bytes_read);
        }

        token = strtok(NULL, delimiter);
    }
    close(pipefd[0]);
}

void parent_function()
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    execlp("find", "find", ".", "-name", "p*.c", NULL);
}

int main(int argc, char* argv[])
{
    if (pipe(pipefd) == -1)
    {
        perror("Pipe Failed");
        exit(EXIT_FAILURE);
    }

    supress_output = 1;
    zfork(&child_function, &parent_function);
    return 0;
}