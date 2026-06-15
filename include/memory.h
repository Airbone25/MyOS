#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MAX_MEMORY_REGIONS 32

typedef struct
{
    uint64_t base;
    uint64_t length;
    uint32_t type;
} memory_region_t;

extern memory_region_t memory_map[MAX_MEMORY_REGIONS];
extern int memory_region_count;

#endif