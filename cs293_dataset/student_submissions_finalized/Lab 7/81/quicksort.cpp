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
bool isLessthan(TrainInfoPerStation* a,TrainInfoPerStation* b){
  for(int i=0;i<7;i++){
    if(a->daysOfWeek[i]||b->daysOfWeek[i]){
      if(!(a->daysOfWeek[i]&&b->daysOfWeek[i])){
        if(a->daysOfWeek[i]){return true;}
        else return false;
      }
      else{
        if(max(a->arrTime,a->depTime)<max(b->arrTime,b->depTime)){return true;}
        else return false;
      }
    }
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
}
