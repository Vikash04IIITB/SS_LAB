//Vikash Kumar Jaiswal
// MT2024168
/*
Question:  Write a program to execute `ls -Rl` by the following system calls 
    2. `execlp` 
*/

#include <unistd.h> // Import for `execlp` function
#include <stdio.h>  // Import for `printf` function

void main()
{
    char *command_path = "/bin/ls";
    char *options = "-Rl";
    char *file_arg = "./sample-files"; // Set if you want to execute `ls` command on a particular file

    printf("============OUTPUT USING execlp===============\n");
    execlp(command_path, command_path, options, file_arg, NULL);
    printf("\n");
}
//OUTPUT
/*The output will be a detailed list of files and directories in the ./sample-files directory, displayed recursively (-R) and in long format (-l). If the execlp call fails, it will print an error message indicating the failure reason.*/