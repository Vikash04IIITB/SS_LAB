#include <unistd.h> // Import for `execl` library function
#include <stdio.h>  // Import for `perror` function

int main()
{
    char *executable_path = "./.out-files/14.out";
    char *arg = "14.c";

    // Attempt to execute the specified program
    if (execl(executable_path, executable_path, arg, NULL) == -1)
    {
        // If execl fails, print the error
        perror("execl failed");
        return 1; // Return a non-zero value to indicate an error
    }

    // This line will not be reached if execl is successful
    return 0;
}
//OUTPUT
/* Child A created...
Putting child A to sleep for 5 seconds
Child B created...
Putting child B to sleep for 10 seconds
Child C created...
Putting child C to sleep for 15 seconds
Child A is now awake!
Child B is now awake!
Child C is now awake!
Child C has terminated with exit status = 0
*/