// Vikash Kumar Jaiswal
// MT2024168

// Question: Write a program to create a file and print the file descriptor value using the `creat` system call

#include <sys/types.h> // Required for `creat` system call
#include <sys/stat.h>  // Required for `creat` system call
#include <fcntl.h>     // Required for `creat` system call
#include <stdio.h>     // Required for `printf` & `perror` functions

int main(int argc, char *argv[])
{
    int fileDescriptor; // File descriptor returned by `creat`

    // Check if the correct number of arguments is provided
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get the filename from command-line arguments
    char *filename = argv[1];

    // Create the file using `creat`
    fileDescriptor = creat(filename, S_IRWXU);

    // Check for errors
    if (fileDescriptor == -1)
    {
        perror("Failed to create the file");
        return 1;
    }

    // Success message
    printf("File created successfully. File descriptor: %d\n", fileDescriptor);

    return 0;
}
//OUTPUT
//File created successfully. File descriptor: [file_descriptor]

