#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <ctype.h>

  //queue struct to find lowest levenshtein numbers
struct Queue {
  HashLink* first;
  HashLink* last;
  int size = 0;
  int cap = 5;
}

/**
 * Add to queue
 * Uses hashlinks to implement a queue
 * Adds links up to capacity, then has normal
 * queue behavior (dropping front)
 * Input: pointer to queue and hash link key 
*/
void addQueue(struct Queue* Q, char* word) {
  HashLink* newLink = 0;
    //create new link
  newLink = malloc(sizeof(HashLink));
  newLink->key = word;
  newLink->next = 0;
  
  if (Q->size == 0) {
    Q->first = Q->last = newLink;
    Q->size++;
  } else if (Q->size < Q->cap) {
       //add to back
    last->next = newLink;
    Q->size++;
  } else {
    last->next = newLink;
    newLink = first->next;
      //delete the front
    free(first);
    return;
}

/**
 * Frees queue memory {
 * Input:ptr to queue 
*/
void destroyQ(struct Queue* q) {
  assert(q != 0);
  assert(q->first != 0;

  HashLink* itr = q->first;
  HashLink* garbage = 0;
  while (itr != 0) {
    garbage = itr;
    itr = itr->next;
    free(garbage);
  }
  free(q);
}

/** 
 * Print the queue
 * */
void printQ(struct Queue* q) {
    HashLink* itr = q->first;
    while (itr->next != 0) {
      printf("%s ",itr->key);
      itr = itr->next; 
    }
}

/** Calculate levenshtein number for map
 * input: two words
 * inspired by: https://people.cs.pitt.edu/~kirk/cs1501/Pruhs/Spring2006/assignments/editdistance/Levenshtein%20Distance.htm 
 * */
int levenshtein(char* w1, char* w2) {
  int cost = 0;
    //get the string lengths
  int len1 = strlength(w1);
  int len2 = strlength(w2);
    //temp chars
  char char1;
  char char2;
    //base case: if either is empty, return the other
  if (len1 == 0) {
    return len2;
  } else if (len2 == 0){
    return len1;
  }
    //create a matrix initialized to 0
  int matrix[len1 + 1][len2 + 1];
  for (int i = 0; i <= len1; i++) {
    for (int j = 0; j <= len2; j++) {
      matrix[i][j] = 0;
    }
  }
    //initialize first column and row to 0...n 
  for (int i = 1; i <= len1; i++) {
    matrix[i][0] = 1; 
  }
  
  for (int j = 1; j <= len2; j++) {
    matrix[0][j] = j;
  }
    //compare each character in the strings
  for (int i = 1; i <= len1; i++) {
    char1 = w1[i-1];
    for (int j = 1; j <= len2; j++) {
      char2 = w2[j-1];
      if (char1 == char2) {
        cost = 0;
      } else {
        cost = 1;
      }
      matrix[i][j] = minimum(matrix[i-1][j] + 1, matrix[i][j-1]+1.matrix[i-1][j-1] + cost);
    }
  }
  return matrix[len1][len2];
}



  
  for (int j = 1; j < len2; j++) {
    for (int i = 1; i < len1; i++) {
      if (w1[i] = w2[j]) {
        //cost = 9
      else {
        //cost = 1
      }
      matrix[i,j] =   

/**
 * Convert word to lower case
 * input: an ascii null-terminated word
**/
void lowerCase(char* word) {
    int idx = 0;
    while(word[idx] != '\0') {
        word[idx] = tolower(word[idx]); 
        idx++;
    }
}

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
          //read a word
    word = nextWord(file);
    while(word) {
            //make case insensitive
        lowerCase(word);
            //add the word to the map
        hashMapPut(map,word,1);
           //delete word
        free(word);
          //get next word
        word = nextWord(file);
    }
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    HashMap* map = hashMapNew(1000);
    char* word;
    struct Queue* levenshteinQ = malloc(sizeof(struct Queue));
    int maxVal = 0;
    char garbage;
    int size;
    HashLink* linkptr = 0;
    int valid = 1;

    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");

          //discard what's in the input buffer
        while((garbage = getchar()) != '\n' && garbage != EOF);

        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..
          //get clean word
        size = 0;
        while(inputBuffer[size] != '\n'){
           size++;
        }
        size++;
        word = malloc(sizeof(char) * (size);
        for (int i = 0; i < size; i++) {
          word[i] = inputBuffer[i];
            //clear the buffer
          inputBuffer[i] = 0;
            //validate word
          if (word[i] < 'a' || word[i] > 'z') {
            valid = 0;
          }
        }
        if (!valid) {
          printf("Invalid input. Only letters please.\n");
        } else {
              //check dictionary for word
          if (hashMapContainsKey(map,word)) {
            printf("The inputted word... is spelled correctly\n");
          } else {
            printf("The inputted word... is spelled incorrectly\n");

                //traverse map calculating levenshtein
              for (int i = 0; i < hashMapCapacity(map); i++) {
                linkptr = map->table[i];
                while (linkptr != 0) {
                  linkptr->value = levenshtein(linkptr->key,word);
                }
              }
             
                //add words with lowest levenshtein to queue
            maxVal = 1000000;
            for (int i = 0; i < hashMapCapacity(map); i++) {
                linkptr = map->table[i];
                while (linkptr != 0) {
                  if (linkptr->value < maxVal || levenshteinQ->size < levenshteinQ->cap) {
                    addQueue(levenshteinQ,linkptr->key);
                    if (linkptr->value < maxVal) {
                      maxVal = linkptr->value; 
                    }
                  }
                }
            }

            printf("Did you mean: ");
            printQ(levenshteinQ);
          
          if (strcmp(word, "quit") == 0)
          {
              quit = 1;
          }
      }
        free(word);
    }
    
    hashMapDelete(map);
    return 0;
}
