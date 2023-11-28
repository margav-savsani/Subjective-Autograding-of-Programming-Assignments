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

TrainInfoPerStation * pivot(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  //Find the pivot in a given linked list
  //TODO
  return stnInfoList;
}

listOfObjects<TrainInfoPerStation *> * partition(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  listOfObjects<TrainInfoPerStation *> *nextToChange = stnInfoList;
  TrainInfoPerStation * pivotInfo = pivot(stnInfoList);
  while(stnInfoList != nullptr){ // TODO: Fix this
    if(stnInfoList->object < pivot){
      std::swap(stnInfoList->object, nextToChange->object);
      nextToChange = nextToChange->next;
    }
  }
  return nextToChange->prev;
}

listOfObjects<TrainInfoPerStation *> * QuickSortRecursive(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  // Returns the last element in the sorted list
  if(stnInfoList->next == nullptr){return;}
  listOfObjects<TrainInfoPerStation *> * partition = partition(stnInfoList);
  return
}


void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.

  
}
