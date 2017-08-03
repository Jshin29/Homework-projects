#include <stdio.h>
#include "heapmgr.h"
int *header;
int *headernext;
int *sentinel;
void *p;
int totalblock;
int freeblock;


void  initmemory(int size){  // initialize a simulated heap
    int factor =size/8;
    totalblock = (8*(factor +1))+8;
    freeblock = (8*(factor +1));
    printf("free block size in initmemory() = %d\n", freeblock); 
    p =  malloc(totalblock); 
    sentinel = p + totalblock -4 ;
    *sentinel = 0;
    header = p+4;
    *header = freeblock;   
    printf("the address of the original header = %d\n", header);
    printf("\t=== End of initmemory()=== \n\n");
}
    

void *myalloc(int length){   // allocate a block of length (or more) bytes
    int newsize = (((length)/8)+1) *8;   
    printf("required size = %d\n", length);
    printf("allocated size = %d\n", newsize);
    int *ptr = header;
    printf("the content of the header = %d\n", *ptr);
    while(1){
        if( *ptr > newsize && (*ptr & 1)== 0){
            int oldsize = *ptr;
            *ptr = newsize +1;
    		printf("---the addredd of the current header after myaloc() = %d\n", ptr);
    		printf("---the content of the header after myaloc() = %d\n", *ptr);
            ptr= ptr + newsize/4 ;
            *ptr = oldsize - newsize ;   
    		printf("---the addredd of the next header after myaloc() = %d\n", ptr);
    		printf("---the content of the next header after myaloc() = %d\n", *ptr);
    		printf("\t=== End of myalloc()=== \n\n");
		return;
        }
        else if ((*ptr & 1)!=0) {
            ptr = ptr + ( *ptr/4);
    		printf("the addredd of the next header = %d\n", ptr);
    		printf("\t\tthe block is used, so go to next header  = %d\n", *ptr);
	
        } else
            return NULL;
    }//end of while 
}

void  myfree(void *ptr){     // free an allocated block
    int *ptr1 = (int*)ptr -4;
    *ptr1 = *ptr1 -1;
}

void  coalesce(){            // go through the heap, coalescing unallocated blocks
    int *next = nextBlock(p);
    int *ptr = p;
    while( *next != 0){
        if ((*ptr & 1) ==0 && (*next &1) == 0)
           *ptr = *ptr + *next + 8;
        else
            ptr = nextBlock(ptr);

        next = nextBlock(ptr);
    }
}

int *nextBlock(int *p){    // return a pointer to the block that follows p
     int *ptr = p +4;
     ptr = ptr + *ptr;
     return ptr;
}

void printallocation() {
    int *ptr = header;
    int count = 0;
    while(*ptr > 0){
        if( (*ptr & 1)== 0){
            int size = *ptr;
    		printf("Block %d: size %d\t\tunallocated\n", count, size);
            ptr= ptr + (*ptr/4);
        }
        else {
            int size = *ptr-1;
    		printf("Block %d: size %d\t\tallocated\n", count, size);
            ptr= ptr + (*ptr/4);
        }
        count++;
     }

}

