#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif
listOfObjects<TrainInfoPerStation *> partition(listOfObjects<TrainInfoPerStation *> *head, listOfObjects<TrainInfoPerStation *> *end,listOfObjects<TrainInfoPerStation *> newHead,listOfObjects<TrainInfoPerStation *>*newEnd){

    listOfObjects<TrainInfoPerStation *> *pivot = end;
    listOfObjects<TrainInfoPerStation *> *prev = NULL, *curr = head, *tail = pivot;
    while (curr != pivot) {
        if (curr->data < pivot->data) 
            if ((*newHead) == NULL)
                (*newHead) = curr;
            prev = curr;
            curr = curr->next;
        }
        else {
            if (prev)
                prev->next = curr->next;
            listOfObjects<TrainInfoPerStation *> *tmp = curr->next;
            curr->next = NULL;
            tail->next = curr;
            tail = curr;
            curr = tmp;
        }
    }
    if ((*newHead) == NULL)
        (*newHead) = pivot;
 
    (*newEnd) = tail;
 
    // Return the pivot node
    return pivot;
}

struct Node* quickSortRecur(struct Node* head, struct Node* end)
{
    if (!head || head == end)
        return head;
 
    Node *newHead = NULL, *newEnd = NULL;
    struct Node* pivot = partition(head, end, &newHead, &newEnd);
    if (newHead != pivot) {
        struct Node* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);
 
    return newHead;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

        (*headRef)= quickSortRecur(*headRef, getTail(*headRef));
        return;
    
}
