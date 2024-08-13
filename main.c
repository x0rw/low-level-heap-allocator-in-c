#include <stdio.h>
#include <unistd.h>

#define MALLOC_ALIGNMENT \
  (__alignof__ (double) > sizeof (size_t) ? __alignof__ (double) : sizeof (size_t))

#define MALLOC_HEADER_SIZE			\
  (MALLOC_ALIGNMENT < sizeof (size_t)		\
   ? sizeof (size_t)				\
   : MALLOC_ALIGNMENT)
struct header {
    size_t size;
    unsigned free;
    struct header *next;
};
 
typedef struct header header_t;
header_t *head, *tail;

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
  printf("address:%d\n",sizeof(header_t));
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

int main(){
  int *i1, *i2;
  char * mem = alloc(4);
  char * memd = alloc(40);
  
} 
