#include "../include/arena.h"

/* extends the heap to create an arena using sbrk or mmap 
*  magic_h and magic_h are used by the worker(thread) later to check if there is any memory overflow 
*/
void * init_arena(size_t size)
{

  void * heap_base = sbrk(size+ sizeof(struct arena_h)+sizeof(struct arena_f));
  if(!arena_base)
    arena_base = heap_base;
  struct arena_h * ah = heap_base;
  ah->size = size;
  ah->head = NULL;
  ah->magic_h= 0xff;
  struct arena_f * af = heap_base +sizeof(struct arena_h)+ size;
  af->magic_f = 0xff;
  af->next= NULL;
  return ah;
}

/**
 * _next_arena checks the footer structure (struct arena_f) if there is a next arena 
 *  returns the address of the next arena otherwise NULL if there is no next
 *  
*/
void * _next_arena(struct arena_h * arena ){
  struct arena_f * arena_footer = (void *)arena + sizeof(struct arena_h)+ arena->size;
  if(arena_footer->next)
    return arena_footer->next;
  return NULL;
}

/*_extend_arena is used to create a new arena when needed with a spesific policy 
*
*
*/
void _extend_arena(size_t needed_size){
  struct arena_h * arena = arena_base;
  size_t new_arena_size;

  //last arena
  while( _next_arena(arena)) {
    arena = _next_arena(arena);
  }

  //extending policy (change to switch later)
  if(_ARENA_EXTND_MUL_PREV)
    new_arena_size = arena->size * _ARENA_EXTND_MUL_PREV;
  else if(_ARENA_EXTND_NEEDED_ONLY)
    new_arena_size = arena->size;
  else if(_ARENA_EXTND_ADD_FIXED)
    new_arena_size = _ARENA_EXTND_ADD_FIXED;
  
  if(new_arena_size < needed_size){
    new_arena_size = needed_size;
  }
  
  //construct the arena
  void * n_arena = init_arena(new_arena_size);
  struct arena_f * af = (void *)arena + sizeof(struct arena_h) + arena->size;  
  af->next = n_arena;
  return;
}
void * _arena_has_next(struct arena_h* ah){
   struct arena_f * af = (void *)ah + ah->size;
   return af->next ? (af + sizeof(struct arena_f)) : 0;
}

void * _arena_free_block(size_t size, struct arena_h * ah){
  void * arena = ah; 
  void * arena_head = ah->head; 
  struct alloc_block * current_block = arena_head; 
  if(arena_head == NULL){

    struct alloc_block * ab = ((void *)ah + sizeof(struct arena_h));
    ah->head = (void *)ab;

    ab->size = size;
    ab->next = NULL;
    return ab;
  }

  struct alloc_block * tmp_b= arena_head;

  while(current_block  != NULL ){ 
    /* First Fit algo*/
    //printf("\n res %d",current_block->reserved);
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
  int rem_size = ah->size - ((void *)current_block - arena_head) ;
  //printf("\n size : %d\t rem_size: %d \n", size, rem_size); 
  if(size + sizeof(struct alloc_block) <= rem_size ){
    tmp_b->next = current_block;
    current_block->size = size;
    current_block->next = NULL;
    return (void *)current_block;
  }

  struct arena_h * arena_next= _next_arena(arena);
  
  if(arena_next)  
    return _arena_free_block(size, arena_next);
  else {
    _extend_arena(size);
    return _arena_free_block(size,_next_arena(arena) );
  }
  return NULL;
}

/* dumps all the allocations in a spesific arena */
void arena_dump(struct arena_h * ah){
  struct alloc_block * current_block = ah->head;
  struct alloc_block * prev_dbg= ah->head;
  while(current_block){

    printf("\n size = %ld \t reserved: %d", current_block->size,current_block->reserved);
    prev_dbg = current_block;
    current_block = current_block->next;
  }


}

/* prints all the avaliable arenas */
void arenas_dump(){
  struct arena_h * arena = arena_base;
  int i= 0;
  //last arena
  while(arena) {
    printf("\nArena %d \t arena size: %ld \n", i++,arena->size  );
    arena = _next_arena(arena);
  }


}