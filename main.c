  #include <stdio.h>
#include <unistd.h>
#include "include/allocator.h"
#include "include/memory_worker.h"


int main(){
//  init_worker();

  void * ad = init_arena(1000);
  
  void * alloc_1 = allocate(1);
  void * alloc_2 = allocate(16);
  char c = 'c';
  //memset(alloc_2, c, 16);

    void * alloc_3 = allocate(16);
 // memset(alloc_3, c, 16);

    void * alloc_4 = allocate(64);
  //memset(alloc_4, c, 64);
    void * alloc_5 = allocate(64);
    void * alloc_56 = allocate(6);
   
    void * alloc_6 = allocate(640);
    void * alloc_7 = allocate(100);
    free_alloc(alloc_3);   
    void * alloc_8 = allocate(10);
    void * alloc_10 = allocate(120);
    void * alloc_9 = allocate(11);
    void * alloc_90 = allocate(11);
    void * alloc_91 = allocate(1);
    void * alloc_92 = allocate(1);

    free_alloc(alloc_10);   


//  void * alloc_511 = allocate(13000);
//  void * alloc_1511 = allocate(130000);
//  void * alloc_15411 = allocate(130000);
//  free_alloc(alloc_3);
//  free_alloc(alloc_4);
//  void * afbadsq = allocate(100);
  printf("\n----------------------\n");
  arenas_dump();
  arena_dump(_next_arena(arena_base));

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
