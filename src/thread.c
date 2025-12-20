#define _GNU_SOURCE
#include <pthread.h>
#include <time.h>

#ifdef __linux__
#include <sched.h>
#define HAS_CPU_AFFINITY 1
#else
#define HAS_CPU_AFFINITY 0
#endif

#include "schedlat_time.h"
#include "thread.h"

void *worker(void *arg) {
    thread_arg_t *t = arg;
    struct timespec req = {0, 1000000};

#if HAS_CPU_AFFINITY
    if (t->pin_single_cpu) {
        cpu_set_t cpus;
        CPU_ZERO(&cpus);
        CPU_SET(0, &cpus);
        pthread_setaffinity_np(pthread_self(), sizeof(cpus), &cpus);
    }
#else
    (void)t->pin_single_cpu;
#endif

    for (size_t i = 0; i < t->num_samples; i++) {
        long start_ns = now_ns();

        if (t->busy_wait) {
            while (now_ns() - start_ns < 1000000) {
            }
        } else {
            nanosleep(&req, NULL);
        }

        long end_ns = now_ns();
        t->samples[i] = end_ns - start_ns - 1000000;
    }
    return NULL;
}
