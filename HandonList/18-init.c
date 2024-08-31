#include <sys/types.h> // For `open`, `lseek`
#include <sys/stat.h>  // For `open`
#include <fcntl.h>     // For `fcntl`, `open`
#include <unistd.h>    // For `write`, `lseek`, `fcntl`
#include <stdio.h>     // For `perror`, `printf`
#include <stdlib.h>    // For `exit`

#define FILENAME "record-file.dat" // File name where records are stored

// Define the record structure
struct record {
    int recordNumber;
    int someNumber;
};

// Function to lock a record
void lock_record(int fileDescriptor, off_t offset, int length, short lockType) {
    struct flock lock;
    lock.l_type = lockType;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = length;
    lock.l_pid = getpid();

    if (fcntl(fileDescriptor, F_SETLKW, &lock) == -1) {
        perror("Error while locking record");
        close(fileDescriptor);
        exit(EXIT_FAILURE); // Exit if locking fails
    }
}

// Function to unlock a record
void unlock_record(int fileDescriptor, off_t offset, int length) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = length;
    lock.l_pid = getpid();

    if (fcntl(fileDescriptor, F_SETLKW, &lock) == -1) {
        perror("Error while unlocking record");
        close(fileDescriptor);
        exit(EXIT_FAILURE); // Exit if unlocking fails
    }
}

// Function to initialize records
void initialize_records(int fileDescriptor) {
    struct record records[3] = {
        {1, 0},
        {2, 0},
        {3, 0}
    };

    if (write(fileDescriptor, records, sizeof(records)) == -1) {
        perror("Error while initializing records");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
}

int main() {
    int fileDescriptor;
    struct record records[3];

    // Open the file (create if it doesn't exist)
    fileDescriptor = open(FILENAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fileDescriptor == -1) {
        perror("Error while opening the file");
        exit(EXIT_FAILURE);
    }

    // Initialize file with records if empty
    if (lseek(fileDescriptor, 0, SEEK_END) == 0) {
        lseek(fileDescriptor, 0, SEEK_SET);
        initialize_records(fileDescriptor);
    }

    // Lock and modify records
    for (int i = 0; i < 3; i++) {
        off_t offset = i * sizeof(struct record);
        lock_record(fileDescriptor, offset, sizeof(struct record), F_WRLCK);

        lseek(fileDescriptor, offset, SEEK_SET);
        if (read(fileDescriptor, &records[i], sizeof(struct record)) == -1) {
            perror("Error while reading record");
            unlock_record(fileDescriptor, offset, sizeof(struct record));
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }

        records[i].someNumber += 1; // Modify the record

        lseek(fileDescriptor, offset, SEEK_SET);
        if (write(fileDescriptor, &records[i], sizeof(struct record)) == -1) {
            perror("Error while writing record");
            unlock_record(fileDescriptor, offset, sizeof(struct record));
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }

        unlock_record(fileDescriptor, offset, sizeof(struct record));
    }

    close(fileDescriptor);
    return EXIT_SUCCESS;
}
//output
/*If everything works correctly, there will be no output other than the modifications to record-file.dat. If an error occurs, the error message will be printed, and the program will exit with an error code.

Here is a concise view of the locking operations:

Lock the record: Ensures exclusive access to the record.
Read and Modify: Safely read and update the record.
Unlock the record: Release the lock for other processes.
The program is a good demonstration of file handling and synchronization using file locks in Unix-like systems.*/