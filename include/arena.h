#ifndef _ARENA_H
#define _ARENA_H

/*
 *
 *                       ARENA
 *  arena contains the head (struct header) of the first 
 *  allocation 
 *  
 *  every alloc is a struct in arena with header 
 *  
 * 
 *  the alloc header contains the size and the resered flag
 *  when we allocate we check each block until we find a free one
 *  we set it as reserved
 *  after each free we merge the free blocks together


----------HEADER----------
 *
 * 
 *       struct arena_h {
 *       char magic_h;
 *       void * head;
 *       size_t size;
 *       };
 * 
 * 
 *---------FOOTER------------
 * 
 *       struct arena_f {
 *       unsigned next;
 *       char magic_f;
 *       };
 *
 *
 *
 * 'magic_f' 1 byte to detect memory corruption
*/


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