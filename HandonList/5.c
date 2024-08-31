// Vikash Kumar Jaiswal
// MT2024168

// Question: Write a program to create five new files in an infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.

#include <sys/types.h> // Required for `creat` system call
#include <sys/stat.h>  // Required for `creat` system call
#include <fcntl.h>     // Required for `creat` system call
#include <unistd.h>    // Required for `sleep` function

int main()
{
    while (1)
    {
        // Create five new files in the "sample-files" directory
        creat("./sample-files/file_1", S_IRWXU);
        creat("./sample-files/file_2", S_IRWXU);
        creat("./sample-files/file_3", S_IRWXU);
        creat("./sample-files/file_4", S_IRWXU);
        creat("./sample-files/file_5", S_IRWXU);

        // Sleep to prevent overwhelming the system
        sleep(1);
    }

    return 0;
}
//OUTPUT
//The output will be a continuous creation of files every second in the ./sample-files directory, with the file descriptor table growing rapidly.