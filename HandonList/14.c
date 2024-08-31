// Vikash Kumar Jaiswal
// MT2024168
/* Question: Write a program to find the type of a file. 
    1. Input should be taken from the command line. 
    2. The program should be able to identify any type of file.
*/

#include <sys/types.h> // Imports for using `stat` system call
#include <sys/stat.h>  // Imports for using `stat` system call
#include <unistd.h>    // Imports for using `stat` system call
#include <fcntl.h>     // Import for `O_RDONLY` flag
#include <stdio.h>     // Import for `printf` function

int main(int argc, char *argv[])
{
    struct stat statbuf;
    int fileDescriptor;
    ssize_t result;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor == -1)
    {
        perror("Error opening file");
        return 1;
    }

    if (fstat(fileDescriptor, &statbuf) == -1)
    {
        perror("Error getting file status");
        close(fileDescriptor);
        return 1;
    }

    close(fileDescriptor);

    switch (statbuf.st_mode & S_IFMT)
    {
    case S_IFBLK:
        result = write(STDOUT_FILENO, "Block File\n", 11);
        break;
    case S_IFCHR:
        result = write(STDOUT_FILENO, "Character File\n", 15);
        break;
    case S_IFDIR:
        result = write(STDOUT_FILENO, "Directory File\n", 15);
        break;
    case S_IFIFO:
        result = write(STDOUT_FILENO, "FIFO File\n", 10);
        break;
    case S_IFLNK:
        result = write(STDOUT_FILENO, "Symbolic Link File\n", 19);
        break;
    case S_IFREG:
        result = write(STDOUT_FILENO, "Regular File\n", 13);
        break;
    case S_IFSOCK:
        result = write(STDOUT_FILENO, "Socket\n", 7);
        break;
    default:
        result = write(STDOUT_FILENO, "Unknown\n", 8);
        break;
    }

    if (result == -1)
    {
        perror("Error writing to stdout");
        return 1;
    }

    return 0;
}
/*output
Block File
Character File
Directory File
FIFO File
Symbolic Link File
Regular File
Socket
Unknown
*/
