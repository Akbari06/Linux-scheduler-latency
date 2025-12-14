#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000;

// function declaration
long diff_nanoseconds(struct timespec start, struct timespec end);

int main(void) {
    
    long samples[N];

    struct timespec start, end;
    struct timespec req = {0, 1000000}; // 1 ms

    for (int i = 0; i < 10000; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        nanosleep(&req, NULL);
        clock_gettime(CLOCK_MONOTONIC, &end);

        long elapsed_ns = diff_nanoseconds(start, end);
        samples[i] = elapsed_ns - 1000000; // jitter
    }

    qsort(samples,N, sizeof(long), cpm_long);

    long p50 = samples[(int)(N * 0.5)];
    long p90 = samples[(int)(N * 90)];
    long p99 = samples[(int)(N * 0.99)];

    printf("p50: %ld ns\n", p50);
    printf("p90: %ld ns\n", p90);
    printf("p99: %ld ns\n", p99);
    
    return 0;
}

int cpm_long(const void *a, const void *b) {
    long la = *(const long *)a;
    long lb = *(const long *)b;
    return (la > lb) - (la < lb);
}

long diff_nanoseconds(struct timespec start, struct timespec end) {
    long seconds_diff = end.tv_sec - start.tv_sec;
    long nanoseconds_diff = end.tv_nsec - start.tv_nsec;

    return seconds_diff * 1000000000L + nanoseconds_diff;
}
