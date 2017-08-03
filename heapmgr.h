int *nextBlock(int *p);    // return a pointer to the block that follows p
void  initmemory(int size);
void *myalloc(int length);
void  myfree(void *ptr);
void  coalesce();
void  printallocation();
void  printresult(int* p);
int  isAllocated(int *p);  // is the block at location p allocated?
int *firstBlock();         // return a pointer to the first block on the heap
int *lastBlock();          // return a pointer to the sentinel block
