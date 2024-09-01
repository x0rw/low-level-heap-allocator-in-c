#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <unistd.h>
#include "include/arena.h"
struct alloc_block{
  size_t size;
  unsigned reserved;//if empty 0
  struct alloc_block * next;
};
void * allocate(size_t);
#endif