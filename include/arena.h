#ifndef _ARENA_H
#define _ARENA_H
#include <stdio.h>
#include <unistd.h>
#include "allocator.h"
void * arena_base;

struct arena_h {
  char magic_h;
  void * head;
  size_t size;
};
struct arena_f {
  unsigned next;
  char magic_f;
};

void * init_arena(size_t);
void * _arena_has_next(struct arena_h*);
void * _arena_free_block(size_t, struct arena_h *);
void arena_dump(struct arena_h *);

#endif