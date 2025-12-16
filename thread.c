#define _POSIX_C_SOURCE 200809L
#include "thread.h"
#include <time.h>

long now_ns(void);

void *worker(void *arg) {
    thread_arg_t *t = arg;
    struct timespec req = {0, 1000000};

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
