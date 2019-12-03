#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
typedef struct _arguments
{
	int index;
	int target;
	int* searchSpace;
	int length;
	int stepSize;
} arguments;
typedef struct _myThread
{
	pthread_t id;
	int index;
}myThread;
int variableSearch(int,int*,int,int);
void* search(void*);
const char* mode="threads";
int variableSearch(int length,int* searchSpace,int target,int stepSize)
{
	myThread* tlist;
	int count=0;
	int i;
	int j;
	pid_t targetid;
	pid_t temp;
	int realIndex;
	int status;
	void* retval;
	int* intval;
	int result;
	if(length%stepSize==0)
	{
		tlist=(myThread*)malloc((length/stepSize)*sizeof(myThread));
	}else
	{
		tlist=(myThread*)malloc((length/stepSize)*sizeof(myThread)+1);
	}
	for(i=0;i<length;i+=stepSize)
	{
		tlist[count].index=i;
		arguments* args=(arguments*)malloc(sizeof(arguments));
		args->index=i;
		args->target=target;
		args->searchSpace=searchSpace;
		args->length=length;
		args->stepSize=stepSize;
		if(pthread_create(&(tlist[count].id),NULL,search,args)!=0)
		{
			free(tlist);
			printf("Thread creation failed\n");
			return 0;
		}else
		{
			count++;
		}
	}
	for(i=0;i<count;i++)
	{
		pthread_join(tlist[i].id,&retval);
		intval=(int*)retval;
		result=*intval;
		if(result!=255)
		{
			realIndex=tlist[i].index+result;
		}
		free(retval);
	}
	free(tlist);
	return(realIndex);
}
void* search(void* arg)
{
	arguments* args=(arguments*)arg;
	int index=args->index;
	int target=args->target;
	int stepSize=args->stepSize;
	int length=args->length;
	int* searchSpace=args->searchSpace;
	int i;
	int *retval=(int*)malloc(sizeof(int));
	*retval=255;
	for(i=0;i<stepSize;i++)
	{
		if(index+i>=length)
		{
			free(args);
			pthread_exit(retval);
		}else if(searchSpace[index+i]==target)
		{
			free(args);
			*retval=i;
			pthread_exit(retval);
		}
	}
	free(args);
	pthread_exit(retval);
}