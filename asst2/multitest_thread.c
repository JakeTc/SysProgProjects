#include "multitest.h"

typedef struct _searchArgs {
	int *arr;
	int start;
	int end;
	int target;
} searchArgs;

void* searchSection(void* arguments) {
	//convert and unpack the arguments
	searchArgs* arg = (searchArgs*)arguments;
	int *arr1 = arg->arr;
	int start1 = arg->start;
	int end1 = arg->end;
	int target1 = arg->target;

	//pointer to the return argument. set it = -1
	int* retval = (int*)malloc(sizeof(int));
	*retval = -1;
	
	int i = 0;
	for(i = start1; i < end1; i++) {
		if(arr1[i] == target1) {
			*retval = i;
			break;
		}
	}
	
	//-1 indicates that the element was not found
	pthread_exit((void*)retval);	
	
}

int search(int *arr, int end, int target, int amount) {
	//array to store all of the threads
	pthread_t* kernels = (pthread_t*)malloc(sizeof(pthread_t) * amount);
	
	//determine how the array will get split by the threads
	int step = end / (amount - 1);
	int remainder = end % (amount - 1);
	
	//create all of the threads and give them their section
	int i = 0;
	for(i = 0; i < amount; i++) {
		int start = i * step;
		
		//determines end depending on if the child is last or not
		int end;
		if(i == amount - 1) {
			end = start + remainder;
		
		} else {
			end = start + step;
		}

		
		
		
		//first make the searchargs struct
		searchArgs* arg = (searchArgs*)malloc(sizeof(searchArgs));
		arg->arr = arr;
		arg->start = start;
		arg->end = end;
		arg->target = target;
		
		//make a fnptr to searchSection
		void* (*fnptr)(void*) = searchSection;

		pthread_create(kernels + i, NULL, searchSection, (void*)arg);
			
	}
	
	//join with threads and get their return values
	//if the return value != -1, target found	
	int found = 0;
	int index = -1;
	for(i = 0; i < amount; i++) {
		//joins with every thread in the kernel list
		void* retval;
		if(pthread_join(kernels[i], &retval) != 0) {
			printf("Error\n");
			return index;
		}
		
		//if the returned value is not -1, thats the index we want to return
		if(*((int*)retval) != -1 && found == 0) {
			index = *((int*)retval);
			found = 1;
		}
	}
	
	return index;
}


