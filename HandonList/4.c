// Vikash Kumar Jaiswal
// MT2024168

// Question: Write a program to open an existing file in read-write mode. Test with the O_EXCL flag as well.

#include <sys/types.h> // Required for `open` system call
#include <sys/stat.h>  // Required for `open` system call
#include <fcntl.h>     // Required for `open` system call
#include <unistd.h>    // Required for `write` function
#include <stdio.h>     // Required for `printf` & `perror` functions

int main(int argc, char *argv[])
{
    int fileDescriptor; // File descriptor returned by `open`

    // Check if the correct number of arguments is provided
    if (argc != 2)
    {
        write(STDOUT_FILENO, "Usage: <program_name> <filename>\n", 33);
        return 1;
    }

    // Get the filename from command-line arguments
    char *filename = argv[1];

    // Attempt to open the file with read-write mode
    fileDescriptor = open(filename, O_RDWR);

    if (fileDescriptor == -1)
    {
        perror("Error opening the file in read-write mode");
        return 1;
    }

    printf("File opened successfully in read-write mode. File descriptor: %d\n", fileDescriptor);

    // Attempt to open the file with O_EXCL flag
    int fileDescriptorExcl = open(filename, O_RDWR | O_EXCL);

    if (fileDescriptorExcl == -1)
    {
        perror("Error opening the file with O_EXCL flag");
    }
    else
    {
        printf("File opened successfully with O_EXCL flag. File descriptor: %d\n", fileDescriptorExcl);
    }

    // Close the opened file descriptors
    close(fileDescriptor);
    close(fileDescriptorExcl);

    return 0;
}
//OUTPUT
//File opened successfully in read-write mode. File descriptor: [file_descriptor]
//File opened successfully with O_EXCL flag. File descriptor: [file_descriptor_excl]
