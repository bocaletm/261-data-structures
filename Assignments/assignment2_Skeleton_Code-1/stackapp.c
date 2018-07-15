/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	assert(s != 0);

	char check = '0';
	int balanced = 0;
		//make stack for each type
	DynArr* parens = newDynArr(5);
	DynArr* curlyBrace = newDynArr(5);
	DynArr* strBrace = newDynArr(5);

	while (check != '\0') {
			//get the next character
		check = nextChar(s);

			//put characters on stacks
		if (check == '(' || check == ')') {
			pushDynArr(parens, check);
		} else if (check == '{' || check == '}') {
			pushDynArr(curlyBrace, check);
		} else if (check == '[' || check == ']') {
			pushDynArr(strBrace, check);
		}
	}

		//check the parentheses
	while (!isEmptyDynArr(parens)) {
		check = topDynArr(parens);
		popDynArr(parens);
		if (check == '(') {
			balanced++;
		} else {
			balanced--;
		}
	}

	if (balanced != 0) {
		return 1;
	}

		//check the curly braces
	while (!isEmptyDynArr(curlyBrace)) {
		check = topDynArr(curlyBrace);
		popDynArr(curlyBrace);
		if (check == '{') {
			balanced++;
		}
		else {
			balanced--;
		}
	}

	if (balanced != 0) {
		return 1;
	}

	//check the brackets
	while (!isEmptyDynArr(strBrace)) {
		check = topDynArr(strBrace);
		popDynArr(strBrace);
		if (check == '[') {
			balanced++;
		}
		else {
			balanced--;
		}
	}
	
	if (balanced != 0) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

