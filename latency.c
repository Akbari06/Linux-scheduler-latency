#include <stdio.h>
#include <time.h>

int main(void) {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    printf("Seconds: %ld, Nanoseconds: %ld\n", ts.tv_sec, ts.tv_nsec);

    return 0;
}

long diff_nanoseconds(struct timespec start, struct timespec end) {
    long seconds_diff = end.tv_sec - start.tv_sec;
    long nanoseconds_diff = end.tv_nsec - start.tv_nsec;

    return seconds_diff * 1000000000L + nanoseconds_diff;
}