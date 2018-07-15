/*
 *Name: Mario Bocaletti
 *Date: 7/15/18
 */

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArrayAmort.h"


int main(int argc, char *argv[]){
	
	int capacity = atoi(argv[1]);	
	int pushes = atoi(argv[2]);
    int costUnits = 0;

    DynArr* test = newDynArr(capacity);

    for (int i = 0; i < pushes; i++) {
        costUnits += pushDynArr(test,'0');
    }
    
    printf("The cost is: %d",costUnits);

	return 0;	
}


