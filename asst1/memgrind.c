#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"
//#define malloc(x) mymalloc(x, __FILE__, __LINE__)
//#define free(x) myfree(x, __FILE__, __LINE__)


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
			
			if(coin == 0) {
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
			
			if(coin == 0) {
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
	/*
	int i = 0;
	for(i = 0; i < 50; i++) {
		free(ptrArr[i]);
	}
	*/
	while(counter > 0) {
		free(ptrArr[counter - 1]);
		counter--;
	}
	
	return 0;
	
	
	
}

//In the beginning, allocates 4030b to one pointer and sets it aside
//then, does what task D does.
//This tests if the malloc function will deny memory when there
//isnt a sufficient amount of space
//Frees all pointers at the end, including the one that points to 4030bs
int taskE() {
	
	//counter is at the next EMPTY element.
	int counter = 0;//keeps track of malloced pointer amt
	int mallocs = 0;//counts times malloc has been called
	int *initialPtr = (int*)malloc(4028);//allocates 4028b
	srand(time(0));//randomizer, returns a value that is
			//between 0 and INTEGER_MAX.
	
	
	//array that will store up to 50 pointers
	int *ptrArr[50] = { NULL };
	
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
			
			if(coin == 0) {
				//malloc a chunk 1 - 64
				ptrArr[counter] = (int*)malloc(((int)rand()) % 64 + 1);

				//if pointer is null, no more space!
				if(ptrArr[counter] == NULL) {
					//dont do anything, so the coin flips again
					//program will keep encountering this for loop until
					//malloc returns a valid pointer or
					//the program frees a memory
					
				} else {
				
					//increments everything to keep track of space in
					//the array and the total mallocs
					counter++;
					mallocs++;
				
				}
				
			} else {
				//free a pointer
				free(ptrArr[counter - 1]);
				counter--;
				
			}
		}
	}
	
	//frees the entire array at the end
	while(counter != 0) {
		free(ptrArr[counter - 1]);
		counter--;
	}
	
	printf("\n");
	//frees initial pointer
	free(initialPtr);
	return 0;
}

//this function randomly mallocs 127 and 254 spaces
//then, it frees 16 random pointers.
//afterward, attempts to malloc 16 pointers with 127 space
//tests if the malloc function fills in empty space
int taskF() {
	int *arr[256];
	int  *ptr = NULL;
	srand(time(0)); //randomizer for choosing the size of the space
	int coin = 0; //store coin flip result
	int i = 0;
	int ptramt = 0; //stores the amount of pointers in the array
	int size = ((int)rand() % 2 + 1) * 127;//returns randomly either 127 or 254
	ptr = (int*)malloc(size);
	
	//randomly mallocs 127 or 254 space until all of the space is filled
	while(ptr != NULL) {
		arr[i] = ptr;
		//printf("%d\t", i);
		i++;
		size = ((int)rand() % 2 + 1) * 127;//returns randomly either 127 or 254
		ptr = (int*)malloc(size);
		
	}
	//if the malloc failed at size 254, there is a chance that there still is a small amout of space left
	//the following line ensures that the entire array is completely filled
	arr[i] = (int*)malloc(127);
	
	printf("--------------------------------------------------------------\n");
	
	ptramt = i;//transfers i to ptramt so that we can reset i to 0
	
	//does the following process 10 times
	int j = 0;
	for(j = 0; j < 10; j++) {
		//frees random elements of the array
		for(i = 0; i < ptramt; i++) {
			coin = (int)rand() % 4;
			if(!coin) {//only runs when the coin was originally 0
				free(arr[i]);
			}	
		}
		
		//randomly mallocs 127 or 254 space until all of the space is filled
		
		//prepares a random sized space and stores it in ptr.
		i = ptramt;
		size = ((int)rand() % 2 + 1) * 127;//returns randomly either 127 or 254
		ptr = (int*)malloc(size);
		//loop that keeps adding randomly size spaces (127 or 254) until space has run out
		while(ptr != NULL) {
			arr[i] = ptr;
			//printf("%d\t", i);
			i++;
			size = ((int)rand() % 2 + 1) * 127;//returns randomly either 127 or 254
			ptr = (int*)malloc(size);
			
		}
		printf("----------------------------------------------------------------------\n");
		
		//if the malloc failed at size 254, there is a chance that there still is a small amout of space left
		//the following line ensures that the entire array is completely filled
		arr[i] = (int*)malloc(127);
		
		ptramt = i;//transfers the amount of pointers from i to pointeramount
	}
	
	//frees all pointers at the end
	i = 0;
	for(i = 0; i < ptramt; i++) {
		free(arr[i]);
	}
	
	return 0;
	
}

long mean(long *arr, int size) {
	long int sum = 0;
	
	//finds the sum of all of the times
	int i = 0; //for forloop
	for(i = 0; i < size; i++) {
		sum += arr[i];
	}
	
	//divides by the size and returns the result
	return sum / size;
}

int main(int argc, char *argv[]) {
	//testing area
	/*
	taskA();
	taskB();
	taskC();
	taskD();
	taskE();
	taskF();
	return 0;
	*/
	
	//struct to time the functions
	struct timeval start;
	struct timeval end;

	//array to store the times of each function A - F
	long timeArr[6][100];
	
	//run taskA 100 times
	int i = 0; //counter for forloops
	for(i = 0; i < 100; i++) {
		
		//starts the timer
		gettimeofday(&start, NULL);
		
		taskA();
		
		//ends the timer
		gettimeofday(&end, NULL);
		
		//gets the time
		//the first term finds the amount of seconds that elapsed
		//we multiply this by 1million to convert it to microseconds
		//the second term finds the amount of microseconds that elapsed
		//we add these two terms together to get the total amount of
		//microseconds it took for the function to execute
		timeArr[0][i] = (1000000 * (end.tv_sec - start.tv_sec)) + (end.tv_usec - start.tv_usec);
	}
	
	//run taskB 100 times
	for(i = 0; i < 100; i++) {
		
		//starts the timer
		gettimeofday(&start, NULL);
		
		taskB();
		
		//ends the timer
		gettimeofday(&end, NULL);
		
		//gets the time
		//the first term finds the amount of seconds that elapsed
		//we multiply this by 1million to convert it to microseconds
		//the second term finds the amount of microseconds that elapsed
		//we add these two terms together to get the total amount of
		//microseconds it took for the function to execute
		timeArr[1][i] = (1000000 * (end.tv_sec - start.tv_sec)) + (end.tv_usec - start.tv_usec);
	}
	
	//run taskC 100 times
	for(i = 0; i < 100; i++) {
		
		//starts the timer
		gettimeofday(&start, NULL);
		
		taskC();
		
		//ends the timer
		gettimeofday(&end, NULL);
		
		//gets the time
		//the first term finds the amount of seconds that elapsed
		//we multiply this by 1million to convert it to microseconds
		//the second term finds the amount of microseconds that elapsed
		//we add these two terms together to get the total amount of
		//microseconds it took for the function to execute
		timeArr[2][i] = (1000000 * (end.tv_sec - start.tv_sec)) + (end.tv_usec - start.tv_usec);
	}
	
	//run taskD 100 times
	for(i = 0; i < 100; i++) {
		
		//starts the timer
		gettimeofday(&start, NULL);
		
		taskD();
		
		//ends the timer
		gettimeofday(&end, NULL);
		
		//gets the time
		//the first term finds the amount of seconds that elapsed
		//we multiply this by 1million to convert it to microseconds
		//the second term finds the amount of microseconds that elapsed
		//we add these two terms together to get the total amount of
		//microseconds it took for the function to execute
		
		//printf("S: %ld; MS: %ld\n", (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));

		timeArr[3][i] = (1000000 * (end.tv_sec - start.tv_sec)) + (end.tv_usec - start.tv_usec);
	}
	
	//run taskE 100 times
	for(i = 0; i < 100; i++) {
		
		//starts the timer
		gettimeofday(&start, NULL);
		
		taskE();
		
		//ends the timer
		gettimeofday(&end, NULL);
		
		//gets the time
		//the first term finds the amount of seconds that elapsed
		//we multiply this by 1million to convert it to microseconds
		//the second term finds the amount of microseconds that elapsed
		//we add these two terms together to get the total amount of
		//microseconds it took for the function to execute
		timeArr[4][i] = (1000000 * (end.tv_sec - start.tv_sec)) + (end.tv_usec - start.tv_usec);
	}
	
	//run taskF 100 times
	for(i = 0; i < 100; i++) {
		
		//starts the timer
		gettimeofday(&start, NULL);
		
		taskF();
		
		//ends the timer
		gettimeofday(&end, NULL);
		
		//gets the time
		//the first term finds the amount of seconds that elapsed
		//we multiply this by 1million to convert it to microseconds
		//the second term finds the amount of microseconds that elapsed
		//we add these two terms together to get the total amount of
		//microseconds it took for the function to execute
		timeArr[5][i] = (1000000 * (end.tv_sec - start.tv_sec)) + (end.tv_usec - start.tv_usec);
	}
	
	//takes the time table, finds the mean time for each task, and outputs it.
	long avg[6];
	for(i = 0; i < 6; i++) {
		avg[i] = mean(timeArr[i], 100);
		
	}
	
	printf("The average time for taskA to run is: %ld\n", avg[0]);
	printf("The average time for taskB to run is: %ld\n", avg[1]);
	printf("The average time for taskC to run is: %ld\n", avg[2]);
	printf("The average time for taskD to run is: %ld\n", avg[3]);
	printf("The average time for taskE to run is: %ld\n", avg[4]);
	printf("The average time for taskF to run is: %ld\n", avg[5]);
	
	return 0;
}























