#include <fcntl.h>

#include "common.h"

/*
    Write another program using fork(). The child process should
    print “hello”; the parent process should print “goodbye”. You should
    try to ensure that the child process always prints first; can you do
    this without calling wait() in the parent?
*/

static const char* childStatusFile = "./static/child_status.txt";
static const char childTerminateChar[] = "T";

void childFunction()
{
    printf("hello");
    int fd = open(childStatusFile, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
    if (fd < 0)
    {
        perror("Error:");
        exit(1);
    }
    write(fd, childTerminateChar, sizeof(childTerminateChar));
    close(fd);
}

void parentFunction()
{
    while (1)
    {
        int fd = open(childStatusFile, O_RDONLY, S_IRUSR);
        if (fd >= 0)
        {
            char buf[8];
            read(fd, buf, sizeof(buf));
            if (buf[0] == childTerminateChar[0])
                break;
        }
    }
    printf("goodbye\n");
    int fd = open(childStatusFile, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
    if (ftruncate(fd, 0) < 0)
    {
        perror("File Truncation Error:");
        close(fd);
    }
    close(fd);
}

int main(int argc, char* argv[])
{
    supressOutput = 1;
    zackFork(&childFunction, &parentFunction);
    return 0;
}