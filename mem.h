#ifndef MEM_H
#define MEM_H

#include <stddef.h>

long *alloc_samples(size_t n);
void free_samples(long *samples);

#endif
