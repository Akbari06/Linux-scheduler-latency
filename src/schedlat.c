#include <pthread.h>
#include <stdlib.h>

#include "mem.h"
#include "schedlat.h"
#include "thread.h"

static int validate_config(const schedlat_config_t *cfg) {
    if (cfg == NULL) {
        return -1;
    }
    if (cfg->samples == 0) {
        return -1;
    }
    if (cfg->threads <= 0) {
        return -1;
    }
    return 0;
}

int schedlat_run(const schedlat_config_t *cfg, schedlat_result_t *out) {
    if (out == NULL) {
        return -1;
    }

    out->latencies = NULL;
    out->samples = 0;
    out->threads = 0;

    if (validate_config(cfg) != 0) {
        return -1;
    }

    long **latencies = calloc((size_t)cfg->threads, sizeof(long *));
    pthread_t *threads = calloc((size_t)cfg->threads, sizeof(pthread_t));
    thread_arg_t *args = calloc((size_t)cfg->threads, sizeof(thread_arg_t));
    if (latencies == NULL || threads == NULL || args == NULL) {
        free(latencies);
        free(threads);
        free(args);
        return -1;
    }

    size_t started = 0;
    int joined_in_loop = 0;
    int status = 0;
    for (int i = 0; i < cfg->threads; i++) {
        latencies[i] = alloc_samples(cfg->samples);
        if (latencies[i] == NULL) {
            status = -1;
            goto cleanup;
        }

        args[i].thread_id = i;
        args[i].busy_wait = cfg->busy_wait;
        args[i].pin_single_cpu = cfg->pin_single_cpu;
        args[i].samples = latencies[i];
        args[i].num_samples = cfg->samples;

        if (pthread_create(&threads[i], NULL, worker, &args[i]) != 0) {
            status = -1;
            goto cleanup;
        }
        started++;
    }

    for (size_t i = 0; i < started; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            status = -1;
        }
    }
    joined_in_loop = 1;

cleanup:
    if (status != 0) {
        if (!joined_in_loop) {
            for (size_t i = 0; i < started; i++) {
                pthread_join(threads[i], NULL);
            }
        }
        if (latencies != NULL) {
            for (int i = 0; i < cfg->threads; i++) {
                free_samples(latencies[i]);
            }
        }
        free(latencies);
        out->latencies = NULL;
        out->samples = 0;
        out->threads = 0;
    } else {
        out->latencies = latencies;
        out->samples = cfg->samples;
        out->threads = cfg->threads;
    }

    free(threads);
    free(args);
    return status;
}

void schedlat_free(schedlat_result_t *out) {
    if (out == NULL || out->latencies == NULL) {
        return;
    }

    for (int i = 0; i < out->threads; i++) {
        free_samples(out->latencies[i]);
    }

    free(out->latencies);
    out->latencies = NULL;
    out->samples = 0;
    out->threads = 0;
}
