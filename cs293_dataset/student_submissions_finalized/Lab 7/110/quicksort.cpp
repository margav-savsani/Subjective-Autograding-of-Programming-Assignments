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
TrainInfoPerStation* partition(int l,int h,listOfObjects<TrainInfoPerStation *> *stnInfoList){

}
TrainInfoPerStation* randompartition(int l,int h,listOfObjects<TrainInfoPerStation *> *stnInfoList){

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  
  if(stnInfoList == nullptr) return;
  listOfObjects<TrainInfoPerStation *> *f = stnInfoList;
  int size = 0;
  while(stnInfoList!=nullptr){
    stnInfoList=stnInfoList->next;
    size++;
  }
  TrainInfoPerStation *r = randompartition(0,size,f);

}
