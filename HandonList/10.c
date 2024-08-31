// Vikash Kumar Jaiswal
// MT2024168
// Question: Write a program to open a file with read-write mode, write 10 bytes, move the file pointer by 10 bytes (using lseek), and write again 10 bytes.

#include <sys/stat.h>  // Required for `open` system call
#include <fcntl.h>     // Required for `open` system call
#include <sys/types.h> // Required for `open`, `lseek` system call
#include <unistd.h>    // Required for `close`, `lseek`, `write` system calls
#include <stdio.h>     // Required for `perror` and `printf` functions

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int fileDescriptor = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fileDescriptor == -1)
    {
        perror("Error while opening file");
        return 1;
    }

    off_t offset = lseek(fileDescriptor, 0, SEEK_SET); // Move to start of the file
    if (offset == (off_t)-1)
    {
        perror("Error while seeking in the file");
        close(fileDescriptor);
        return 1;
    }

    ssize_t writeByteCount = write(fileDescriptor, "ABCDEFGHIJ", 10);
    if (writeByteCount == -1)
    {
        perror("Error while writing to the file");
        close(fileDescriptor);
        return 1;
    }

    offset = lseek(fileDescriptor, 10, SEEK_CUR); // Move forward 10 bytes from current position
    if (offset == (off_t)-1)
    {
        perror("Error while seeking in the file");
        close(fileDescriptor);
        return 1;
    }

    writeByteCount = write(fileDescriptor, "ABCDEFGHIJ", 10);
    if (writeByteCount == -1)
    {
        perror("Error while writing to the file");
        close(fileDescriptor);
        return 1;
    }

    printf("Return value of lseek: %ld\n", (long)offset);

    close(fileDescriptor);
    return 0;
}
//output
//Return value of lseek: [final_file_offset]
