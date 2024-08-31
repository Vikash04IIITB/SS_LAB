// Vikash Kumar Jaiswal
// MT2024168

// Question: Create a symbolic link file using the `symlink` system call

#include <unistd.h> // Import for `symlink` & `write` system calls
#include <stdio.h>  // Import for `perror` & `printf` functions

// argv[1] -> File path
// argv[2] -> Symbolic Link File path
int main(int argc, char *argv[])
{
    char *filepath;     // File name of the source file
    char *softLinkPath; // File name of the symbolic link file

    int status; // 0 -> Success, -1 -> Error

    if (argc != 3)
    {
        printf("Enter the file path and symbolic link file path as the arguments to the program\n");
        return 1;
    }

    filepath = argv[1];
    softLinkPath = argv[2];

    status = symlink(filepath, softLinkPath);

    if (status == -1)
        perror("Error while creating symbolic link!");
    else
        printf("Successfully created a symbolic link. Check with the `ll` or `ls -l` command.\n");

    return 0;
}
//output
//Successfully created a symbolic link. Check with the `ll` or `ls -l` command.
