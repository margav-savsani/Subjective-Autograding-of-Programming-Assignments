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
  //note that depTime of each node of the list should be >0 (basically, not -1)
  //TrainInfoPerStation* pivot=getPivot(stnInfoList);

}

TrainInfoPerStation* getPivot(listOfObjects<TrainInfoPerStation*> *stnInfoList){
  return stnInfoList->object;
}

bool lessThan(TrainInfoPerStation* a,TrainInfoPerStation* b){
  for(int i=0;i<7;i++){
    if(a->daysOfWeek[i] && !b->daysOfWeek[i]){
      return true;
    }
    else if(!a->daysOfWeek[i] && b->daysOfWeek[i]){
      return false;
    }
    else if(a->daysOfWeek[i] && b->daysOfWeek[i]){
      if(a->depTime < b->depTime){
        return true;
      }
      else{
        return false;
      }
    }
    else{
      continue;
    }
  }
  return true;
}