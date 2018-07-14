// Worksheet 18: Linked List Queue, pointer to Tail

// In Preparation: Read Chapters 6 and 7 to learn more about the Stack and Queue data types.
// If you have not done so already, you should do Worksheet 17 to learn about the basic features
// of a linked list.

// One problem with the linked list stack is that it only permits rapid access to the front of
// the collection. This was no problem for the stack operations described in Worksheet 17, but
// would present a difficulty if we tried to implement a queue, where elements were inserted at
// one end and removed from the other.

// A solution to this problem is to maintain two references into the collection of links. As before,
// the data field firstLink refers to the first link in the sequence. But now a second data field
// named lastLink will refer to the final link in the sequence:

 

// To reduce the size of the image the fields in the links have been omitted, replaced with the
// graphic arrow. Both the firstLink and lastLink fields can be null if a list is empty. Removing
// a data field from the front is the same as before, with the additional requirement that when
// the last value is removed and the list becomes empty the variable lastLink must also be set to null. 

 
// Because we have a link to the back, it is easy to add a new value to the end of the list.

 
 
// We will add another variation to our container. A sentinel is a special link, one that does not
// contain a value. The sentinel is used to mark either the beginning or end of a chain of links.
// In our case we will use a sentinel at the front. This is sometimes termed a list header. The
// presence of the sentinel makes it easier to address special cases. For example, the list of links
// is never actually empty, even when it is logically empty, since there is always at least one link.
// A new value is inserted after the end.



// Values are removed from the front, as with the stack. But because of the sentinel, the element removed
// will be the element right after the sentinel. Make sure that when you remove a value from the collection
// you free the memory for the associated link.

// You should complete the following skeleton code for the ListQueue. The structures have been written
// for you, as well as the initialization routine. The function isEmpty must determine whether or not
// the collection has any elements. What property characterizes an empty queue? 


// (You need to submit the answers of the following questions)

// 1.	Draw a picture showing the values of the various data fields in an instance of ListQueue when it is
// first created.

// 2.	Draw a picture showing what it looks like after one element has been inserted.

// 3.	Based on the previous two drawings, can you determine what feature you can use to tell if a list is
// empty?
//
//			If the firstLink is equal to the lastLink, the list is empty
//
// 4.	Draw a picture showing what it looks like after two elements have been inserted.

// 5.	What is the algorithmic complexity of each of the queue operations?
// 				listQueueAddBack -> O(1)
// 				listQueueFront -> O(1)
// 				listQueueRemoveFront -> O(1)
// 				listQueueIsEmpty -> O(1)


// 6.	How difficult would it be to write the method addFront(newValue) that inserts a new element into the 
// front of the collection? A container that supports adding values at either and, but removal from only one
// side, is sometimes termed a scroll.

//				Not very difficult: 
//					1. create a new link 
//					2. point the new link's next pointer to the first link 
//					3. point the firstLink pointer to the new link

// 7.	Explain why removing the value from the back would be difficult for this container. What would be the
// algorithmic complexity of the removeLast operation?
//					Gettingthe pointer to the previous-to-last link requires traversing all the links
//					The complexity would be O(n)

 
struct link {
   TYPE value;
   struct link * next;
};

struct listQueue {
   struct link *firstLink;
   struct link *lastLink;
};

void listQueueInit (struct listQueue *q) {
   struct link *lnk = (struct link *) malloc(sizeof(struct link));
   assert(lnk != 0); /* lnk is the sentinel */
   lnk->next = 0;
   q->firstLink = q->lastLink = lnk;
}

void listQueueAddBack (struct listQueue *q, TYPE e) {
  		//create a new link
	struct link * newLink = (struct link *) malloc(sizeof(struct link));
    assert (newLink != 0);
  		
  		//set new link values
  	newLink->next = 0;
  	newLink->value = e;
  
  		//connect link to the queue
  	q->lastLink->next = newLink;
  	
  		//point lastLink to the new link
	q->lastLink = newLink;
  
  		//set newLink to null
  	newLink = 0;
}

TYPE listQueueFront (struct listQueue *q) {
	return q->firstLink->value;
}


void listQueueRemoveFront (struct listQueue *q) {
  		//keep track of the struct to delete
  	struct link* garbage = q->firstLink;
  
  		//disconnect the head
	q->firstLink = q->firstLink->next;
  
  		//delete the head
  	free(garbage);
  	garbage = 0;
}

int listQueueIsEmpty (struct listQueue *q) {
	if (q->firstLink == q->lastLink) {
      return 1;
    } else {
      return 0;
    }

}

