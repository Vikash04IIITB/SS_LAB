#include <unistd.h>    // Import for `fork` system call
#include <sys/types.h> // Import for `open`, `fork` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open` system call
#include <stdio.h>     // Import for `perror` function

int main()
{
    char *filename = "./sample-files/pgm-22-sample.txt";
    int childPid, fileDescriptor;
    
    fileDescriptor = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
    if (fileDescriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    childPid = fork();
    if (childPid == -1) {
        perror("Error during fork");
        close(fileDescriptor);
        return 1;
    }

    if (childPid == 0) {
        // Child process
        if (write(fileDescriptor, "Child\n", 6) == -1) {
            perror("Error writing to file in child");
        }
    } else {
        // Parent process
        if (write(fileDescriptor, "Parent\n", 7) == -1) {
            perror("Error writing to file in parent");
        }
    }

    close(fileDescriptor);
    return 0;
}
//output
/*Child
Parent
*/