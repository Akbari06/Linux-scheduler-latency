#include <stdlib.h>
#include "mem.h"

long *alloc_samples(size_t n) {
    return malloc(sizeof(long) * n);
}

void free_samples(long *samples){
    free(samples);
}
