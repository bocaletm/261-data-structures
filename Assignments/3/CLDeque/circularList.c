#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
        //create sentinel
    list->sentinel = malloc(sizeof(struct Link));
    assert(list->sentinel != 0);
        //point sentinel to itself
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
        //set size to zero
    list->size = 0;
    return; 
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
        //create a link
    struct Link* newLink = malloc(sizeof(struct Link));
    assert(newLink != 0);
        //point to null
    newLink->prev = 0;
    newLink->next = 0;
        //set the value
    newLink->value = value;    
    return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
          //create the link
    struct Link* newLink = createLink(value);
        //increment size
    list->size++;
        //point the new link to the parameter link
    newLink->prev = link;
        //point the new link to the parameter's next link
    newLink->next = link->next;
        //point the adjacent links to the new link
    link->next->prev = newLink;
    link->next = newLink;
    newLink = 0;
    return;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
        //decrement list size
    list->size--;
        //disconnect from the list
    link->prev->next = link->next;
    link->next->prev = link->prev;
        //delete the link
    free(link);
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
    struct Link* next = list->sentinel->next;
    struct Link* garbage = 0; 
    while(!circularListIsEmpty(list)){
            //deallocate the link
       garbage = next;
       next = next->next;
       removeLink(list,garbage);
    }
    garbage = 0;
    next = 0;
        //free the list struct
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
        //add a link after the sentinel
    addLinkAfter(list,list->sentinel,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
        //add a link after the sentinel prev
    addLinkAfter(list,list->sentinel->prev,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
    removeLink(list,list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    removeLink(list,list->sentinel->next);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	return (list->sentinel->next == list->sentinel);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
    struct Link* iterator = list->sentinel;
    while(iterator->next != list->sentinel){
             //move to the next link
        iterator = iterator->next;
            //print the value
        printf("%g ",iterator->value);
    }
    printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
    struct Link* temp;
	struct Link* iterator = list->sentinel;
    while(iterator->next != list->sentinel){
            //point to the next link
        iterator = iterator->next;
            //swap the pointers in the previous link
        temp = iterator->prev->prev;
        iterator->prev->prev = iterator->prev->next;
        iterator->prev->next = temp;
    }
}
