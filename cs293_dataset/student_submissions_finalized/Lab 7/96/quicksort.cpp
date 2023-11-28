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

void partition(listOfObjects<TrainInfoPerStation *> *head , listOfObjects<TrainInfoPerStation *> *tail){
  listOfObjects<TrainInfoPerStation *> *pivot;
}

void recQuicksort(listOfObjects<TrainInfoPerStation *> *head , listOfObjects<TrainInfoPerStation *> *tail){
  if (tail != NULL && head != tail && head != tail->next) 
    { 
        listOfObjects<TrainInfoPerStation *> *p = partition(head, tail); 
        _quickSort(head, p->prev); 
        _quickSort(p->next, tail); 
    }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *tail = stnInfoList;
  while(tail->next != nullptr){
    tail=tail->next;
  }
  recQuicksort(stnInfoList,tail);
}
