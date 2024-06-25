#include <fcntl.h>

#include "common.h"

/*
    Write a program that opens a file (with the open() system call)
    and then calls fork() to create a new process. Can both the child
    and parent access the file descriptor returned by open()? What
    happens when they are writing to the file concurrently, i.e., at the
    same time?
*/

static int parentWaits = 0;
static const char* testFile = "./static/file.txt";

int openFile(const char* path)
{
    int fd = open(path, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
    if (fd < 0)
    {
        printf("Error Opening File %s\n", path);
        perror("Error:");
        exit(1);
    }
    printf("Opened File Descriptor = %d\n", fd);
    return fd;
}

void closeFile(int fd)
{
    if (close(fd) < 0)
    {
        printf("Error Closing File Descriptor %d\n", fd);
        perror("Error:");
        exit(1);
    }
    printf("Closed File Descriptor.\n");
}

void childFunction()
{
    int fd = openFile(testFile);
    write(fd, "child", 5);
    sleep(1);
    closeFile(fd);
}

void parentFunction()
{
    if (parentWaits)
    {
        wait(NULL);
        printf("Parent finished waiting for child\n");
    }

    int fd = openFile(testFile);
    write(fd, "PARENT", 6);
    sleep(1);
    closeFile(fd);
}

void handleInput(int argc, char* argv[])
{
    if (argc > 1)
        parentWaits = 1;
}

int main(int argc, char* argv[])
{
    handleInput(argc, argv);
    zackFork(&childFunction, &parentFunction);
    return 0;
}