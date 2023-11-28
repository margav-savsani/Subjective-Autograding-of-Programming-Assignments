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

listOfObjects<TrainInfoPerStation *>* partition(listOfObjects<TrainInfoPerStation *> head, listOfObjects<TrainInfoPerStation *> end,
                       listOfObjects<TrainInfoPerStation *>* newHead,
                       listOfObjects<TrainInfoPerStation *>* newEnd)
{
    listOfObjects<TrainInfoPerStation *> pivot = end;
    listOfObjects<TrainInfoPerStation *> prev = NULL;
 
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot) {
        if (cur->data < pivot->data) {
            // First node that has a value less than the
            // pivot - becomes the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change
            // tail
            if (prev)  prev->next = cur->next;
            struct Node* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
    
}
