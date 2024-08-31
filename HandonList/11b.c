// Vikash Kumar Jaiswal
// MT2024168
// Question: Write a program to open a file, duplicate the file descriptor using `dup2`, and append data using both descriptors.

#include <unistd.h>    // Import for `dup2` system call
#include <sys/types.h> // Import for `open` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open` system call
#include <stdio.h>     // Import for `perror` & `printf` functions

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int fileDescriptor, dupFileDescriptor;
    ssize_t writeByteCount;

    // Open the file in write-only mode with append flag, create it if necessary
    fileDescriptor = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (fileDescriptor == -1)
    {
        perror("Error while opening file");
        return 1;
    }

    // Duplicate the file descriptor using `dup2`
    dupFileDescriptor = dup2(fileDescriptor, 123); // 123 is an arbitrary file descriptor number
    if (dupFileDescriptor == -1)
    {
        perror("Error while duplicating file descriptor");
        close(fileDescriptor);
        return 1;
    }

    // Write to the file using the original file descriptor
    writeByteCount = write(fileDescriptor, "Using original FD\n", 19);
    if (writeByteCount == -1)
    {
        perror("Error while writing file using original FD");
        close(fileDescriptor);
        close(dupFileDescriptor);
        return 1;
    }

    // Write to the file using the duplicated file descriptor
    writeByteCount = write(dupFileDescriptor, "Using duplicate FD\n", 21);
    if (writeByteCount == -1)
    {
        perror("Error while writing file using duplicate FD");
        close(fileDescriptor);
        close(dupFileDescriptor);
        return 1;
    }

    // Close both file descriptors
    close(fileDescriptor);
    close(dupFileDescriptor);

    return 0;
}
//output
//Using original FD
//Using duplicate FD

