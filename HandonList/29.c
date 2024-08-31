#include <sched.h>    // Import for `sched_getscheduler` and `sched_setscheduler`
#include <sys/types.h> // Import for `getpid`
#include <unistd.h>    // Import for `getpid`
#include <stdio.h>     // Import for `perror` and `printf`

int main()
{
    int currentPolicy;
    pid_t pid;
    pid = getpid(); // Get the process ID of the current process
    struct sched_param priority;

    // Set desired priority (make sure it is valid for the scheduling policy)
    priority.sched_priority = 10;

    // Get the current scheduling policy
    currentPolicy = sched_getscheduler(pid);
    if (currentPolicy == -1) {
        perror("Error while getting current policy");
        return 1; // Return a non-zero value to indicate an error
    }

    // Print current scheduling policy
    switch (currentPolicy)
    {
    case SCHED_FIFO:
        printf("Current policy is FIFO\n");
        if (sched_setscheduler(pid, SCHED_RR, &priority) == -1) {
            perror("Error while setting policy to RR");
            return 1; // Return a non-zero value to indicate an error
        }
        printf("Policy has been changed to RR\n");
        break;

    case SCHED_RR:
        printf("Current policy is RR\n");
        if (sched_setscheduler(pid, SCHED_FIFO, &priority) == -1) {
            perror("Error while setting policy to FIFO");
            return 1; // Return a non-zero value to indicate an error
        }
        printf("Policy has been changed to FIFO\n");
        break;

    case SCHED_OTHER:
        printf("Current policy is OTHER\n");
        if (sched_setscheduler(pid, SCHED_RR, &priority) == -1) {
            perror("Error while setting policy to RR");
            return 1; // Return a non-zero value to indicate an error
        }
        printf("Policy has been changed to RR\n");
        break;

    default:
        fprintf(stderr, "Unknown scheduling policy\n");
        return 1; // Return a non-zero value to indicate an error
    }

    // Verify the change
    currentPolicy = sched_getscheduler(pid);
    if (currentPolicy == -1) {
        perror("Error while getting updated policy");
        return 1; // Return a non-zero value to indicate an error
    }
    printf("Updated policy is %d\n", currentPolicy);

    return 0; // Return 0 to indicate success
}

//output
/*Current policy is OTHER
Policy has been changed to RR
Updated policy is 2
*/