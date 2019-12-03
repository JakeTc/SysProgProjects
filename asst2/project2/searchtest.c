#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "multitest.h"
typedef struct _efficiencies
{
	unsigned long minTime;
	unsigned long maxTime;
	double average;
	double stdDev;
}efficiencies;
void makeArray(int*,int);
void testFunc(int,int);
void test8();
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("Error, expected a single number 1 through 8 to denote which test should be run\n");
		return;
	}
	srand(time(0));
	char testType=*argv[1];
	if(testType=='1')
	{
		testFunc(1, 250);
	}else if(testType=='2')
	{
		testFunc(2, 500);
	}else if(testType=='3')
	{
		testFunc(3, 1250);
	}else if(testType=='4')
	{
		testFunc(4, 2500);
	}else if(testType=='5')
	{
		testFunc(5, 12500);
	}else if(testType=='6')
	{
		testFunc(6, 25000);
	}else if(testType=='7')
	{
		testFunc(7, 250000);
	}else if(testType=='8')
	{
		test8();
	}else
	{
		printf("Error, expected a single number 1 through 8 to denote which test should be run\n");
		return;
	}
	return;
}
void makeArray(int* searchSpace,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		searchSpace[i]=i;
	}
	for(i=0;i<size;i++)
	{
		int randInt1=rand()%size;
		int randInt2=rand()%size;
		int temp=searchSpace[randInt1];
		searchSpace[randInt1]=searchSpace[randInt2];
		searchSpace[randInt2]=temp;
	}
	return;
}
void testFunc(int testNum, int size)
{
	int numIterations=1000;
	int* searchSpace=malloc(size*sizeof(int));
	makeArray(searchSpace,size);
	unsigned long results[numIterations];
	unsigned long maxTime=0;
	unsigned long minTime=18000000000000000000;
	unsigned long total=0;
	double varianceTotal=0;
	double standardDev;
	int i;
	double average;
	struct timeval start;
	struct timeval end;
	int location;

	
		
	printf("Running Test %d using %s\nLength=%d, Target=0, Step Size=250\n",testNum,mode,size);
	for(i=0;i<numIterations;i++)
	{
		gettimeofday(&start,NULL);
		location=dummy(size, searchSpace, 0, 250);
		gettimeofday(&end,NULL);
		int randInt=rand()%size;
		int temp=searchSpace[location];
		searchSpace[location]=searchSpace[randInt];
		searchSpace[randInt]=temp;
		results[i]=(1000000*(end.tv_sec-start.tv_sec))+(end.tv_usec-start.tv_usec);
		printf("Iteration %d time was %lu microseconds\n",i,results[i]);
		
		
		if(results[i]>maxTime)
		{
			maxTime=results[i];
		}
		if(results[i]<minTime)
		{
			minTime=results[i];
		}
		total=total+results[i];
	}
	average=(double)total/(double)numIterations;
	for(i=0;i<numIterations;i++)
	{
		varianceTotal=varianceTotal+(((double)results[i]-average)*((double)results[i]-average));
	}
	varianceTotal=varianceTotal/(double)numIterations;
	standardDev=sqrt(varianceTotal);
	printf("Min time= %lu microseconds\nMax time= %lu microseconds\nAverage time= %lf microseconds\nStandard deviation= %lf microseconds\n",minTime,maxTime,average,standardDev);
	free(searchSpace);
	return;
}
void test8()
{
	int threadCounts[24]={1,2,3,4,5,6,8,10,12,15,16,20,24,30,32,40,48,60,80,96,120,160,240,480};
	int size=480;
	int numIterations=1000;
	int* searchSpace=malloc(size*sizeof(int));
	makeArray(searchSpace,size);
	unsigned long results[numIterations];
	unsigned long maxTime=0;
	unsigned long minTime=18000000000000000000;
	unsigned long total=0;
	double varianceTotal=0;
	double standardDev;
	int i;
	int j;
	int count=0;
	efficiencies times[24];
	double average;
	struct timeval start;
	struct timeval end;
	int location;
	for(j=0;j<24;j++)
	{
		printf("Running Test 8 using %d %s\nLength=480, Target=0, Step Size=%d\n",threadCounts[j],mode,480/threadCounts[j]);
		for(i=0;i<numIterations;i++)
		{
			gettimeofday(&start,NULL);
			location=dummy(size, searchSpace, 0, 480/threadCounts[j]);
			gettimeofday(&end,NULL);
			int randInt=rand()%size;
			int temp=searchSpace[location];
			searchSpace[location]=searchSpace[randInt];
			searchSpace[randInt]=temp;
			results[i]=(1000000*(end.tv_sec-start.tv_sec))+(end.tv_usec-start.tv_usec);
			printf("Iteration %d time was %lu microseconds\n",i,results[i]);
			if(results[i]>maxTime)
			{
				maxTime=results[i];
			}
			if(results[i]<minTime)
			{
				minTime=results[i];
			}
			total=total+results[i];
		}
		average=(double)total/(double)numIterations;
		for(i=0;i<numIterations;i++)
		{
			varianceTotal=varianceTotal+(((double)results[i]-average)*((double)results[i]-average));
		}
		varianceTotal=varianceTotal/(double)numIterations;
		standardDev=sqrt(varianceTotal);
		times[count].minTime=minTime;
		times[count].maxTime=maxTime;
		times[count].average=average;
		times[count].stdDev=standardDev;
		printf("Min time= %lu microseconds\nMax time= %lu microseconds\nAverage time= %lf microseconds\nStandard deviation= %lf microseconds\n",minTime,maxTime,average,standardDev);
		count++;
		total=0;
		varianceTotal=0;
		maxTime=0;
		minTime=18000000000000000000;
	}
	for(i=0;i<24;i++)
	{
		printf("Average time using %d %s was %lf\n",threadCounts[i],mode,times[i].average);
	}
	free(searchSpace);
	return;
}
	
	