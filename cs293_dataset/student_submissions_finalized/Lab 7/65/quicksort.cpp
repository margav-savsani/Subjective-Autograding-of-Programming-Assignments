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
  listOfObjects<TrainInfoPerStation *> *dummy=stnInfoList;
  TrainInfoPerStation *pivot=nullptr;
  int size=0;
  while(stnInfoList!=nullptr){
    l++;
    stnInfoList=stnInfoList->next;
  }
  int m=randint()%l;
  int i=0;
  while(i<m){
    i++;
    stnInfoList=stnInfoList->next;
  }
  pivot=stnInfoList->object;
  listOfObjects<TrainInfoPerStation *> *firstpart =nullptr;
  listOfObjects<TrainInfoPerStation *> *secondpart=nullptr;




}
