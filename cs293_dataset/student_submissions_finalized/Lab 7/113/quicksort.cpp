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

void Quicksort(listOfObjects<TrainInfoPerStation *> *&stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *dummy=new listOfObjects<TrainInfoPerStation *>(stnInfoList->object);
  listOfObjects<TrainInfoPerStation *> *dummytraversing=dummy;
  while (stnInfoList->next != NULL){
    dummytraversing->next = new listOfObjects<TrainInfoPerStation *>(stnInfoList->next->object);
    dummytraversing->next->prev = dummytraversing;
    dummytraversing = dummytraversing->next;
    stnInfoList=stnInfoList->next;
  }

  stnInfoList = dummy;
  dummytraversing=dummy;
  
}
