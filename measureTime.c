#include <time.h>
#include <unistd.h>

unsigned long getTick() {
    return sysconf(_SC_CLK_TCK);
}

// returns us
unsigned long getTimestamp() 
{
    struct timespec ts;
    unsigned theTick = 0U;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    
    // time_t tv_sec : the number of seconds since 1970.
    // time_t tv_nsec : The number of nanoseconds expired in the current second. This value increases by some multiple of nanoseconds, based on the system clock's resolution. 
    theTick  = ts.tv_nsec / 1000;
    theTick += ts.tv_sec * 1000000;
    
    return theTick;
}

