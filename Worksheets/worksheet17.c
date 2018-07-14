#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TYPE int

struct link {					// Single link.
	TYPE value;					// Data contained by this link.
	struct link * next;			// Pointer to the next link.
};

struct linkedListStack {
	struct link *firstLink;		// Initialize routine sets to zero/NULL.
};

void linkedListStackInit(struct linkedListStack * s)
{
	s->firstLink = 0;
}

void linkedListStackPush(struct linkedListStack *s, TYPE d) {
	struct link * newLink = (struct link *) malloc(sizeof(struct link));
	assert(newLink != 0);

	/* Fix me */
	newLink->value = d;
	newLink->next = s->firstLink;
	s->firstLink = newLink;
}

TYPE linkedListStackTop(struct linkedListStack *s) {
	/* Fix me */
	assert(!linkedListStackIsEmpty(s));
	return s->firstLink->value;
}

void linkedListStackPop(struct linkedListStack *s) {
	/* Fix me */
	/*Assign the firstLink to a link to be deleted.*/
	struct link * tempLink = s->firstLink;
	/*Check whether or not the linked list is empty.*/
	assert(!linkedListStackIsEmpty(s));
	/*If the list is not empty, change the pointer of the first link.*/
	s->firstLink = tempLink->next;
	/*Free the memory of the deleted link.*/
	free(tempLink);
}

int linkedListStackIsEmpty(struct linkedListStack *s) {
	/* Fix me */
	//assert(s->firstLink != 0);
	return s->firstLink == 0;
}


void linkedListStackFree(struct linkedListStack *s)
{
	while (!linkedListStackIsEmpty(s)) linkedListStackPop(s);
}

int main() {

	return 0;
}
