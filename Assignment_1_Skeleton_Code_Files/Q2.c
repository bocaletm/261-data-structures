/* CS261- Assignment 1 - Q.2*/
/* Name:
 * Date:
 * Solution description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    int* temp;
    /*Swap the addresses stored in the pointer variables a and b*/
    temp = a;
    a = b;
    b = temp;

    /*Decrement the value of integer variable c*/
    c--;

    /*Return c*/
    return c;
}

int main(){
    srand(time(0)); //seed random function
    const int min = 0;
    const int max = 10;

    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand() % (max + 1 - min) + min;
    int y = rand() % (max + 1 - min) + min;
    int z = rand() % (max + 1 - min) + min;

    /*Print the values of x, y and z*/
    printf("\nX = %d\t Y = %d\t Z = %d\n", x,y,z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
    int cval = foo(&x,&y,z);

    /*Print the values of x, y and z*/
    printf("\nX = %d\t Y = %d\t Z = %d\n", x,y,z);

    /*Print the value returned by foo*/
    printf("Value in C is %d\n",cval); 
    
    return 0;
}
    
    


