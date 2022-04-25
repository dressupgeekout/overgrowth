#include <Compat/time.h>

#include <sys/time.h>
#include <stdlib.h>

uint64_t GetPrecisionTime() {
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return time.tv_usec +
            (time.tv_sec * 1000 * 1000);
}

uint64_t ToNanoseconds(uint64_t time){
    return time * 1000;
}
