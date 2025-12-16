#include <stdlib.h>
#include "mem.h"
#include <stdio.h>

long *alloc_samples(size_t n) {
    long *samples = malloc(sizeof(long) * n);
    if (samples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return samples;
}

void free_samples(long *samples){
    free(samples);
}