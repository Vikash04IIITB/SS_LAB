#include <unistd.h>    // Import for `fork`
#include <sys/types.h> // Import for `fork`, `waitpid`
#include <sys/wait.h>  // Import for `waitpid`
#include <stdio.h>     // Import for `printf`

int main()
{
    pid_t childA, childB, childC, terminatedChild;
    int waitStatus;

    // Create Child A
    if ((childA = fork()) == 0)
    {
        // Child A
        printf("Child A created...\n");
        printf("Putting child A to sleep for 5 seconds\n");
        sleep(5);
        printf("Child A is now awake!\n");
        _exit(0);
    }
    else if (childA > 0)
    {
        // Create Child B
        if ((childB = fork()) == 0)
        {
            // Child B
            printf("Child B created...\n");
            printf("Putting child B to sleep for 10 seconds\n");
            sleep(10);
            printf("Child B is now awake!\n");
            _exit(0);
        }
        else if (childB > 0)
        {
            // Create Child C
            if ((childC = fork()) == 0)
            {
                // Child C
                printf("Child C created...\n");
                printf("Putting child C to sleep for 15 seconds\n");
                sleep(15);
                printf("Child C is now awake!\n");
                _exit(0);
            }
            else if (childC > 0)
            {
                // Parent process
                terminatedChild = waitpid(childC, &waitStatus, 0); // Wait for Child C

                if (terminatedChild == childC)
                {
                    if (WIFEXITED(waitStatus))
                    {
                        printf("Child C has terminated with exit status = %d\n", WEXITSTATUS(waitStatus));
                    }
                    else
                    {
                        printf("Child C did not terminate normally\n");
                    }
                }
                else
                {
                    perror("Error in waitpid");
                }
            }
            else
            {
                perror("Fork failed for Child C");
            }
        }
        else
        {
            perror("Fork failed for Child B");
        }
    }
    else
    {
        perror("Fork failed for Child A");
    }

    return 0;
}
// OUTPUT
/*Child A created...
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