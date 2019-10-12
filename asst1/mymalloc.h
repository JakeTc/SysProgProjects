#ifndef _MY_MALLOC_H
#define _MY_MALLOC_H

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

void* mymalloc(int,char*,int);
void myfree(void*,char*,int);
static char myblock[4096];
#endif
