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
  int size=0;
  while(stnInfoList!=nullptr){
    size++;
    stnInfoList=stnInfoList->next;
  }
  TrainInfoPerStation *array[size];
  for(int i=0;i<size;i++){
    array[i]=stnInfoList->object;
    stnInfoList=stnInfoList->next;
  }
  // Put your code here.
}
