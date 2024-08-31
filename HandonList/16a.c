// Vikash Kumar Jaiswal
// MT2024168
/*
Question: Write a program to perform mandatory locking. 
    - Implement write lock 
*/

#include <unistd.h>    // For `getpid`
#include <fcntl.h>     // For `fcntl`, `open`, `F_WRLCK`, `F_RDLCK`
#include <sys/types.h> // For `open`
#include <sys/stat.h>  // For `open`
#include <stdio.h>     // For `printf`

void main(int argc, char *argv[])
{
    char *filename;
    struct flock lock, lockStatus;
    int fileDescriptor;
    int result;

    if (argc != 2)
    {
        printf("Pass the file name to be locked as the argument!\n");
        return;
    }

    filename = argv[1];

    // Defining lock parameters
    lock.l_type = F_WRLCK;    // Write lock
    lock.l_whence = SEEK_SET; // Seek to start of the file
    lock.l_start = 0;         // Lock from start of the file
    lock.l_len = 0;           // Locks the entire file
    lock.l_pid = getpid();

    // Copying lock contents, used for checking if a lock has already been placed on the file
    lockStatus = lock;

    // Opening the file
    fileDescriptor = open(filename, O_RDWR);
    if (fileDescriptor == -1)
    {
        perror("Error opening file");
        return;
    }

    // Checking file lock status
    result = fcntl(fileDescriptor, F_GETLK, &lockStatus);
    if (result == -1)
    {
        perror("Error getting lock status");
        close(fileDescriptor);
        return;
    }

    if (lockStatus.l_type == F_WRLCK) // File already has a write lock
        printf("File already locked for writing\n");
    else if (lockStatus.l_type == F_RDLCK) // File already has a read lock
        printf("File already locked for reading\n");
    else
    {
        // Applying lock
        result = fcntl(fileDescriptor, F_SETLK, &lock);
        if (result == -1)
        {
            perror("Error setting lock");
        }
        else
        {
            printf("File is now locked for writing\n");
        }
    }

    // Close the file descriptor
    close(fileDescriptor);
}
//output
//File is now locked for writing
