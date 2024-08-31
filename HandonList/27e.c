//Vikash Kumar Jaiswal
// MT2024168
/*
Question:  Write a program to execute ls -Rl by the following system calls 
    5. execvp
*/
#include <unistd.h> // Import for `execvp` function
#include <stdio.h>  // Import for `printf` function

int main()
{
    // Command name, options, file name
    char *args[] = {"ls", "-Rl", "./sample-files", NULL}; // Set the last but one argument if you want to execute `ls` command on a particular file

    printf("============OUTPUT USING execvp===============\n");

    // Execute the `ls -Rl` command
    execvp(args[0], args);

    // If execvp is successful, the following line will not be executed
    perror("execvp failed");
    return 1; // Return a non-zero value to indicate an error
}
//output
/*============OUTPUT USING execvp===============
<output of `ls -Rl ./sample-files`>
*/