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

listOfObjects<TrainInfoPerStation *> *choosePivot(listOfObjects<TrainInfoPerStation *> *stnInfoList, int len){
  int r=0;
  if(len<4){
    r = 1 + rand()%len;
  }else{
    r = 1 + rand()%4;
  }
  
  listOfObjects<TrainInfoPerStation *> *point = stnInfoList;
  
  return point;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.

}
