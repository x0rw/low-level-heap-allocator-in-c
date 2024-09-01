#include <stdio.h>
#include <unistd.h>
/*          ARENA
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
 *
*
 *
 *----------HEADER----------
 *
 * 
 *
 *
 * 
 *
 * ---------FOOTER----------| 1 byte to detect memory corruption
 * */
struct arena_h {
  char magic_h;
  void * head;
  size_t size;
};
struct arena_f {
  unsigned next;
  char magic_f;
};


struct alloc_header {
    size_t size;
    unsigned free;
    struct alloc_header *next;
};


struct alloc_block{
  size_t size;
  unsigned reserved;//if empty 0
  struct alloc_block * next;
};

void * arena_base;
typedef struct alloc_header header_t;
header_t *head, *tail;

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
void * alloc(size_t size)
{
  header_t * current= head;
  header_t * header= NULL;
  
  /*  ---------------------  */
  while(current){
   if(current->free && current->size>= size){
     header  = current;
      header->free = 0;
      return (void*)(header + 1); //return address after skipping the header and casting it to void *
   }
  current = current->next;
  }
  // if there is a free block 
  /*  ---------- MUTEX -----------  */
  //no free block avaliable
  size = size + sizeof(header_t);
  void * nblock;
  //sbrk allocate a block
  nblock =(void *)sbrk(size);

  if(nblock==(void *)-1)
    return NULL;
  printf("address:%ld\n",size);
  header = nblock;
  header->size =size;
  header->free=0;
  header->next = NULL;
  if(!head)
    head = header;
  if(tail)
    tail->next= header;
  tail = header;
  printf("succ");
  return (void *)(header + 1);

  
  
}
/* function that frees the heap
* could be given a non cast   
*
*/
void freem(void * address)
{
   header_t *header, *tmp;
   void * sbreak= sbrk(0);

   header = (header_t *) address - 1; //get the header
   if(address + header->size == sbreak){//if its the last block
     if(head== tail){
       head= tail= NULL; //if its the last and only block
     }else  { 
      tmp = head;
      while(tmp){
        if(tmp->next == tail){
          tmp->next = NULL;
          tail = tmp;
        }
        tmp = tmp->next;
      }     
     }

    sbrk(0-sizeof(header_t)-header->size);
    printf("\nsbrk called\n");
    return;
  }
   header->free = 1;
}

void heap_dump(){
  header_t * tmp;
  tmp = head;
  while(tmp){
    printf("\nblock size: %ld bytes | data \t", tmp->size - sizeof(header_t));
   for(int i ; i< tmp->size- sizeof(header_t); i++){
    //  char * d = tmp+sizeof(header_t);
    // printf("%c \t",d[i]);
   } 
  tmp = tmp->next;
  }
}
int main(){
  void * ad = init_arena(500);

  void * afbaaaa = allocate(4);
  void * afba = allocate(1);
  void * afbaw = allocate(2);
  void * afbad = allocate(1);
  void * afbads = allocate(100);
  void * afbadsq = allocate(100);
  void * afbadswq = allocate(100);
  void * afbadsdf = allocate(100);
  void * afbadsjk = allocate(100);
  printf("%p\n",afbaw);
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
