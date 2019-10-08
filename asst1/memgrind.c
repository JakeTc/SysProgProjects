#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//immediately mallocs and frees 1 byte 150 times
int taskA() {
	//pointer to be malloced and demalloced
	int *ptr = NULL;
	//counter for forloop
	int i = 0;
	for(i = 0; i < 150; i++) {
		ptr = (int*)malloc(1);
		free(ptr);
	}
	return 0;
}

//mallocs 150 bytes in total, mallocing 1 byte 50 times,
//then freeing all 50 bytes. Does this 3 times
int taskB() {
	//stores chunks of 50 pointers
	int *ptrArr[50];
	
	//counter for forloop
	int i = 0;
	
	//mallocs and frees 50 bytes 3 times
	for(i = 0; i < 3; i++) {
		int j = 0;//counter for forloops

		//mallocs 1 byte to all 50 elements of the array
		for(j = 0; j < 50; j++) {
			ptrArr[j] = (int*)malloc(1);
				
		}
		
		//frees all 50 elements of the array
		for(j = 0; j < 50; j++) {
			free(ptrArr[j]);
			
		}
	}
	return 0;
	
}

int taskC() {
	
	//counter is at the next EMPTY element.
	int counter = 0;//keeps track of malloced pointer amt
	int mallocs = 0;//counts times malloc has been called
	srand(time(0));//randomizer, returns a value that is
			//between 0 and INTEGER_MAX.
	
	//array that will store up to 50 pointers
	int *ptrArr[50];
	
	//randomly mallocs and frees 1 byte chunks until 50 mallocs
	//have been made
	while(mallocs < 50) {
		
		//if array is empty
		if(counter == 0) {
			//mallocs a byte
			ptrArr[counter] = (int*)malloc(1);
			counter++;
			mallocs++;
		} else {
			//coin flips on whether to malloc or free
			int coin = ((int)rand()) % 2;
			
			if(coin = 0) {
				//malloc a byte
				ptrArr[counter] = (int*)malloc(1);
				counter++;
				mallocs++;
				
			} else {
				//free a byte
				free(ptrArr[counter - 1]);
				counter--;
				
			}
		}
	}
	
	//frees the entire array at the end
	while(counter > 0) {
		free(ptrArr[counter - 1]);
		counter--;
	}
	return 0;
}

//randomly mallocs or frees randomly sized chunks
//chunk size = [1, 64]
//mallocs 50 times in total
//free all pointers at the end if they are not freed
//ASSUMES that the malloc function returns a null pointer
//if there is no more space!!!
int taskD() {
	
	//counter is at the next EMPTY element.
	int counter = 0;//keeps track of malloced pointer amt
	int mallocs = 0;//counts times malloc has been called
	srand(time(0));//randomizer, returns a value that is
			//between 0 and INTEGER_MAX.
	
	//array that will store up to 50 pointers
	int *ptrArr[50];
	
	//randomly mallocs and frees 1-64 byte chunks until 50 mallocs
	//have been made
	while(mallocs < 50) {
		
		//if array is empty
		if(counter == 0) {
			//mallocs a chunk
			//randomizes chunk size, adding 1 to make sure that
			//we are never mallocing 0 bytes!
			ptrArr[counter] = (int*)malloc(((int)rand()) % 64 + 1);
			
			
			//increments everything to keep track of space in
			//the array and the total mallocs
			counter++;
			mallocs++;
		} else {
			//coin flips on whether to malloc or free
			int coin = ((int)rand()) % 2;
			
			if(coin = 0) {
				//malloc a chunk 1 - 64
				ptrArr[counter] = (int*)malloc(((int)rand()) % 64 + 1);
		
				//if pointer is null, no more space!
				if(ptrArr[counter] == NULL) {
					//resets everything, so the coin flips again
					//program will keep encountering this for loop until
					//malloc returns a valid pointer or
					//the program frees a memory
					
					//decrements everything to reset
					counter--;
					mallocs--;
				}
				
				//increments everything to keep track of space in
				//the array and the total mallocs
				counter++;
				mallocs++;
				
			} else {
				//free a pointer
				free(ptrArr[counter - 1]);
				counter--;
				
			}
		}
	}
	
	//frees the entire array at the end
	while(counter > 0) {
		free(ptrArr[counter - 1]);
		counter--;
	}
	return 0;
	
	
	
}

int main(int argc, char *argv[]) {
	taskD();
	
	return 0;
}





















