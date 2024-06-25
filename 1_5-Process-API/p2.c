#include <fcntl.h>

#include "common.h"

/*
    Write a program that opens a file (with the open() system call)
    and then calls fork() to create a new process. Can both the child
    and parent access the file descriptor returned by open()? What
    happens when they are writing to the file concurrently, i.e., at the
    same time?
*/

static int parent_waits = 0;
static const char* test_file = "./static/file.txt";

int open_file(const char* path)
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

void close_file(int fd)
{
    if (close(fd) < 0)
    {
        printf("Error Closing File Descriptor %d\n", fd);
        perror("Error:");
        exit(1);
    }
    printf("Closed File Descriptor.\n");
}

void child_function()
{
    int fd = open_file(test_file);
    write(fd, "child", 5);
    sleep(1);
    close_file(fd);
}

void parent_function()
{
    if (parent_waits)
    {
        wait(NULL);
        printf("Parent finished waiting for child\n");
    }

    int fd = open_file(test_file);
    write(fd, "PARENT", 6);
    sleep(1);
    close_file(fd);
}

void handle_input(int argc, char* argv[])
{
    if (argc > 1)
        parent_waits = 1;
}

int main(int argc, char* argv[])
{
    handle_input(argc, argv);
    zfork(&child_function, &parent_function);
    return 0;
}