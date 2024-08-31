//Vikash Kumar Jaiswal
// MT2024168
/*
Question:  Write a program to execute `ls -Rl` by the following system calls 
    4. `execv` 
*/

#include <unistd.h> // Import for `execv` function
#include <stdio.h>  // Import for `printf` function

int main()
{
    char *args[] = {"/bin/ls", "-Rl", "./sample-files", NULL}; // Command and arguments

    printf("============OUTPUT USING execv===============\n");

    // Execute the `ls -Rl` command
    execv(args[0], args);

    // If execv is successful, the following line will not be executed
    perror("execv failed");
    return 1; // Return a non-zero value to indicate an error
}
//output
/*============OUTPUT USING execv===============
<output of `ls -Rl ./sample-files`>
*/