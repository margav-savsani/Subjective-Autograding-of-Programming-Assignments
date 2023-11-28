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
void copy(TrainInfoPerStation *y,TrainInfoPerStation *news ){
  y->arrTime=news->arrTime;
  // y->daysOfWeek=news->daysOfWeek;
  y->depTime=news->depTime;
  y->journeyCode = news->journeyCode;
  y->stopSeq=news->stopSeq;



}
void swap(TrainInfoPerStation *y,TrainInfoPerStation *news ){
  TrainInfoPerStation *temp =new TrainInfoPerStation(0,0,0,0);
  copy(temp,y);
  copy(y,news);
  copy(news,temp);
}
listOfObjects<TrainInfoPerStation *> partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,int k){
  return nullptr;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList,int k)
{
  // Put your code here.
}

