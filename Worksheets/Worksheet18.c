#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE int

struct link {									// Single link.
	TYPE value;									// Data contained by this link.
	struct link * next;							// Pointer to the next link.
};

struct listQueue {
	struct link *firstLink;						// Initialize routine sets to zero/NULL.
	struct link *lastLink;						// Initialize routine sets to zero/NULL.
};

void listQueueInit(struct listQueue *q) {
	struct link *lnk = (struct link *) malloc(sizeof(struct link));
	assert(lnk != 0);							// lnk is the sentinel/header.
	lnk->next = 0;								// lnk is pointing to the next link == 0.
	q->firstLink = q->lastLink = lnk;			// At the start, because the queue is empty firstLink == lastLink. 
}

void listQueueAddBack(struct listQueue *q, TYPE e) {
	struct link *newLink = (struct link *) malloc(sizeof(struct link)); // Allocate memory for the new link.
	assert(newLink != 0);						// Make sure the new link was created.
	newLink->value = e;							// Assign passed value to the new link.
	newLink->next = 0;							// Set the new link's pointer to NULL, making it the new last link in the list.
	q->lastLink->next = newLink;				// Update the lastLink pointer so that it points to the next element after new link.
	q->lastLink = newLink;						// Finally, make the new link the last link in the list.
}

TYPE listQueueFront(struct listQueue *q) {
	assert(!listQueueIsEmpty(q));				// Check to see whether or not the list is empty.
	return q->firstLink->next->value;			// Return the value of the first link. (The value after the sentinel)
}

void listQueueRemoveFront(struct listQueue *q) {
	struct link *tempLink = q->firstLink->next;	// Copy the value stored in the first link to a temporary link.
	assert(!linkedListStackIsEmpty(q));			// Check to see whether or not the list is empty.
	if (q->firstLink->next->next == 0) {		// If the list is empty: 
		q->lastLink = q->firstLink;				// Set the lastLink to be equal to the firstLink.
	}											// Else:
	q->firstLink->next = tempLink->next;		// Change the pointer to the next element.
	free(tempLink);								// And free the memory of the deleted link.
}

int listQueueIsEmpty(struct listQueue *q) {
	return q->firstLink == q->lastLink;		// If list is empty, the first and last link will point to the same NULL value.
}


int main() {

	return 0;
}