//Vikash Kumar Jaiswal
// MT2024168
// Question : Write a program to get maximum and minimum real time priority

#include <sched.h> // Import for `sched_get_priority_*` functions
#include <stdio.h> // Import for `printf` and `perror`

int main()
{
    int maxPriority, minPriority;

    // Get maximum priority for the SCHED_RR (Round Robin) scheduling policy
    maxPriority = sched_get_priority_max(SCHED_RR);
    if (maxPriority == -1)
    {
        perror("Error while finding max priority");
        return 1; // Return a non-zero value to indicate an error
    }
    else
    {
        printf("The max priority with RR Scheduling Policy is : %d\n", maxPriority);
    }

    // Get minimum priority for the SCHED_RR (Round Robin) scheduling policy
    minPriority = sched_get_priority_min(SCHED_RR);
    if (minPriority == -1)
    {
        perror("Error while finding min priority");
        return 1; // Return a non-zero value to indicate an error
    }
    else
    {
        printf("The min priority with RR Scheduling Policy is : %d\n", minPriority);
    }

    return 0; // Return 0 to indicate success
}
//output
/*The max priority with RR Scheduling Policy is : 99
The min priority with RR Scheduling Policy is : 1
*/