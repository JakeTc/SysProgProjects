#include "multitest.h"

//the end must be the length of the  array that is going to be worked with
int search(int *arr, int end, int target, int amount) {
	int *children = (int*)malloc(sizeof(int) * amount);
	int child = -2;
	int index = -1;
	int found = 0;
	//end == length
	
	//determine how the array will get split by the processes
	int step = (end) / (amount - 1);
	int remainder = (end) % (amount - 1);
	
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
			
		}
	}
	
	//you are the child and you do child stuff
	if(child == 0 && partition != (amount - 1)) {
		//uses the index of the for loop to determine what to give to the child
		int start = partition * step;
		end = start + step; //end represents the last index + 1
		
		//hopefully the index is <250
		//returns this number to the parent process
		index = searchArr(arr, start, end, target) - start;
		
		//send exit signal and return if you found the index!
		if(index > 250 || index == -1) {
			exit(255);
		} else {
			exit(index);
		}
		
	
	//this process deals with the remainder
	} else if(child == 0) {
		int start = partition * step;
		end = start + remainder;
		
		//hopefully the index is <250
		//returns this number to the parent process
		index = searchArr(arr, start, end, target) - start;
		if(index == -1 || index > 250) {
			exit(255);
		} else {
			exit(index);
		}
		
	//you are the parent, and must wait for your children
	} else {
		int status;
		int childPID;
		
		//waits for ALL children (first come, first serve)
		for(i = 0; i < amount; i++) {
			childPID = wait(&status);
			
			//if == 255, assume target not found
			if(WEXITSTATUS(status) != 255 && !found) {
				//recalculates start of the array, adds that to the childs exit status
				//, and sets index to be that
				partition = search(children, 0, amount, childPID);
				index =  partition * step + WEXITSTATUS(status);
				found = 1;
			}
		}
		
	}
	
	//finished with using children
	free(children);
	
	//returns the index
	return index;
}

//does a simple search of the speified portion of the array
int searchArr(int *arr, int start, int end, int target) {
	int i = 0;
	for(i = start; i < end; i++) {
		if(arr[i] == target) {
			return i;
		}
	}
	
	//-1 indicates that the element was not found
	return -1;
}
