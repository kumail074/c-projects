#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct block{
    size_t size;
    struct block *next;
    unsigned free;
} block;

#define BLOCKSIZE sizeof(block)

static block *freelist = NULL;

block *findfreeblock(size_t size){
    block *current = freelist;
    while(current && (current->free && current->size >= size)) {
        current = current->next; 
    }
    return current;
}

block *requestblock(block *last, size_t size){
    block *Block = sbrk(0);
    void *request = sbrk(size+BLOCKSIZE);
    if(request == (void*) -1)
        return NULL;

    Block->size = size;
    Block->next = NULL;
    Block->free = 0;

    if(last){
        last->next = Block;
    }
    return Block;
}

void *mymalloc(size_t size){
    if(size<=0)
        return NULL;

    block *b;
    if(!freelist){
        b = requestblock(NULL, size);
        if(!b)
            return NULL;
        freelist = b;
    } else {
        block *last = freelist;
        b = findfreeblock(size);
        if(!b){
            b = requestblock(last, size);
            if(!b)
                return NULL;
        } else {
            b->free = 0;
        }
    }
    return (b+1);
}

void mergefreeblock(){
    block *current = freelist;
    while(current && current->next){
        if(current->free && current->next->free){
            current->free += BLOCKSIZE + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void myfree(void *ptr){
    if(!ptr)
        return;
    block *b = (block*)ptr - 1;
    b->free = 1;
    mergefreeblock();
}

int main(){
    int *data = (int*)mymalloc(sizeof(int)*10);
    if(data == NULL){
        printf("Allocation failed\n");
        return 1;
    }
    for(int i=0; i<10; i++){
        data[i] = i*2;
        printf("%d ", data[i]);
    }
    putchar('\n');
    myfree(data);
    return 0;
}
