// Vikash Kumar Jaiswal
// MT2024168
// Question: Write a program to print various information about a given file.

#include <sys/types.h>  // Required for using `stat` system call
#include <sys/stat.h>   // Required for using `stat` system call
#include <unistd.h>     // Required for using `stat` system call
#include <stdio.h>      // Required for `printf` and `perror` functions
#include <time.h>       // Required for converting epoch timestamps to human-readable format

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    struct stat statbuf;

    // Get file status
    if (stat(filename, &statbuf) == -1)
    {
        perror("Error getting file status");
        return 1;
    }

    // Print file information
    printf("Inode -> %ld\n", (long)statbuf.st_ino);
    printf("Number of hard links -> %ld\n", (long)statbuf.st_nlink);
    printf("UID -> %u\n", statbuf.st_uid);
    printf("GID -> %u\n", statbuf.st_gid);
    printf("Size -> %ld bytes\n", (long)statbuf.st_size);
    printf("Block Size -> %ld bytes\n", (long)statbuf.st_blksize);
    printf("Number of Blocks -> %ld\n", (long)statbuf.st_blocks);
    printf("Time of last access -> %s", ctime(&statbuf.st_atime));
    printf("Time of last modification -> %s", ctime(&statbuf.st_mtime));
    printf("Time of last change -> %s", ctime(&statbuf.st_ctime));

    return 0;
}
//output
/*Inode -> [inode_number]
Number of hard links -> [number_of_hard_links]
UID -> [user_id]
GID -> [group_id]
Size -> [file_size] bytes
Block Size -> [block_size] bytes
Number of Blocks -> [number_of_blocks]
Time of last access -> [last_access_time]
Time of last modification -> [last_modification_time]
Time of last change -> [last_change_time]
*/