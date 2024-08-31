// Vikash Kumar Jaiswal
// MT2024168
// Question: Write a program to wait for STDIN for 10 seconds using select.

#include <sys/time.h>  // Import for `select` system call
#include <sys/types.h> // Import for `select` system call
#include <unistd.h>    // Import for `select` system call
#include <stdio.h>     // Import for `perror` & `printf` function

int main()
{
    fd_set readFDSet;  // Set of file descriptors to read from
    struct timeval timeout;  // Timeout period
    int returnVal;  // Return value of `select`

    // Initialize the file descriptor set
    FD_ZERO(&readFDSet);
    FD_SET(STDIN_FILENO, &readFDSet); // Add STDIN to the set of file descriptors to read from

    // Set the timeout period to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // `select` waits for data to be available on any file descriptor in the set or until the timeout expires
    returnVal = select(STDIN_FILENO + 1, &readFDSet, NULL, NULL, &timeout);

    if (returnVal == -1)
    {
        perror("Error with select");
        return 1;
    }
    else if (returnVal == 0)
    {
        // Timeout occurred
        printf("No data was given for 10 seconds\n");
    }
    else
    {
        // Data is available on STDIN
        if (FD_ISSET(STDIN_FILENO, &readFDSet))
        {
            printf("Data is now available on STDIN\n");
        }
    }

    return 0;
}
//output
//Data is now available on STDIN
