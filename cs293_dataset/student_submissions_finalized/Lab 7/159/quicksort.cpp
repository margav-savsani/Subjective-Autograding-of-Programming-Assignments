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
listOfObjects<TrainInfoPerStation *> getTail(listOfObjects<TrainInfoPerStation *> *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return *cur;
}
listOfObjects<TrainInfoPerStation *> partition(listOfObjects<TrainInfoPerStation *> *head, listOfObjects<TrainInfoPerStation *> *end,
                       listOfObjects<TrainInfoPerStation *> *newHead,
                       listOfObjects<TrainInfoPerStation *> *newEnd)
{
    listOfObjects<TrainInfoPerStation *> *pivot = end;
    listOfObjects<TrainInfoPerStation *> *prev = NULL; 
    listOfObjects<TrainInfoPerStation *> *cur = head;
    listOfObjects<TrainInfoPerStation *> *tail = pivot;
 
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot) {
        if (cur->object < pivot->object) {
            // First node that has a value less than the
            // pivot - becomes the new head
            if (newHead == NULL)
                newHead = cur;
 
            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change
            // tail
            if (prev)
                prev->next = cur->next;
            listOfObjects<TrainInfoPerStation *> *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    // If the pivot data is the smallest element in the
    // current list, pivot becomes the head
    if (newHead == NULL)
        newHead= pivot;
 
    // Update newEnd to the current last node
    newEnd = tail;
 
    // Return the pivot node
    return *pivot;
}
 
// here the sorting happens exclusive of the end node
listOfObjects<TrainInfoPerStation *> recursivequicksort(listOfObjects<TrainInfoPerStation *> *head,
                            listOfObjects<TrainInfoPerStation *> *end)
{
    // base condition
    if (!head || head == end)
        return *head;
 
    listOfObjects<TrainInfoPerStation *> *newHead = NULL;
    listOfObjects<TrainInfoPerStation *> *newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be
    // updated by the partition function
    listOfObjects<TrainInfoPerStation *> pivot
        = partition(head, end, newHead, newEnd);
 
    // If pivot is the smallest element - no need to recur
    // for the left part.
    if (newHead->object != pivot.object) {
        // Set the node before the pivot node as NULL
        listOfObjects<TrainInfoPerStation *> *tmp = newHead;
        while (tmp->next->object != pivot.object)
            tmp = tmp->next;
        tmp->next = NULL;
 
        // Recur for the list before pivot
        *newHead = recursivequicksort(newHead, tmp);
 
        // Change next of last node of the left half to
        // pivot
        *tmp = getTail(newHead);
        *tmp->next = pivot;
    }
 
    // Recur for the list after the pivot element
    *pivot.next = recursivequicksort(pivot.next, newEnd);
 
    return *newHead;
}
 
// The main function for quick sort. This is a wrapper over
// recursive function recursivequicksort()
void quickSort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    (*stnInfoList)
        = recursivequicksort(stnInfoList, &getTail(stnInfoList));
    return;
}