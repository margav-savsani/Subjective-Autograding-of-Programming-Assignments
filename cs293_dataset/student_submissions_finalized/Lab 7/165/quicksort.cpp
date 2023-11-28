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

// void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
// {
  // Put your code here.
// Returns the last node of the linked list
TrainInfoPerStation * getTail(listOfObjects<TrainInfoPerStation *> *cur){

    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur->object;
}
 
// Partitions the list taking the last element as the pivot
struct Node* partition(listOfObjects<TrainInfoPerStation *>* head, listOfObjects<TrainInfoPerStation *>* end, listOfObjects<TrainInfoPerStation *>** newHead, listOfObjects<TrainInfoPerStation *>** newEnd)
{
    TrainInfoPerStation *pivot = end->object;
    listOfObjects<TrainInfoPerStation *> *prev = NULL, *cur = head, *tail = end;
 
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    TrainInfoPerStation* temp;
    while (cur->object != pivot) {
      
        if (cur->object->daysOfWeek < pivot->daysOfWeek){ //implement later

          temp = cur->object;
        }
        else if(cur->object->depTime < pivot->depTime){

          temp = cur->object;

        }
        cur = cur->next;
    }

    while(tail->object != pivot){
      if (tail->object->daysOfWeek < pivot->daysOfWeek){ //implement later

          temp = tail->object;
      }
      else if(tail->object->depTime < pivot->depTime){

          temp = tail->object;

      }
      tail = tail->prev;
    }
}  
 
    // If the pivot data is the smallest element in the
//     // current list, pivot becomes the head
//     if ((*newHead) == NULL)
//         (*newHead) = pivot;
 
//     // Update newEnd to the current last node
//     (*newEnd) = tail;
 
//     // Return the pivot node
//     return pivot;
// }
 
// // here the sorting happens exclusive of the end node
// struct Node* quickSortRecur(struct Node* head,
//                             struct Node* end)
// {
//     // base condition
//     if (!head || head == end)
//         return head;
 
//     Node *newHead = NULL, *newEnd = NULL;
 
//     // Partition the list, newHead and newEnd will be
//     // updated by the partition function
//     struct Node* pivot
//         = partition(head, end, &newHead, &newEnd);
 
//     // If pivot is the smallest element - no need to recur
//     // for the left part.
//     if (newHead != pivot) {
//         // Set the node before the pivot node as NULL
//         struct Node* tmp = newHead;
//         while (tmp->next != pivot)
//             tmp = tmp->next;
//         tmp->next = NULL;
 
//         // Recur for the list before pivot
//         newHead = quickSortRecur(newHead, tmp);
 
//         // Change next of last node of the left half to
//         // pivot
//         tmp = getTail(newHead);
//         tmp->next = pivot;
//     }
 
//     // Recur for the list after the pivot element
//     pivot->next = quickSortRecur(pivot->next, newEnd);
 
//     return newHead;
// }
 
// // The main function for quick sort. This is a wrapper over
// // recursive function quickSortRecur()
// void quickSort(struct Node** headRef)
// {
//     (*headRef)
//         = quickSortRecur(*headRef, getTail(*headRef));
//     return;
// }

// }
