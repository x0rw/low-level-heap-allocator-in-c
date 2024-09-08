#ifndef MEMORY_WORKER_H
#define MEMORY_WORKER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "arena.h"
#ifndef ALLOC_FREQ_SEC
#define ALLOC_FREQ_SEC 1
#endif

void * _run_order(void *);
void init_worker();
void merge_alloc_blocks(struct arena_h * );
#endif