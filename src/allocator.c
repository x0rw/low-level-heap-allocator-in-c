#include "../include/allocator.h"
void * allocate(size_t size){
  struct arena_h * head_arena = ((struct arena_h * )arena_base);
  struct alloc_block * ab = _arena_free_block(size, head_arena);
  if(!ab){
    printf("couldn't allocate memory for size: %d\n", size);
    exit(-1);
  }
  ab->reserved= 1;
  ab->size = size;
  return (void *) ab;
}
void free_alloc(void * block){
    struct alloc_block * al_block = block - sizeof(struct alloc_block);
    al_block->reserved = 0;
}