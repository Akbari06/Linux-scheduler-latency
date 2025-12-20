#ifndef THREAD_H
#define THREAD_H

#include <stddef.h>

typedef struct {
    int thread_id;
    int busy_wait;
    int pin_single_cpu;
    long *samples;
    size_t num_samples;
} thread_arg_t;

void *worker(void *arg);

#endif

