#include <stdio.h>
#include <time.h>

int main(void) {
    struct timespec start, end;
    struct timespec req = {0, 1000000}; // 1 ms

    for (int i = 0; i < 10000; i++); {

        clock_gettime(CLOCK_MONOTONIC, &start);
        nanosleep(&req, NULL);
        clock_gettime(CLOCK_MONOTONIC, &end);

        long elapsed_ns = diff_nanoseconds(start, end);
        printf("%ld\n", elapsed_ns - 1000000); // Print the difference from requested time
    }// Warm-up loop
    

    long elapsed_ns = diff_nanoseconds(start, end);

    printf("Requested: 1000000 ns\n");
    printf("Actual:    %ld ns\n", elapsed_ns);

    return 0;
}

long diff_nanoseconds(struct timespec start, struct timespec end) {
    long seconds_diff = end.tv_sec - start.tv_sec;
    long nanoseconds_diff = end.tv_nsec - start.tv_nsec;

    return seconds_diff * 1000000000L + nanoseconds_diff;
}