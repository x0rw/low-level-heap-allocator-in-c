#ifndef MEMORY_WORKER_H
#define MEMORY_WORKER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "arena.h"
void * _run_order(void *);
void init_worker();
#endif