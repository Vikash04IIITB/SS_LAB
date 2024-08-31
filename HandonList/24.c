#include <sys/types.h> // Import for `fork` system call
#include <unistd.h>    // Import for `fork` system call
#include <stdio.h>     // Import for `printf` function
#include <stdlib.h>    // Import for `exit` function

int main()
{
    pid_t childPid;

    // Create a new process
    if ((childPid = fork()) > 0)
    {
        // Parent process
        printf("Parent PID: %d\n", getpid());
        printf("Parent is going to sleep for 10s...\n");
        sleep(10); // Parent process sleeps for 10 seconds
        printf("Parent is now exiting...\n");
        exit(0); // Terminate the parent process
    }
    else if (childPid == 0)
    {
        // Child process
        printf("Child PID: %d\n", getpid());
        printf("Child is going to sleep for 100s...\n");
        sleep(100); // Child process sleeps for 100 seconds
        printf("Child is now awake!\n");
    }
    else
    {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
//output
/*Parent PID: <parent_pid>
Parent is going to sleep for 10s...
Child PID: <child_pid>
Child is going to sleep for 100s...

Parent is now exiting...

Child is now awake!

*/