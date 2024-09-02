#include "../include/memory_worker.h"
void merge_alloc_blocks(struct arena_h * arena){
    struct alloc_block * current_block = arena->head;
    while(current_block->next){
        //mux
        struct alloc_block * next_block = current_block->next;
        //if two contigous blocks are not free 
        if(current_block->reserved == 0 && next_block->reserved == 0){
            current_block->size = current_block->size + next_block->size + sizeof(struct alloc_block);
            current_block->next = next_block->next;
            bzero((void *) next_block, sizeof(struct alloc_block));
            continue;        
        }
        current_block= current_block->next;
    }

}
void * _run_order(void * args){
    printf("arena_base %d", arena_base);

}
void init_worker(){
    pthread_t pt;
    void * res;
    pthread_create(&pt,NULL,&_run_order, NULL);
    pthread_join(pt, &res);
}
