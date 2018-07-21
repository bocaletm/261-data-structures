/* CS261- Assignment 1 - Q. 0*/
/* Name: Mario Bocaletti
 * Date: 28 June 2018
 * Solution description: This program gets a random number 1-10 and prints it using pointers; the program also manipulates and prints the pointer addresses
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){
    
     /*Print the value and address of the integer pointed to by iptr*/
     printf("The value of the integer pointed to by iptr is: %d\n\n",*iptr);          
     
     /*Increment the value of the integer pointed to by iptr by 5*/
     iptr += 5;

     /*Print the address of iptr itself*/
     printf("The address of iptr itself is: %p\n\n",iptr);
}


void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/
     printf("The value of the integer pointed to by jptr is: %d\n\n",*jptr);  

     /*Decrement jptr by 1*/
     jptr--; 

     /*Print the address of jptr itself*/
     printf("The address of jptr itself is: %p\n\n",jptr);
}


int main(){
    
        /*Declare an integer x and initialize it randomly to a value in [0,10]*/
    srand(time(0)); //seed random function

    int x;
    const int min = 1;
    const int max = 10;

    //set x to random number
    x = rand() % (max + 1 - min) + min;

    /*Print the value and address of x*/
    printf("\nRandom Number: %d  Address: %p\n\n",x,&x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*Print the value of x*/
    printf("Random Number: %d\n\n",x);

/*The value of x is not different than 
 * the value printed at first
 * because the function modified the 
 * pointer and not the value in that address*/
    
    /*Call fooB() with the address of x*/
    fooB(&x);

    /*Print the value and address of x*/
    printf("Random Number: %d  Address: %p\n\n",x,&x); 
    
/*The value of x is not different than 
 * the value printed at first
 * because the function modified the 
 * pointer and not the value in that address
 *
 * The address is still the same because the function 
 * only modified its local copy of the pointer. We
 * did not pass a pointer to pointer.*/
    return 0;
}


