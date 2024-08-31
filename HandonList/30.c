#include <time.h>      // Import for time-related functions
#include <stdio.h>     // Import for printf function
#include <stdlib.h>    // Import for atoi
#include <sys/types.h> // Import for fork, setsid
#include <unistd.h>    // Import for fork, setsid
#include <sys/stat.h>  // Import for umask
#include <errno.h>     // Import for errno

// Function to create a daemon process
void daemonize()
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        // Parent process exits
        exit(EXIT_SUCCESS);
    }

    // Child process becomes the daemon
    if (setsid() < 0) {
        perror("setsid failed");
        exit(EXIT_FAILURE);
    }

    if (chdir("/") < 0) {
        perror("chdir failed");
        exit(EXIT_FAILURE);
    }

    umask(0);

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s hour [minute [second]]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int hour = atoi(argv[1]);
    int minute = (argc > 2) ? atoi(argv[2]) : 0;
    int second = (argc > 3) ? atoi(argv[3]) : 0;

    time_t currentEpoch, deadlineEpoch;
    struct tm *deadline;

    time(&currentEpoch);
    deadline = localtime(&currentEpoch);

    deadline->tm_hour = hour;
    deadline->tm_min = minute;
    deadline->tm_sec = second;
    deadline->tm_year += 1900; // Correct year (tm_year is year since 1900)
    deadline->tm_mon += 1;     // Correct month (tm_mon is 0-based)

    // Handle end of year wrap-around
    if (mktime(deadline) < currentEpoch) {
        deadline->tm_year += 1; // Schedule for the next year if deadline is in the past
        deadlineEpoch = mktime(deadline);
    } else {
        deadlineEpoch = mktime(deadline);
    }

    // Create a daemon process
    daemonize();

    // Wait until the specified time
    do {
        time(&currentEpoch);
    } while (difftime(deadlineEpoch, currentEpoch) > 0);

    // Action to be taken after the specified time
    printf("Boo! Got ya!\n");

    return 0;
}
//output
/*Usage: <program> hour [minute [second]]
*/
