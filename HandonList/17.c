// Vikash Kumar Jaiswal
// MT2024168
// Ticket Reservation Writer Program

#include <sys/types.h> // For `open`, `lseek`
#include <sys/stat.h>  // For `open`
#include <fcntl.h>     // For `fcntl`, `open`
#include <unistd.h>    // For `write`, `lseek`, `fcntl`
#include <stdio.h>     // For `perror`, `printf`

void main()
{
    char *ticketFile = "./sample-files/ticket-file.txt"; // Name of the file used for storing the ticket number

    int fileDescriptor, fcntlStatus;
    ssize_t readBytes, writeBytes;
    off_t lseekOffset;
    int buffer;
    struct flock ticketLock;

    fileDescriptor = open(ticketFile, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fileDescriptor == -1)
    {
        perror("Error while opening the file");
        return;
    }

    // Define lock parameters
    ticketLock.l_type = F_WRLCK;    // Write lock
    ticketLock.l_whence = SEEK_SET; // Seek from start of the file
    ticketLock.l_start = 0;         // Start of the file
    ticketLock.l_len = 0;           // Lock the entire file
    ticketLock.l_pid = getpid();

    // Check if the file is already locked
    fcntlStatus = fcntl(fileDescriptor, F_GETLK, &ticketLock);
    if (fcntlStatus == -1)
    {
        perror("Error while getting lock status");
        close(fileDescriptor);
        return;
    }

    if (ticketLock.l_type == F_WRLCK)
    {
        printf("The ticket file %s is already locked for writing!\n", ticketFile);
    }
    else if (ticketLock.l_type == F_RDLCK)
    {
        printf("The ticket file %s is already locked for reading!\n", ticketFile);
    }
    else
    {
        // Apply write lock
        ticketLock.l_type = F_WRLCK;
        fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &ticketLock);
        if (fcntlStatus == -1)
        {
            perror("Error while locking the ticket file");
            close(fileDescriptor);
            return;
        }

        // Read the current ticket number
        readBytes = read(fileDescriptor, &buffer, sizeof(int));
        if (readBytes == -1)
        {
            perror("Error while reading ticket");
            fcntlStatus = fcntl(fileDescriptor, F_UNLCK, &ticketLock);
            close(fileDescriptor);
            return;
        }

        // If no ticket number exists, start with 1
        if (readBytes == 0)
        {
            buffer = 1;
        }
        else
        {
            // Increment the ticket number
            buffer++;
            lseekOffset = lseek(fileDescriptor, 0, SEEK_SET);
            if (lseekOffset == -1)
            {
                perror("Error while seeking");
                fcntlStatus = fcntl(fileDescriptor, F_UNLCK, &ticketLock);
                close(fileDescriptor);
                return;
            }
        }

        // Write the new ticket number
        writeBytes = write(fileDescriptor, &buffer, sizeof(int));
        if (writeBytes == -1)
        {
            perror("Error while writing to ticket file");
            fcntlStatus = fcntl(fileDescriptor, F_UNLCK, &ticketLock);
            close(fileDescriptor);
            return;
        }

        printf("Your ticket number is: %d\n", buffer);

        // Release the lock
        ticketLock.l_type = F_UNLCK;
        fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &ticketLock);
        if (fcntlStatus == -1)
        {
            perror("Error releasing lock");
        }
        else
        {
            printf("Lock released successfully\n");
        }
    }

    close(fileDescriptor);
}
//output
//Your ticket number is: [ticket_number]
//Lock released successfully
