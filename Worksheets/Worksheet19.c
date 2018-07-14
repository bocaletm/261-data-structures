#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE int

struct dlink {									// Single link.
	TYPE value;									// Data contained by this link.
	struct dlink * next;						// Pointer to the next link.
	struct dlink * prev;						// Pointer to the previous link.
};

struct linkedList {
	int size;									// Number of elements in the list.
	struct dlink * frontSentinel;				// Initialize routine sets to zero/NULL.
	struct dlink * backSentinel;				// Initialize routine sets to zero/NULL.
};

/* these functions are written for you */
void LinkedListInit(struct linkedList *q) {
	q->frontSentinel = (struct dlink *) malloc(sizeof(struct dlink));
	assert(q->frontSentinel != 0);
	q->backSentinel = (struct dlink *) malloc(sizeof(struct dlink));
	assert(q->backSentinel);
	q->frontSentinel->next = q->backSentinel;
	q->backSentinel->prev = q->frontSentinel;
	q->size = 0;
}

void linkedListFree(struct linkedList *q) {
	while (q->size > 0)
		linkedListRemoveFront(q);
	free(q->frontSentinel);
	free(q->backSentinel);
	q->frontSentinel = q->backSentinel = NULL;
}

void LinkedListAddFront(struct linkedList *q, TYPE e)
{
	_addLink(q, q->frontSentinel->next, e);
}

void LinkedListAddback(struct linkedList *q, TYPE e)
{
	_addLink(q, q->backSentinel, e);
}

void linkedListRemoveFront(struct linkedList *q) {
	assert(!linkedListIsEmpty(q));
	_removeLink(q, q->frontSentinel->next);
}

void LinkedListRemoveBack(struct linkedList *q) {
	assert(!linkedListIsEmpty(q));
	_removeLink(q, q->backSentinel->prev);
}

int LinkedListIsEmpty(struct linkedList *q) {
	return q->size == 0;
}

/********************************************************************
*						_addLink									*
* Parameters: struct linkedList * q, struct dlink *lnk, TYPE e(int)	*
* - struct linkedList *q: Pointer to the linked list deque.			*
* - struct dlink *lnk: Pointer to a single link in the list.		*
* - TYPE e: An integer to be assigned to the newly created link.	*
* Description: _addLink places a new link before the given location	*
* of struct dlink *lnk (second parameter) and increments the size	*
* of the deque by one.												*
********************************************************************/
void _addLink(struct linkedList *q, struct dlink *lnk, TYPE e) {
	struct dlink * newLink = (struct dlink *) malloc(sizeof(struct dlink));	// Allocate memory for the new link.
	assert(newLink != 0);						// Make sure that the new link was created.
	newLink->value = e;							// Assign the passed value of e to the value of the new link.
	newLink->prev = lnk->prev;					// Update the new link's prev point to match the passed location's prev pointer.
	newLink->next = lnk;						// Update the new link's next pointer to the passed location, since it now proceeds it.
	lnk->prev->next = newLink;					// Update the next pointer of the link that once proceeded lnk, but now proceeds newLink.
	lnk->prev = newLink;						// Update lnk's prev point to newLink, since newLink now proceeds lnk.
	q->size++;									// Increment the size of the list by 1, since a new link has been added.
}

/********************************************************************
*							_removeLink								*
* Parameters: struct linkedList *q, struct dlink *lnk				*
* - struct linkedList *q: Pointer to the linked list deque.			*
* - struct dlink *lnk: Pointer to a single link in the list, which	*
* will be removed from the deque.									*
* Description: When called, this function will remove the target	*
* link from the deque (the second parameter) and decrement the size	*
* of the deque by 1.												*
********************************************************************/
void _removeLink(struct linkedList *q, struct dlink *lnk) {
	lnk->next->prev = lnk->prev;				// Update the previous pointer of the previous link.
	lnk->prev->next = lnk->next;				// Update the next pointer of the next link.
	free(lnk);									// Free the memory of the link being removed.
	q->size--;									// Decrement the size of the list by 1, since a link has been removed.
}
/********************************************************************
*						LinkedListFront								*
* Parameters: struct linkedList *q									*
* - struct linkedList *q: Pointer to the linked list deque.			*
* Description: This function returns the value of the first link in	*
* the deque.														*

********************************************************************/
TYPE LinkedListFront(struct linkedList *q) {
	assert(!LinkedListIsEmpty(q));				// Make sure the list isn't empty.
	return q->frontSentinel->next->value;		// Return the value stored in the link.
}

/********************************************************************
*						LinkedListBack								*
* Parameters: struct linkedList *q									*
* - struct linkedList *q: Pointer to the linked list deque.			*
* Description: This function returns the value of the last link in	*
* the deque.														*
********************************************************************/
TYPE LinkedListBack(struct linkedList *q) {
	assert(!LinkedListIsEmpty(q));				// Make sure the list isn't empty.
	return q->frontSentinel->prev->value;		// Return the value stored in the link.
}
