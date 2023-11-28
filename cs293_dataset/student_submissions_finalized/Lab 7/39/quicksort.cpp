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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  TrainInfoPerStation * pivot = stnInfoList->object;
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *list1 = nullptr;
  listOfObjects<TrainInfoPerStation *> *list2= nullptr;


  while(temp != nullptr){
    if (temp->object->arrTime < pivot->arrTime){
      list1->next->object = temp->object;
    }else {
      list2->next->object = temp->object;
    }
    temp = temp->next;
  }

}

