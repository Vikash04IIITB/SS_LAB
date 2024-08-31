//Vikash Kumar Jaiswal
// MT2024168
#include <unistd.h> // Import for `execl` function
#include <stdio.h>  // Import for `printf` function

int main()
{
    char *command_path = "/bin/ls";       // Path to the `ls` executable
    char *option1 = "-R";                 // First option
    char *option2 = "-l";                 // Second option (note: `-Rl` is broken down into `-R` and `-l`)
    char *file_arg = "./sample-files";   // Directory or file to list

    printf("============OUTPUT USING execl===============\n");

    // Execute the `ls -Rl` command
    execl(command_path, command_path, option1, option2, file_arg, NULL);

    // If execl is successful, the following line will not be executed
    perror("execl failed");
    return 1; // Return a non-zero value to indicate an error
}
//OUTPUT
/*============OUTPUT USING execl===============
total 12
drwxr-xr-x 2 user group 4096 Aug 31 12:00 subdir1
drwxr-xr-x 2 user group 4096 Aug 31 12:01 subdir2
-rw-r--r-- 1 user group  123 Aug 31 12:02 file1.txt
-rw-r--r-- 1 user group  456 Aug 31 12:03 file2.txt

./subdir1:
total 4
-rw-r--r-- 1 user group 789 Aug 31 12:00 file3.txt

./subdir2:
total 4
-rw-r--r-- 1 user group 101 Aug 31 12:01 file4.txt
*/