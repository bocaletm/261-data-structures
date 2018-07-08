/* CS261- Assignment 1 - Q.3*/
/* Name: Mario Bocaletti
 * Date: 7/8/18
 * Solution description: This program converts strings to camel case
 */

#include <stdio.h>
#include <stdlib.h>



char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
    return ch - 32;
}

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
    return ch + 32;
}

int stringLength(char s[]) {
    int count = 0;
   /*Return the length of the string*/
    while (s[count] != '\0') {
        count++;
    }
    count--;
    return count;
}

void collapse(char* word, int iter){
    while (word[iter] != '\0') {
        word[iter] = word[iter+1];
        iter++;   
    }
}

void camelCase(char* word){
    int length = stringLength(word);
    int newLength = length;
    int iter = 0;
    
	/*Convert to camelCase*/
    for (int i = 0; i < length; i++) {
          if (word[i] == '_'){
                word[i] = toUpperCase(word[i+1]);
                iter = (i+1);
                while (word[iter] != '\0') {
                    word[iter] = word[iter+1];
                    iter++;
                }
                newLength--;
          }          
    }
}

int main() {

	/*Read the string from the keyboard*/
    char word[25];
    char cleanWord[25];
    int newLength = 0;
    int underscore = 0;
    int doubleDiv = 0;

    printf("\nEnter a word <= 25 characters, and I will convert to camelCase: ");
    fgets(word,25,stdin);
    int length = stringLength(word);
    
    printf("\nOriginal Word: %s",word);

    /*validate string*/
    for (int i = 0; i < length; i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            cleanWord[newLength] = toLowerCase(word[i]);
            newLength++;
            doubleDiv = 0;
        } else if (word[i] >= 'a' && word[i] <= 'z') {
            cleanWord[newLength] = word[i];
            newLength++;
            doubleDiv = 0;
        } else if (!doubleDiv) { 
            cleanWord[newLength] = '_';
            underscore++;
            newLength++;
            doubleDiv++;
        }
    }
    /*remove leading and ending underscore*/
    if (cleanWord[0] == '_') {
        collapse(cleanWord,0);
        newLength--;
    } 
    if (cleanWord[newLength - 1] == '_') {
        underscore = 0;
    }        
    /*null terminate string*/
    cleanWord[newLength] = '\0';

	/*Call camelCase*/
    if (underscore && newLength) {
        printf("\nIntermediate Word: %s",cleanWord);
	    camelCase(cleanWord);
    	/*Print the new string*/
	    printf("\n\nCamel Case Word: %s\n",cleanWord);
    } else {
        printf("\ninvalid input string");
    }
	return 0;
}

