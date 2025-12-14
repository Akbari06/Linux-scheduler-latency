#include <stdio.h>
#include <time.h>

int main(void) {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    printf("Seconds: %ld, Nanoseconds: %ld\n", ts.tv_sec, ts.tv_nsec);

    return 0;
}
