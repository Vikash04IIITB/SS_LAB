//Vikash Kumar Jaiswal
// MT2024168
/*
Question:  Write a program to execute `ls -Rl` by the following system calls 
    3. `execle` 
*/

#include <unistd.h> // Import for `execle` function
#include <stdio.h>  // Import for `printf` function

int main()
{
    char *command_path = "/bin/ls";
    char *option1 = "-R";
    char *option2 = "-l";
    char *file_arg = "./sample-files"; // Directory or file to list

    printf("============OUTPUT USING execle===============\n");

    // Execute the `ls -Rl` command
    execle(command_path, "ls", option1, option2, file_arg, NULL, NULL);

    // If execle is successful, the following line will not be executed
    perror("execle failed");
    return 1; // Return a non-zero value to indicate an error
}
//OUTPUT
/*============OUTPUT USING execle===============
<output of `ls -Rl ./sample-files`>
*/