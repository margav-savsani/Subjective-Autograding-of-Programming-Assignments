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

int total =1;

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
   TrainInfoPerStation* extra;
   listOfObjects<TrainInfoPerStation *> *pivot;
   listOfObjects<TrainInfoPerStation *> *start = stnInfoList;
   listOfObjects<TrainInfoPerStation *> *end = stnInfoList;
  if(stnInfoList != nullptr){
  
    while(end->next != nullptr){
      end = end->next;
      total++;
    }
    while(true){
    while(!(end->object->arrTime <= pivot->object->arrTime)){
      end = end->prev;
    }
    while(!(start->object->arrTime >= pivot->object->arrTime)){
      start = start->next;
    }
    if(start == end->prev){
      extra = start->object;
      start->object = end->object;
      end->object = extra;
    }
    else{
      break;
    }
    }
    Quicksort(end);
    Quicksort(end->next);
  }
}

void pivot_fun(){

}

