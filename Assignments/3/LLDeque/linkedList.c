#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
        //create sentinel links
    list->frontSentinel = malloc(sizeof(struct Link));
    assert(list->frontSentinel != 0);
    list->backSentinel = malloc(sizeof(struct Link));
    assert(list->backSentinel != 0);
        //connect the sentinels
    list->frontSentinel->next = list->backSentinel;
    list->frontSentinel->prev = 0;
    list->backSentinel->prev = list->frontSentinel;
    list->backSentinel->next = 0;

    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
        //increment size
    list->size++;
        //create the link
    struct Link* newLink = malloc(sizeof(struct Link));
    newLink->value = value;

        //connect the link's prev and next
    newLink->next = link;
    newLink->prev = link->prev;

        //connect the link to the parameter's prev
    link->prev->next = newLink;

        //connect the link to the parameter
    link->prev = newLink;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
        //decrement size
    list->size--;

        //disconnect from prev
    link->prev->next = link->next;

        //disconnect from next
    link->next->prev = link->prev;

        //free memory
    free(link);
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    addLinkBefore(list,list->frontSentinel->next,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    addLinkBefore(list,list->backSentinel,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    removeLink(list,list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    removeLink(list,list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
    return (list->frontSentinel->next == list->backSentinel);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
    struct Link* iterator = list->frontSentinel->next;
    while (iterator != list->backSentinel) {
        printf("%d ",iterator->value);
        iterator = iterator->next;
    }
    printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
   linkedListAddBack(list,value); 
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    int found = 0;
    struct Link* iterator = list->frontSentinel->next;
    while (iterator != list->backSentinel) {
        if (iterator->value == value) {
            found = 1;
        }
        iterator = iterator->next;
    }
    return found;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	struct Link* iterator = list->frontSentinel->next;
    while (iterator != list->backSentinel) {
        if (iterator->value == value) {
           removeLink(list,iterator);
                //break the loop
           iterator = list->backSentinel->prev; 
        }
        iterator = iterator->next;
    }
}
