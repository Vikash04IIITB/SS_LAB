#include <sys/time.h>  // Import for `gettimeofday`
#include <sys/types.h> // Import for `getpid`
#include <unistd.h>    // Import for `getpid`
#include <stdio.h>     // Import for `printf`

#ifdef _MSC_VER
#include <intrin.h>   // Import for __rdtsc() on MSVC
#else
#include <x86intrin.h> // Import for __rdtsc() on GCC/Clang
#endif

int main()
{
    unsigned long long start, end;
    pid_t pid;

    // Get the timestamp before the system call
    start = __rdtsc();

    // System call to get the process ID
    pid = getpid();

    // Get the timestamp after the system call
    end = __rdtsc();

    // Output the results
    printf("PID: %d\n", pid);
    printf("Time taken: %llu CPU cycles\n", end - start);

    return 0;
}
//output
//PID: 1234
//Time taken: 123456 CPU cycles
