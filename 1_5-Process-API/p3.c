#include <fcntl.h>

#include "common.h"

/*
    Write another program using fork(). The child process should
    print “hello”; the parent process should print “goodbye”. You should
    try to ensure that the child process always prints first; can you do
    this without calling wait() in the parent?
*/

static const char* child_status_file = "./static/child_status.txt";
static const char child_terminate_char[] = "T";

void child_function()
{
    printf("hello");
    fflush(stdout);
    int fd = open(child_status_file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
    if (fd < 0)
    {
        perror("Error:");
        exit(1);
    }
    write(fd, child_terminate_char, sizeof(child_terminate_char));
    close(fd);
}

void parent_function()
{
    while (1)
    {
        int fd = open(child_status_file, O_RDONLY, S_IRUSR);
        if (fd >= 0)
        {
            char buf[8];
            read(fd, buf, sizeof(buf));
            if (buf[0] == child_terminate_char[0])
                break;
        }
    }
    printf("goodbye\n");
    int fd = open(child_status_file, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
    if (ftruncate(fd, 0) < 0)
    {
        perror("File Truncation Error:");
        close(fd);
    }
    close(fd);
}

int main(int argc, char* argv[])
{
    supress_output = 1;
    zfork(&child_function, &parent_function);
    return 0;
}