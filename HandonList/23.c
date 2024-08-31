#include <sys/types.h> // Import for `fork` system call
#include <unistd.h>    // Import for `fork` system call
#include <stdio.h>     // Import for `printf` function
#include <stdlib.h>    // Import for `exit` function

int main()
{
    pid_t childPid;

    if ((childPid = fork()) > 0)
    {
        // Parent process
        printf("Parent PID: %d\n", getpid());
        printf("Putting parent to sleep for 100s!\n");
        sleep(100); // Put the parent process to sleep for 100s
        printf("Parent is now awake!\n");
    }
    else if (childPid == 0)
    {
        // Child process
        printf("Child PID: %d\n", getpid());
        printf("Exiting child!\n");
        exit(0); // Terminate the child process
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
Putting parent to sleep for 100s!
Child PID: <child_pid>
Exiting child!

After 100 seconds, the parent process will print:
Parent is now awake!

*/