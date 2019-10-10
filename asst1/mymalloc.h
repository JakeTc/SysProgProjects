#ifndef _MY_MALLOC_H
#define _MY_MALLOC_H
void* mymalloc(int,char*,int);
void myfree(void*,char*,int);
static char myblock[4096];
#endif
