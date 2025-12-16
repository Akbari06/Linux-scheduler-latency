#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#include "mem.h"
#include "thread.h"

#define N 10000
#define THREADS 4

int cmp_long(const void *a, const void *b);
long now_ns(void);

int main(void) {
    pthread_t threads[THREADS];
    thread_arg_t args[THREADS];

    int busy_wait = 1;

    for (int i = 0; i < THREADS; i++) {
        args[i].thread_id = i;
        args[i].busy_wait = busy_wait;
        args[i].num_samples = N;
        args[i].samples = alloc_samples(N);

        pthread_create(&threads[i], NULL, worker, &args[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    FILE *f = fopen("thread_jitter.csv", "w");
    fprintf(f, "thread,jitter_ns\n");

    for (int t = 0; t < THREADS; t++) {
        qsort(args[t].samples, N, sizeof(long), cmp_long);
        for (int i = 0; i < N; i++) {
            fprintf(f, "%d,%ld\n", t, args[t].samples[i]);
        }
        free_samples(args[t].samples);
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
