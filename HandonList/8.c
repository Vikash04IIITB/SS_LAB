// Vikash Kumar Jaiswal
// MT2024168
// Question: Write a program to open a file in read-only mode, read line by line, and display each line as it is read. Close the file when the end of file is reached.

#include <sys/types.h> // Required for `open` system call
#include <sys/stat.h>  // Required for `open` system call
#include <fcntl.h>     // Required for `open` system call
#include <unistd.h>    // Required for `read` and `write` system calls
#include <stdio.h>     // Required for `perror` and `printf` functions

#define BUFFER_SIZE 1024 // Buffer size for reading lines

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    ssize_t i = 0;

    while ((bytesRead = read(fileDescriptor, buffer + i, 1)) > 0)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0'; // Null-terminate the line
            write(STDOUT_FILENO, buffer, i + 1); // Write the line to STDOUT
            i = 0; // Reset buffer index
        }
        else
        {
            i++;
        }

        // If the buffer is full, write out the content
        if (i >= BUFFER_SIZE - 1)
        {
            buffer[i] = '\0'; // Null-terminate the buffer
            write(STDOUT_FILENO, buffer, i);
            i = 0; // Reset buffer index
        }
    }

    // Write any remaining content in the buffer
    if (i > 0)
    {
        buffer[i] = '\0'; // Null-terminate the last line
        write(STDOUT_FILENO, buffer, i);
    }

    if (bytesRead == -1)
    {
        perror("Error reading file");
    }

    close(fileDescriptor);
    return 0;
}

//output
//Hello, World!
//This is a test.
//Goodbye!

