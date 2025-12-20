#ifndef SCHEDLAT_H
#define SCHEDLAT_H

#include <stddef.h>

typedef struct {
    size_t samples;
    int threads;
    int busy_wait;
    int pin_single_cpu;
} schedlat_config_t;

typedef struct {
    long **latencies;
    size_t samples;
    int threads;
} schedlat_result_t;

int schedlat_run(const schedlat_config_t *cfg, schedlat_result_t *out);
void schedlat_free(schedlat_result_t *out);

#endif
