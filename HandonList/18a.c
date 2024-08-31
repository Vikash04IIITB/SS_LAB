#include <sys/types.h> // For `open`, `lseek`
#include <sys/stat.h>  // For `open`
#include <fcntl.h>     // For `fcntl`, `open`
#include <unistd.h>    // For `lseek`, `fcntl`, `read`, `write`
#include <stdio.h>     // For `perror`, `printf`
#include <stdlib.h>    // For `exit`

#include "./18-record.h" // Ensure this header contains `struct record` and `filename`

void main(int argc, char *argv[]) {
    int fileDescriptor, fcntlStatus, recordNumber;
    ssize_t readBytes, writeBytes;
    off_t lseekOffset;
    struct flock lock;
    struct record record;

    if (argc != 2) {
        printf("Usage: %s <record_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Convert the record number from string to integer
    recordNumber = atoi(argv[1]);

    if (recordNumber < 1 || recordNumber > 3) {
        printf("Record number must be between 1 and 3.\n");
        exit(EXIT_FAILURE);
    }

    fileDescriptor = open(filename, O_RDWR);
    if (fileDescriptor == -1) {
        perror("Error while opening the file");
        exit(EXIT_FAILURE);
    }

    // Setup the lock structure for write lock
    lock.l_type = F_WRLCK;
    lock.l_start = sizeof(struct record) * (recordNumber - 1);
    lock.l_len = sizeof(struct record);
    lock.l_whence = SEEK_SET;
    lock.l_pid = getpid();

    fcntlStatus = fcntl(fileDescriptor, F_GETLK, &lock);
    if (fcntlStatus == -1) {
        perror("Error while checking lock status");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }

    if (lock.l_type == F_WRLCK) {
        printf("Record %d already has a write lock!\n", recordNumber);
    } else if (lock.l_type == F_RDLCK) {
        printf("Record %d already has a read lock!\n", recordNumber);
    } else {
        lock.l_type = F_WRLCK;
        fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &lock);
        if (fcntlStatus == -1) {
            perror("Error while getting write lock on the record");
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }

        lseekOffset = lseek(fileDescriptor, lock.l_start, SEEK_SET);
        if (lseekOffset == -1) {
            perror("Error while seeking");
            fcntl(fileDescriptor, F_UNLCK, &lock); // Ensure we unlock before exit
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }

        readBytes = read(fileDescriptor, &record, sizeof(record));
        if (readBytes == -1) {
            perror("Error while reading record");
            fcntl(fileDescriptor, F_UNLCK, &lock); // Ensure we unlock before exit
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }

        printf("Record %d has the value %d\n", record.recordNumber, record.someNumber);
        record.someNumber += 1;

        lseekOffset = lseek(fileDescriptor, lock.l_start, SEEK_SET);
        if (lseekOffset == -1) {
            perror("Error while seeking");
            fcntl(fileDescriptor, F_UNLCK, &lock); // Ensure we unlock before exit
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }

        writeBytes = write(fileDescriptor, &record, sizeof(struct record));
        if (writeBytes == -1) {
            perror("Error while writing record");
            fcntl(fileDescriptor, F_UNLCK, &lock); // Ensure we unlock before exit
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }

        printf("Record %d now has the value %d\n", record.recordNumber, record.someNumber);

        // Unlock the record
        lock.l_type = F_UNLCK;
        fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &lock);
        if (fcntlStatus == -1) {
            perror("Error while unlocking");
        }

        close(fileDescriptor);
    }
}
//output
//./record_manager <record_number>

