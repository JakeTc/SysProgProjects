/* Jake Truongcao
 * CS214 check project
 */

#include <stdlib.h>
#include <stdio.h>

//makes boolean return values possible!
typedef enum {false, true} bool;

//coounts the numbeer of chars in a string INCLUDING delimeter
int tknlng(char *str, char dlim) {
	int lng = 1;	
	while(*(str + lng - 1) != dlim) {
		lng++;
	}
	
	return lng;
}

//compares two strings and returns true or false
bool strCompare(char *arg1, char *arg2) {
	int i = 0;//used to keep track of the current character
	
	//while loop to check if the end of a string has been reached
	while((arg1[i] != '\0') && (arg2[i] != '\0')) {
		//returns false if the characters are not equal

		if(arg1[i] != arg2[i]) {
			return false;
		}
		i++;
	}
	
	//returns true if both statements are \0.
	if((arg1[i] == '\0') && (arg2[i] == '\0')) {
		return true;
	//retrurns false otherwise
	} else {
		return false;
	}
}

//checks if the token is an arithmetic operand
bool aoperand(char *token) {
	//list of arithmetic operands
	char *aopds[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	
	int length = 10;//amount of valid operands	
	
	//loop to check if the token is within the list
	int i;//variable that counts loop iterations
	bool result = false;//
	for(i = 0; i < length; i++) {
		//compares the tokens to see if they are equal!
		if(strCompare(token, aopds[i])) {
			result = true;
			break;
		}
	}
	
	return result;
}

//checks if the token is a logical operand
bool loperand(char *token) {
	//list of logical operands
	char *lopds[2] = {"true", "false"};
	int length = 2;//amount of valid operands

	//loop to check if the token is within the list
	int i;//variable that counts loop iterations
	bool result = false;//
	for(i = 0; i < length; i++) {
		//compares the tokens to see if they are equal!
		if(strCompare(token, lopds[i])) {
			result = true;
			break;
		}
	}
	
	return result;
}

//checks if the token is an arithmetic operator
bool aoperator(char *token) {
	//list of arithmetic operators
	char *aoprs[4] = {"+", "-", "*", "/"};
	int length = 4;//amount of valid operators
	
	//loop to check if the token is within the list
	int i;//variable that counts loop iterations
	bool result = false;//
	for(i = 0; i < length; i++) {
		//compares the tokens to see if they are equal!
		if(strCompare(token, aoprs[i])) {
			result = true;
			break;
		}
	}

	return result;
}

//checks if the token is a logical operator
bool loperator(char *token) {
	//list of logical operators
	char *loprs[2] = {"AND", "OR"};
	int length = 2;//amount of valid operators
	
	//loop to check if the token is within the list
	int i;//variable that counts loop iterations
	bool result = false;//
	for(i = 0; i < length; i++) {
		//compares the tokens to see if they are equal!
		if(strCompare(token, loprs[i])) {
			result = true;
			break;
		}
	}

	return result;
}

//checks if the token is an operand
bool isoperator(char *token) {
	bool result = false;
	if(loperand(token) || aoperand(token)) {
		result = true;
	}
	
	return result;
}

//checking method exclusively for the NOT operator (since it is the only unary operator 
bool notOp(char* token) {
	
	char nottkn[] = "NOT";
	bool result = false;
	if(strCompare(token, nottkn)) {
		result = true;
		
	}
	
	return result;
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
	//Testing area!
	char  **test = malloc(sizeof(char*));

	//printf("\n");

	
	//checks if the user inputted one argument
	if(argc > 2) {
		printf("error: too may arguments given.\n");
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























