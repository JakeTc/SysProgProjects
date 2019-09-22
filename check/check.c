/* Jake Truongcao
 * CS214 check project
 */

#include <stdlib.h>
#include <stdio.h>

//structure for generic linked list
typedef struct _Node {
	void *data;
	struct _Node *next;
} Node;

//makes a new node
Node *mkNode(void *data) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = NULL;

	return nwNode;
}

//makes a new node at the front
Node *push(void *data, Node *head) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = head;

	return nwNode;
}

void deleteLL(Node *head) {
	Node *current = head;
	Node *next;
	
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

}

//coounts the numbeer of chars in a string INCLUDING delimeter
int tknlng(char *str, char dlim) {
	int lng = 1;	
	while(*(str + lng - 1) != dlim) {
		lng++;
	}
	
	return lng;
}

//breaks a whole string into tokens based upon a delimeter parameter.
//DOES NOT include the delimeters!
char **tokenizer(char whole[], char dlim, int *tknCount){
	char *ptr = whole;
	int strlength = 1; //INCLUDES "\0"
	*tknCount = 1;//expects AT LEAST 1 token. each delimeter will add to the amount of expected tokens
	
	//counts the amount of delimeters present, then adds 1 to indicate the number of expexted tokens
	while(*ptr != '\0') {
		if(*ptr == dlim) {
			*tknCount = *tknCount + 1;
		}
		
		strlength++;
		ptr++;
	}
	
	//resets the pointer at the beginning of the string
	ptr = whole;
	printf("Amt tkns: %d\n", *tknCount);
	printf("Strlng: %d\n", strlength);	
	
	char **tokens = malloc(*tknCount * sizeof(char*));
	
	printf("made char**\n");	
	
	//split and store all tokens - 1
	char* tknptr = ptr;
	
	int j;//for for-loop
	for(j = 0; j < (*tknCount) - 1; j++) {
		//allocates space for the token
		int tknsize = tknlng(tknptr, dlim);
		tokens[j] = malloc(tknsize);

		//stores every character of the current token into the token array
		int k;//for for-loop
		for(k = 0; k < tknsize - 1; k++) {
			tokens[j][k] = *(tknptr);
			tknptr++;
		}
		tokens[j][k] = '\0';
		tknptr++; //skips the delimeter
		
		printf("a token succeeded\n");
	}
	//stores the last token, ending in a \0
	int doOnce = 1;
	while(doOnce) {
		
		//allocates space for the token
		int tknsize = tknlng(tknptr, dlim);
		tokens[*tknCount - 1] = malloc(tknsize);
		
		//stores every character of the current token into the token array
		int k;//for for-loop
		for(k = 0; k < tknsize - 1; k++) {
			tokens[*tknCount - 1][k] = *(tknptr);
			tknptr++;
		}
		tokens[j][k] = '\0';
		doOnce = 0;
		
		printf("last token succeeded\n");
	}
	
	printf("\nPrinting Tokens:\n");
	//print tokens for testing
	int i; //for for-loop
	for(i = 0; i < *tknCount; i++) {
		printf("\"%s\"\n", tokens[i]);
	}
	printf("---------------------------------------------------\n");	
	return tokens;
}


int main(int argc, char* argv[]) {

	//check if given one and only one input
	if(argc > 2) {
		printf("error: too many arguments.\n");
		return 0;
	} else if(argc < 2) {
		printf("error: no arguments given.\n");
		return 0;
	}
	//keeps track of the tokens 	
	int *tknCount = (int*)malloc(sizeof(int));
	int i = 0;//counter for all for loops

	char **expressions  = tokenizer(argv[1], ';', tknCount);
	
	//*
	//keeps track of the operators and operands within each token
	//using an array of pointers
	char ***opers = (char***)malloc((*tknCount) * sizeof(char**));
	int **tknCounters = (int**)malloc((*tknCount) * sizeof(int*));
	
	for(i = 0; i < *tknCount; i++) {
		tknCounters[i] = (int*)malloc(sizeof(int*));
	}
	
	i = 0;
	for(i = 0; i < *tknCount; i++) {
		printf("loop %d worked\n", i);	
		opers[i] = tokenizer(expressions[i], ' ', tknCounters[i]);
	}
	//*/






	
	//free all elements of expression double pointer
	i = 0;//reset for loop counter to 0
	for(i = 0; i < *tknCount; i++) {
		free(expressions[i]);
	}
	free(expressions);
	free(tknCount);
	
	return 0;
}























