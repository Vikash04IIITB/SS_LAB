// Vikash Kumar Jaiswal
// MT2024168

// Question: Write a program to copy the contents of file1 to file2 (similar to `cp file1 file2`).

#include <sys/types.h> // Required for `open` system call
#include <sys/stat.h>  // Required for `open` system call
#include <fcntl.h>     // Required for `open` system call
#include <unistd.h>    // Required for `read` and `write` system calls
#include <stdio.h>     // Required for `perror` and `printf` functions

#define BUFFER_SIZE 1024 // Buffer size for reading and writing

int main(int argc, char *argv[])
{
    char *sourcePath;
    char *destinationPath;

    int sourceFD, destinationFD; // File descriptors for source and destination files
    ssize_t bytesRead;           // Number of bytes read from the source file
    ssize_t bytesWritten;        // Number of bytes written to the destination file

    char buffer[BUFFER_SIZE]; // Buffer to store file contents

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    sourcePath = argv[1];
    destinationPath = argv[2];

    // Open the source file in read-only mode
    sourceFD = open(sourcePath, O_RDONLY);
    if (sourceFD == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    // Create or truncate the destination file and open it in read-write mode
    destinationFD = open(destinationPath, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (destinationFD == -1)
    {
        perror("Error opening destination file");
        close(sourceFD);
        return 1;
    }

    // Read from the source file and write to the destination file
    while ((bytesRead = read(sourceFD, buffer, BUFFER_SIZE)) > 0)
    {
        bytesWritten = write(destinationFD, buffer, bytesRead);
        if (bytesWritten != bytesRead)
        {
            perror("Error writing to destination file");
            close(sourceFD);
            close(destinationFD);
            return 1;
        }
    }

    if (bytesRead == -1)
    {
        perror("Error reading from source file");
    }
    else
    {
        printf("File copied successfully!\n");
    }

    // Close file descriptors
    close(sourceFD);
    close(destinationFD);

    return 0;
}

//OUTPUT
//File copied successfully!

