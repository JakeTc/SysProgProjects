#include "multitest.h"

//does a simple search of the speified portion of the array
int searchArr(int *arr, int start, int end, int target) {
	int i = start;
	for(i = start; i < end; i++) {
		if(arr[i] == target) {
			return i;
			printf("found: %d\n", i);
		}
	}
	
	//start -1 indicates that the element was not found
	return start - 1;
}

//the end must be the length of the  array that is going to be worked with
int search(int *arr, int end, int target, int amount) {
	
	int *children = (int*)malloc(sizeof(int) * amount);
	int child = -2;
	int index = -1;
	int found = 0;
	//end == length
	
	//determine how the array will get split by the processes
	int step = end / (amount - 1);
	int remainder = end % (amount - 1);
	
	//creates all of the child processes
	int i = 0;
	int partition = 0;;
	
		
	
	for(i = 0; i < amount; i++) {
		child = fork();
		if(child == 0) {
			partition = i;
			free(children);//child doesnt need this
			break;
		} else {
			//parent stores PID of child
			children[i] = child;
			printf("Parent loop iteration %d\n", i);
			
		}
	}
	
	//you are the child and you do child stuff
	if(child == 0) {
		
		
		//uses the index of the for loop to determine what to give to the child
		int start = partition * step;
		
		//sets end depending on if the child is a remainder or not
		//end = last index + 1
		if(partition == amount - 1) {
			end = start + remainder;
		} else {
			end = start + step;
		}
		
		if(start == end) {
			exit(255);
		}
			
		printf("Step: %d\tRemainder: %d\tAmount: %d\tStart: %d\tEnd: %d\n", step, remainder, amount, start, end);
		
		//hopefully the index is <250
		//returns this number to the parent process
		index = searchArr(arr, start, end, target) - start;
		
		//send exit signal and return if you found the index!
		if(index == -1 || index > 250) {
			exit(255);
		} else {
			printf("Found at relindex: %d\n", index);
			exit(index);
		}
		exit(254);
		
	//you are the parent, and must wait for your children
	} else {
		int status;
		int childPID;
		
		//waits for ALL children (first come, first serve)
		for(i = 0; i < amount; i++) {
			childPID = wait(&status);
			int relativeIndex = WEXITSTATUS(status);

			printf("relIndex: %d\n", relativeIndex);
			//if == 255, assume target not found
			if(relativeIndex != 255 && !found) {
				//recalculates start of the array, adds that to the childs exit status
				//, and sets index to be that
				partition = searchArr(children, 0, amount - 1, childPID);
				index =  partition * step + relativeIndex;
				found = 1;
			}
		}
		
	}
	
	//finished with using children
	free(children);
		
	//returns the index
	return index;
}


