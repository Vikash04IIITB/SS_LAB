// Vikash Kumar Jaiswal
// MT2024168

// Question: Write a program to take input from STDIN and display it on STDOUT using only read/write system calls

#include <unistd.h> // Required for `read` & `write` system calls
#include <stdio.h>  // Required for `perror` function

int main()
{
    char buffer[100];  // Buffer to store input data
    ssize_t bytesRead, bytesWritten;  // To store the number of bytes read/written

    while (1)
    {
        // Read one character from STDIN
        bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
        
        // Check for read errors or EOF
        if (bytesRead == -1)
        {
            perror("Error while reading from STDIN");
            break;
        }
        else if (bytesRead == 0) // EOF encountered
        {
            break;
        }

        // Write the character to STDOUT
        bytesWritten = write(STDOUT_FILENO, buffer, bytesRead);

        // Check for write errors
        if (bytesWritten == -1)
        {
            perror("Error while writing to STDOUT");
            break;
        }
    }

    return 0;
}

//OUTPUT
//
