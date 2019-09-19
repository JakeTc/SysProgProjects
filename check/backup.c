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

//breaks a whole string into tokens based upon a delimeter parameter
char **tokenizer(char whole[], char dlim){
	char *ptr = whole;
	int strlength = 1; //INCLUDES "\0"
	int tknCounter = 1;//expects AT LEAST 1 token. each delimeter will add to the amount of expected tokens
	
	//counts the amount of delimeters present, then adds 1 to indicate the number of expexted tokens
	while(*ptr != '\0') {
		if(*ptr == dlim) {
			tknCounter++;
		}
		
		strlength++;
		ptr++;
	}
	
	//resets the pointer at the beginning of the string
	ptr = whole;
	printf("Amt tkns: %d\n", tknCounter);
	printf("Strlng: %d\n", strlength);	
	
	char **tokens = malloc(tknCounter * sizeof(char*));
	
	printf("made char**\n");	
	
	//split and store all tokens - 1
	char* tknptr = ptr;
	
	int j;//for for-loop
	for(j = 0; j < tknCounter - 1; j++) {
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
		tokens[tknCounter - 1] = malloc(tknsize);
		
		//stores every character of the current token into the token array
		int k;//for for-loop
		for(k = 0; k < tknsize - 1; k++) {
			tokens[tknCounter - 1][k] = *(tknptr);
			tknptr++;
		}
		tokens[j][k] = '\0';
		doOnce = 0;
		
		printf("last token succeeded\n");
	}
	
	printf("\nPrinting Tokens:\n");
	//print tokens for testing
	int i; //for for-loop
	for(i = 0; i < tknCounter; i++) {
		printf("%s\n", tokens[i]);
	}
	
	return tokens;
}


int main(int argc, char* argv[]) {
	printf("length = %d\n", tknlng("hello", '\0'));

	//check if given one and only one input
	if(argc > 2) {
		printf("error: too many arguments.\n");
		return 0;
	} else if(argc == 1) {
		printf("error: no arguments given.\n");
		return 0;
	}
	
	char **expressions  = tokenizer(argv[1], ';');
	
	free(expressions);
	
	return 0;
}























