struct dLink {
   TYPE value;
   struct dLink * next;
   struct dLink * prev;
};
struct linkedList {
   struct dLink * frontSentinel;
   struct dLink * backSentinel;
   int size;
};
/* the following functions were written in earlier lessons */
void linkedlistInit (struct linkedList *lst);
void linkedListFree (struct linkedList *lst);
void _addLink (struct linkedList * lst, struct dLink * lnk, TYPE e);
void _removeLink (struct linkedList * lst, struct dLink * lnk);   
void linkedListAdd (struct linkedList * lst, TYPE e)
   { _addLink(lst, lst->frontSentinel->next, e); }
/* you must write the following */
int linkedListContains (struct linkedList *lst, TYPE e) {
    int found = 0;
    dLink* iterator = lst->frontSentinel;
    while (iterator != lst->backSentinel) {
      if (iterator->next->value == e) {
            found = 1;
      }
      iterator = iterator->next;
    }
    return found;
}
void linkedListRemove (struct linkedList *lst, TYPE e) {
    dLink* iterator = lst->frontSentinel;
    dLink* garbage = 0;
    while (iterator != lst->backSentinel) {
      if (iterator->next->value == e) {
                //disconnect the link
           iterator->next->next->prev = iterator;
           iterator->next = iterator->next->next;
                //clean up
           free(garbage);
           garbage = 0;
      }
      iterator = iterator->next;
    }
    iterator = 0;
    return;
}
//1. What were the algorithmic complexities of the methods addLink and removeLink that you wrote back in linked list for Deque?
//          O(1) for add O(1) for remove
//2. Given your answer to the previous question, what are the algorithmic complexities of the three principal Bag operations? 
//          O(n) for contains and remove
//          O(1) for add
