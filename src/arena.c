#include "../include/arena.h"
void * init_arena(size_t size)
{
  void * heap_base = sbrk(size+ sizeof(struct arena_h)+sizeof(struct arena_f));
  arena_base = heap_base;
  struct arena_h * ah = heap_base;
  ah->size = size;
  ah->magic_h= 0xff;
  struct arena_f * af = heap_base + size;
  af->magic_f = 0xff;
  af->next= 0;
}

void * _arena_has_next(struct arena_h* ah){
   struct arena_f * af = (void *)ah + ah->size;
   return af->next ? (af + sizeof(struct arena_f)) : 0;
}

void * _arena_free_block(size_t size, struct arena_h * ah){
  void * arena = ah; 
  void * arena_head = ah->head; 
  struct alloc_block * current_block = arena_head; 
  if(!ah->head){

    struct alloc_block * ab = ((void *)ah + sizeof(struct arena_h));
    ah->head = (void *)ab;

    ab->size = 111;
    return ab;
  }

  struct alloc_block * tmp_b= arena_head;

  while(current_block){ 
    /* First Fit algo*/
    if(!current_block->reserved && current_block->size>= size){
      tmp_b->next = current_block;        
       return (void * )current_block; 
    }
    tmp_b = current_block;
    current_block = current_block->next;
  }
  /* the size of the remaining arena after traversing the allocated blocks*/
  // there will be issues when we move between arenas
  current_block = (void *)tmp_b + tmp_b->size + sizeof(struct alloc_block); 
  int rem_size = ah->size - ((void *)current_block - arena_head);
  printf("\n size : %d\t rem_size: %d \n", size, rem_size); 
  if(size <= rem_size ){
    tmp_b->next = current_block;   
    return (void *)current_block;
  }
  struct arena_h * arena_next= _arena_has_next(arena);
  if(arena_next)  
    return _arena_free_block(size, arena_next);

  return NULL;
}

void arena_dump(struct arena_h * ah){
  struct alloc_block * current_block = ah->head;
  while(current_block){ 
    printf("\n size = %d \t reserved: %d", current_block->size,current_block->reserved);
    current_block = current_block->next;
  }


}
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