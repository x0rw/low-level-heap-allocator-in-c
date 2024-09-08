  #include <stdio.h>
#include <unistd.h>
#include "include/allocator.h"
#include "include/memory_worker.h"


int main(){
//  init_worker();

  void * ad = init_arena(500);
  
  void * alloc_1 = allocate(1);
  void * alloc_51 = allocate(6000);
  void * alloc_511 = allocate(13000);
  void * alloc_1511 = allocate(130000);
  void * alloc_15411 = allocate(130000);
//  free_alloc(alloc_3);
//  free_alloc(alloc_4);
//  void * afbadsq = allocate(100);
  printf("\n----------------------\n");
  arenas_dump();

  //merge_alloc_blocks(arena_base);

  // int *i1, *i2;
  // char * mem = alloc(8);
  // char * memd = alloc(64);
  // mem[0] = "a";
  // mem[1] = "b";
  // mem[2] = "c";
  // mem[3] = "d";
  // heap_dump();
  // freem(mem); 
  // freem(memd); 
} 
