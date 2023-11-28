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
  listOfObjects<TrainInfoPerStation*> *dummy = nullptr;
  while (true)
  {
    for(int i=0;i<7;i++){
      if(stnInfoList->object->daysOfWeek[i]){
        if(dummy==nullptr) dummy=stnInfoList;
        else dummy->next=stnInfoList;
      }
    }
  }
  

}
