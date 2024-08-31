// Vikash Kumar Jaiswal
// MT2024168

// Question: Create a FIFO file using the `mkfifo` function or `mknod` system call

#include <sys/types.h> // Required for `mkfifo` and `mknod`
#include <sys/stat.h>  // Required for `mkfifo` and `mknod`
#include <fcntl.h>     // Required for `mknod`
#include <unistd.h>    // Required for `mknod`
#include <stdio.h>     // Required for `printf` & `perror`

int main()
{
    char *mkfifoName = "./mymkfifo";    // FIFO file created using `mkfifo`
    char *mknodName = "./mymknod-fifo"; // FIFO file created using `mknod`

    int mkfifo_status, mknod_status; // 0 -> Success, -1 -> Error

    // Create FIFO using `mkfifo`
    mkfifo_status = mkfifo(mkfifoName, S_IRWXU);
    if (mkfifo_status == -1)
    {
        perror("Error creating FIFO file with mkfifo");
    }
    else
    {
        printf("FIFO file created successfully with mkfifo. Check using `ls -l`.\n");
    }

    // Create FIFO using `mknod`
    mknod_status = mknod(mknodName, S_IFIFO | S_IRWXU, 0);
    if (mknod_status == -1)
    {
        perror("Error creating FIFO file with mknod");
    }
    else
    {
        printf("FIFO file created successfully with mknod. Check using `ls -l`.\n");
    }

    return 0;
}
//OUTPUT
//FIFO file created successfully with mkfifo. Check using `ls -l`.
