// Vikash Kumar Jaiswal
// MT2024168
// Question: Write a program to find out the opening mode of a file. Use `fcntl`

#include <sys/types.h> // Import for `open` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open`, `fcntl` system call
#include <unistd.h>    // Import for `fcntl` system call
#include <stdio.h>     // Import required for `perror` & `printf` functions

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int fileDescriptor;
    int status;

    // Open the file in read-only mode
    fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor == -1)
    {
        perror("Error while opening the file");
        return 1;
    }

    // Get the file status flags
    status = fcntl(fileDescriptor, F_GETFL);
    if (status == -1)
    {
        perror("Error while executing fcntl");
        close(fileDescriptor);
        return 1;
    }

    // Check the access mode
    if ((status & O_ACCMODE) == O_RDONLY)
    {
        printf("The file has been opened with the flags: O_RDONLY\n");
    }
    else if ((status & O_ACCMODE) == O_WRONLY)
    {
        printf("The file has been opened with the flags: O_WRONLY\n");
    }
    else if ((status & O_ACCMODE) == O_RDWR)
    {
        printf("The file has been opened with the flags: O_RDWR\n");
    }
    else
    {
        printf("Unknown access mode\n");
    }

    // Check for additional flags
    if (status & O_CREAT)
    {
        printf("The file has been opened with the flag: O_CREAT\n");
    }
    if (status & O_TRUNC)
    {
        printf("The file has been opened with the flag: O_TRUNC\n");
    }
    if (status & O_APPEND)
    {
        printf("The file has been opened with the flag: O_APPEND\n");
    }

    close(fileDescriptor);
    return 0;
}
//output
//The file has been opened with the flag: O_APPEND
