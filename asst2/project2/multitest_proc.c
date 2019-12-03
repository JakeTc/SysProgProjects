#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
typedef struct _process
{
	int index;
	pid_t id;
}process;
int variableSearch(int,int*,int,int);
const char* mode="process's";
int variableSearch(int length,int* searchSpace,int target,int stepSize)
{
	process* plist;
	int count=0;
	int i;
	int j;
	pid_t targetid;
	pid_t temp;
	int realIndex;
	int result;
	int status;
	if(length%stepSize==0)
	{
		plist=(process*)malloc((length/stepSize)*sizeof(process));
	}else
	{
		plist=(process*)malloc((length/stepSize)*sizeof(process)+1);
	}
	for(i=0;i<length;i+=stepSize)
	{
		plist[count].index=i;
		temp=fork();
		if(temp<0)
		{
			printf("Fork failed\n");
			free(plist);
			return 0;
		}else if(temp==0)
		{
			for(j=0;j<stepSize;j++)
			{
				if(i+j>=length)
				{
					exit(255);
				}else if(searchSpace[i+j]==target)
				{
					exit(j);
				}
			}
			exit(255);
		}
		else
		{
			plist[count].id=temp;
			count++;
		}
	}
	for(i=0;i<count;i++)
	{
		targetid=wait(&status);
		result=WEXITSTATUS(status);
		if(result!=255)
		{
			for(j=0;j<count;j++)
			{
				if(plist[j].id==targetid)
				{
					realIndex=plist[j].index+result;
					break;
				}
			}
		}
	}
	free(plist);
	return(realIndex);
}

