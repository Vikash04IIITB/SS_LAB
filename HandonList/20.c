#include <unistd.h> // Import for `nice` system call
#include <stdio.h>  // Import for `printf` function
#include <stdlib.h> // Import for `atoi` function
#include <errno.h>  // Import for `errno` and `perror`

int main(int argc, char *argv[])
{
    int priority, newp;

    // Check if the user provided exactly one argument
    if (argc != 2) {
        printf("Usage: %s <integer value>\n", argv[0]);
        return 1;
    }

    // Convert the argument to an integer
    newp = atoi(argv[1]);

    // Get the current priority
    priority = nice(0);
    if (priority == -1 && errno != 0) {
        perror("Error getting priority");
        return 1;
    }
    printf("Current priority: %d\n", priority);

    // Set the new priority
    priority = nice(newp);
    if (priority == -1 && errno != 0) {
        perror("Error setting priority");
        return 1;
    }
    printf("New priority: %d\n", priority);

    return 0;
}
//output
/*Current priority: 0
New priority: 10
*/