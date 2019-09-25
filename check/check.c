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

//checks if the token is an operator
bool isoperator(char *token) {
	bool result = false;
	if(loperator(token) || aoperator(token)) {
		result = true;
	}
	
	return result;
}

//checks if the token is an operand
bool isoperand(char* token) {
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
	//printf("Amt tkns: %d\n", *tknCount);
	//printf("Strlng: %d\n", strlength);	
	
	char **tokens = malloc(*tknCount * sizeof(char*));
	
	//printf("made char**\n");	
	
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
		
		//printf("a token succeeded\n");
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
		
		//printf("last token succeeded\n");
	}
	/*	
	printf("\nPrinting Tokens:\n");
	//print tokens for testing
	int i; //for for-loop
	for(i = 0; i < *tknCount; i++) {
		printf("\"%s\"\n", tokens[i]);
	}
	
	printf("---------------------------------------------------\n");	
	*/
	return tokens;
}
//*

//evaluates the first operand (or not) to see if it is valid
int opd1(char *token, int *set, int *atype, int exp) {
	
	int err = 0;
	if(aoperand(token) ||  loperand(token)) {
		if(aoperand(token)) {
			*atype = 1;
		} else if(loperand(token)) {
			*atype = 2;
		}
		//printf("Error: Parse error in expression %d: \n\"%s\"\n", exp, token);
		//store the operand type and move on to the operator
		*set = 2;
	} else if(notOp(token)) {
		//check for NOT in next token,
		err = 1;
		*set = 3;
	} else if(loperator(token) || aoperator(token)) {
		//if operator, unexpected operator, move on
		printf("Error: Parse error in expression %d: unexpected operator\n\"%s\"\n", exp, token);
		*set = 3;
		err = 1;
	} else {
		//unknown identifier
		printf("Error: Parse error in expression %d: unknown identifier\n\"%s\"\n", exp, token);
		*set = 1;
		err = 1;
	}
	return err;//returns 1 if there was an error
}

//evaluates if the operator is valid
int opr(char *token, char *prev, int *set, int *atype, int exp) {
	
	int err = 0;
	if(aoperator(token) || loperator(token)) {
		//check if the operand was the correct type
		if((*atype == 1) && loperator(token)) {
			//type mismatch error on previous operand
			printf("Error: Parse error in expression %d: type mismatch in previous token\n\"%s\"\n", exp, prev);
			*atype = 2;
			err = 1;
			
		} else if ((*atype == 2) && aoperator(token)){
			//type mismatch error on previous operand
			printf("Error: Parse error in expression %d: type mismatch in previous token\n\"%s\"\n", exp, prev);
			*atype = 1;
			err = 1;
		}
		*set = 3;
		//increment expressoin counters if first operator
		//do not increment if not
	} else if(aoperand(token) || loperand(token)) {
		//unexpected operand
		printf("Error: Parse error in expression %d: unexpected operand\n\"%s\"\n", exp, token);
		//CHANGE EXPECTED TYPE OF OPERATOR
		err = 1;
		*set = 2;
	} else if(notOp(token)) {
		//unexpected operator
		printf("Error: Parse error in expression %d: unexpected operator\n\"%s\"\n", exp, token);
		err = 1;
		*set = 3;
	
	} else {
		//unknown operator,
		printf("Error: Parse error in expression %d: unknown operator\n\"%s\"\n", exp, token);
		err = 1;
		*set = 3;
	} 
	
	return err;//return 1 if there was an error
}

//evaluates the last operand to see if it is valid
int opd2(char *token, int *set, int *atype, int exp) {
	
	int err = 0;	
	if(aoperand(token) || loperand(token)) {
		if((*atype == 1) && loperand(token)) {
			//type mismatch
			printf("Error: Parse error in expression %d: type mismatch\n\"%s\"\n", exp, token);
			err = 1;
		} else if((*atype == 2) && aoperand(token)){
			//type mismatch
			printf("Error: Parse error in expression %d: type mismatch\n\"%s\"\n", exp, token);
			err = 1;
		}
		*set = 4;
	} else if(aoperator(token) || loperator(token) || notOp) {
		//unexpected operator
		printf("Error: Parse error in expression %d: unexpected operator\n\"%s\"\n", exp, token);
		*set = 3;
		err = 1;
	} else {
		//unknown operand
		printf("Error: Parse error in expression %d: unknown operand\n\"%s\"\n", exp, token);
		*set = 4;
		err = 1;
	}
	
	return err;//returns 1 if there was an error
}

//run when there are extra tokens when the expression should have finished.
int unEnded(char *token, int *set) {
	if(aoperator(token) || loperator(token)) {
		*set = 2;
	} else if(aoperand || loperand) {
		*set = 1;
	} else { 
		*set = 1;
	}
	
	return 1;
}


//Evaluates an expresssion to see if the expression has errors or not
//returns expression type, 2 if no type! 
int evalExp(char* expression[], int exLength, int exNum, char* exp) {
	
	//check for scan errors!
	if(exLength == 1 && strCompare(expression[0], "")) {
		printf("Error: Scan error in expression 0: incomplete expression\n%s\n", expression[0]);
		
		//if scan error, the expression has no type
		return 0;
	}
	
	//values and pointers to be passed through
	//set the type of token to be analyzed
	int s = 1;
	int *set = &s;
	

	//measures when the expression is the first one
	bool first = true;
	bool firstOp = true;

	bool exEnd = true;
	
	//determines the type of the previous tokens
	int a = 0;
	int *atype = &a;
	
	//determines type of whole expression
	int type = 0;
	
	//determines if there was an error
	int err = 0;
	
	//NEED A LOOP TO GO THROUGH TOKENS OF EXPRESSION
	int i = 0;
	for(i = 0; i < exLength; i++) {
		switch(*set) {
			case 1: 
				err = err + opd1(expression[i], set, atype, exNum);
				//determines expression type
				if(firstOp && *set == 3) {

					firstOp = false;
					if(aoperator(expression[i])) {
						type = 1;
					} else if(loperand(expression[i]) || notOp(expression[i])) {
						type = 2;
					}
				}
				
				break;
				
			case 2:
				if(i <= 0) {
					printf("WILL SEG FAULT!\n");
				}
				
				err = err + opr(expression[i], expression[i- 1], set, atype, exNum);
				
				//determines expression type
				if(firstOp && *set == 3) {

					firstOp = false;
					if(aoperator(expression[i])) {
						type = 1;
					} else if(loperand(expression[i]) || notOp(expression[i])) {
						type = 2;
					}
				}	
				
				
				break;
				
			case 3:
				err = err + opd2(expression[i], set, atype, exNum);
				//indicates when the "first" expression has been reached
				if(*set == 4) {
					first = false;
				}
				break;
				
			case 4:
				err = err + unEnded(expression[i], set);
				if(exEnd) {
					printf("Error: Parse error in expression %d: expression wasn't ended\n\"%s\"\n", exNum, exp);
					exEnd = false;
				}
				break;
				
		}
		
		
	}
	
	//printf("Error: Parse error in expression %d: \n\"%s\"\n", exp, token);
	//if first expression was not reached, there had to be missing operators!
	if(first) {
		if(*set == 3) {
			printf("Error: Parse error in expression %d: missing operand\n\"%s\"\n", exNum, exp);
			printf("Error: Parse error in expression %d: incomplete expression\n\"%s\"\n", exNum, exp);
			
			
		} else if(*set == 2) {
			printf("Error: Parse error in expression %d: missing operator\n\"%s\"\n", exNum, exp);
			printf("Error: Parse error in expression %d: incomplete expression\n\"%s\"\n", exNum, exp);
		}
		
	}
	if(!err) {
		printf("OK!\n");
	}
	
		
	return type;
	
	
}


int main(int argc, char* argv[]) {
	//Testing area!
	char  *test[] = {"a", "+", "2"};
	char *exptest = "a + 2";
	int testLength = 3;
	
	int a = evalExp(test, testLength, 1, exptest);
	
	/*
	printf("%d\n", isoperator("+"));
	printf("%d\n", isoperator("-"));
	printf("%d\n", isoperator("/"));
	printf("%d\n", isoperator("*"));
	printf("%d\n", isoperator("3"));
	printf("%d\n", isoperator("AND"));
	printf("%d\n", isoperator("OR"));
	printf("%d\n", isoperator("NOT"));
	*/
	//printf("\n");

	
	//checks if the user inputted one argument
	if(argc > 2) {
		printf("error: too may arguments given.\n");
		return 0;
	} else if(argc < 2) {
		printf("error: no arguments given.\n");
		return 0;
	}
	
	//keeps track of how many arithmetic expressions and logical expressions there are
	int aexpressions = 0;
	int lexpressions = 0;
	int result = 0;
	
	//keeps track of the tokens 	
	int *tknCount = (int*)malloc(sizeof(int));
	int i = 0;//counter for all for loops

	char **expressions  = tokenizer(argv[1], ';', tknCount);
	
	
	//keeps track of the operators and operands within each token
	//using an array of pointers
	char ***opers = (char***)malloc((*tknCount) * sizeof(char**));
	int **tknCounters = (int**)malloc((*tknCount) * sizeof(int*));
	
	for(i = 0; i < *tknCount; i++) {
		tknCounters[i] = (int*)malloc(sizeof(int*));
	}
	
	//stores all of the lengths of the individual expressions
	i = 0;
	for(i = 0; i < *tknCount; i++) {
		opers[i] = tokenizer(expressions[i], ' ', tknCounters[i]);
	}
	
	//iterates through each expression and retrievers the errror messages along with the type of the expression
	for(i = 0; i < *tknCount; i++) {
		result = evalExp(opers[i], *tknCounters[i], i, expressions[i]);
		if(result == 1) {
			aexpressions++;
		} else if(result == 2) {
			lexpressions++;
		}
		result = 0;
	}


	
	//free all elements of expression double pointer
	i = 0;//reset for loop counter to 0
	for(i = 0; i < *tknCount; i++) {
		free(expressions[i]);
	}
	free(expressions);
	
	//free opers triple array
	for(i = 0; i < *tknCount; i++) {
		int j = 0;
		for(j = 0; j < *tknCounters[i]; j++) {
			free(opers[i][j]);
		}
		free(opers[i]);
	}
	free(opers);
		
	free(tknCount);
	
	return 0;
}























