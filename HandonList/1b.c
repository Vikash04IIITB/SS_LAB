// Vikash Kumar Jaiswal
// MT2024168

// Question: Create a hard link using the `link` system call

#include <unistd.h> // Required for `link` system call
#include <stdio.h>  // Required for `perror` & `printf` functions

int main(int argc, char *argv[])
{
    // Define variables for the source file and the hard link path
    char *filePath;
    char *hardLinkPath;

    int status; // Holds the result of the `link` call, 0 -> Success, -1 -> Error

    // Check for correct number of arguments
    if (argc != 3)
    {
        printf("Usage: %s <source_file> <hard_link>\n", argv[0]);
        return 1;
    }

    filePath = argv[1];
    hardLinkPath = argv[2];

    // Attempt to create a hard link
    status = link(filePath, hardLinkPath);

    // Check for errors
    if (status == -1)
    {
        perror("Failed to create hard link");
        return 1;
    }

    // Success message
    printf("Hard link created successfully. Verify with `ls -l`.\n");

    return 0;
}
// OUTPUT
//Hard link created successfully. Verify with `ls -l`.

