#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#pragma warning(disable:4996)

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
            // make lower case
            word[length] = tolower(c);
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
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
         
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    char* word;
        //open file to read
    FILE* file = fopen(fileName,"r"); 
          //read a word
    word = nextWord(file);
    while(word) {
                //increase the number of instances
        if (hashMapContainsKey(map,word)) {
            (*hashMapGet(map,word))++;
        } else {
                //add the word to the map
            hashMapPut(map,word,1);
        }
            //delete word
        free(word);
            //get next word
        word = nextWord(file);
    }
    fclose(file);
        //print the concordance
    printf("\nConcordance:");
    printf("\n----------------------------------");
    HashLink* linkptr = 0;
    for (int i = 0; i < hashMapCapacity(map); i++) {
        linkptr = map->table[i];
        printf("\n\tBucket %d: ",i);
        while (linkptr != 0) {
          printf("-> (%s, %d) ",linkptr->key,linkptr->value);
          linkptr = linkptr->next;
        }
    }
    printf("\n----------------------------------\n");
    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}
