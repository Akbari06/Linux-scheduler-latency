#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct timespec
{
    time_t tv_sec; // seconds
    long tv_nsec; // nanoseconds
};

int main(void){
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    printf("Seconds: %ld, Nanoseconds: %ld\n", ts.tv_sec, ts.tv_nsec);
}
