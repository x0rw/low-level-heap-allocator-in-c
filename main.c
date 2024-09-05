#include <stdio.h>
#include <unistd.h>
#include "include/allocator.h"
#include "include/memory_worker.h"


int main(){
  void * ad = init_arena(500);

  void * afbaaaa = allocate(4);
  void * afba = allocate(1);
  void * afbaw = allocate(2);
  void * afbad = allocate(1);
  void * afbads = allocate(100);
  free_alloc(afbads);
  init_worker();
  void * afbadsq = allocate(100);
  void * afbadswq = allocate(100);

  //printf("%p\n",afbaw);
  arena_dump(arena_base);
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
