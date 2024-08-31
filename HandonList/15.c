// Vikash Kumar Jaiswal
// MT2024168
// Question: Write a program to display the environmental variable of the user (use environ).

#include <stdio.h>   // For printf
#include <string.h>  // For strncmp

extern char **environ;

int isUser(const char *var)
{
    // Check if the variable starts with "USER="
    return strncmp(var, "USER=", 5) == 0;
}

int main()
{
    int iter = 0;

    while (environ[iter] != NULL)
    {
        if (isUser(environ[iter]))
        {
            printf("%s\n", environ[iter]);
        }
        iter++;
    }

    return 0;
}
//output
//USER=your_username
