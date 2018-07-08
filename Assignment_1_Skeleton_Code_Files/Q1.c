/* CS261- Assignment 1 - Q.1*/
/* Name: Mario Bocaletti
 * Date: 28 June 2018
 * Solution description: This program allocates and frees memory for a struct
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int numStudents = 10;

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
    struct student* students = malloc(sizeof(struct student) * numStudents);     
     /*Return the pointer*/
    return students;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/

    srand(time(0)); //seed random function

    const int minId = 1;
    const int maxId = 10;
    const int minScore = 0;
    const int maxScore = 100;
    int idTemp;
    int scoreTemp;

    for (int i = 0; i < numStudents; i++) {

            //get the id
        idTemp = rand() % (maxId + 1 - minId) + minId;

            //get the score
        scoreTemp = rand() % (maxScore + 1 - minScore) + minScore;

            //add the id to the struct
        students[i].id = idTemp;
        students[i].score = scoreTemp;
    }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
        printf("\n"); 
        for (int i = 0; i < numStudents; i++) {
                
            printf("\n%d\t%d",students[i].id,students[i].score);
        }
}

void summary(struct student* students){
         /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = 100;
    int max = 0;
    int sum = 0;
    double avg = 0;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].score < min) {
            min = students[i].score;
        }
        if (students[i].score > max) {
            max = students[i].score;
        }
        sum += students[i].score;
    }

    avg = (double) sum / numStudents;

    printf("\n\nMinimum score: %d\tMaximum score: %d\t Average score: %lf\n",min,max,avg);
}

void deallocate(struct student* stud){
    free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*Call allocate*/
   stud = allocate();

    /*Call generate*/
   generate(stud);

    /*Call output*/
   output(stud);

    /*Call summary*/
   summary(stud);

    /*Call deallocate*/
   deallocate(stud);
    return 0;
}

