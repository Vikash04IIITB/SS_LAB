#include <sys/types.h> // Import for `fork` & `getpid` system call
#include <unistd.h>    // Import for `fork` & `getpid` system call
#include <stdio.h>     // Import for printf function

int main()
{
    pid_t childPid, pid;

    pid = getpid(); // Get the parent process ID
    printf("Parent PID: %d\n", pid);

    childPid = fork(); // Fork the process

    if (childPid == -1) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (childPid == 0) {
        // Child process
        pid = getpid(); // Get the child process ID
        printf("Child PID: %d\n", pid);
    } else {
        // Parent process
        printf("Child PID: %d\n", childPid);
    }

    return 0;
}
//output
/*Parent PID: 1234
Child PID: 1235
Child PID: 1235
*/