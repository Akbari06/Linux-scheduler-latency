#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define N 10000

// function declaration
long diff_nanoseconds(struct timespec start, struct timespec end);
int cmp_long(const void *a, const void *b);
long now_ns(void);

int main(void) {
    
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    sched_setaffinity(0, sizeof(set), &set);
    long samples[N];

    struct timespec start, end;
    struct timespec req = {0, 1000000}; // 1 ms

    for (int i = 0; i < 10000; i++) {

        long start_ns = now_ns();

        while (now_ns() - start_ns < 1000000){
            // busy wait for 1ms
        }

        long end_ns = now_ns();

        samples[i] = end_ns - start_ns - 1000000; // jitter

    }

    qsort(samples, N, sizeof(long), cmp_long);

    long p50 = samples[(int)(N * 0.5)];
    long p90 = samples[(int)(N * 0.90)];
    long p99 = samples[(int)(N * 0.99)];

    FILE *f = fopen("busy_wait.csv", "w");
    fprintf(f, "jitter_ns\n");

    for (int i = 0; i < N; i++) {
        fprintf(f, "%ld\n", samples[i]);
    }

fclose(f);


    return 0;
}

long now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000L + ts.tv_nsec;
}

int cmp_long(const void *a, const void *b) {
    long la = *(const long *)a;
    long lb = *(const long *)b;
    return (la > lb) - (la < lb);
}

long diff_nanoseconds(struct timespec start, struct timespec end) {
    long seconds_diff = end.tv_sec - start.tv_sec;
    long nanoseconds_diff = end.tv_nsec - start.tv_nsec;

    return seconds_diff * 1000000000L + nanoseconds_diff;
}
    