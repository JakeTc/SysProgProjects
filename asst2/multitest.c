#include "multitest.h"

int search(int *arr, int end, int parent, int amount) {
	int *children = (int*)malloc(sizeof(int) * amount);
	int child = -2;
	
	int i = 0;
	for(i = 0; i < amount; i++) {
		child = fork();
		if(child == 0) {
			break;
		} else {
			children[i] = child;
			
		}
			
	}
	
	
	free(children);
}
