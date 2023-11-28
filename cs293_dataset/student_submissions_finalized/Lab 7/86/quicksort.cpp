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

listOfObjects<TrainInfoPerStation *> *Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  if(stnInfoList == nullptr) return;
  listOfObjects<TrainInfoPerStation *> *pivot;
  while(stnInfoList->next != nullptr)
  {
    stnInfoList = stnInfoList->next;
  }
  pivot = stnInfoList; //First assuming pivot to be the last node of doubly linked list.
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *pivot = Partition(stnInfoList);
  Quicksort(pivot->next);
  // Put your code here.
}
