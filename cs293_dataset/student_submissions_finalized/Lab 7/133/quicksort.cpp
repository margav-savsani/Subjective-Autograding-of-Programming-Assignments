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
bool priority(TrainInfoPerStation* info1, TrainInfoPerStation* info2){
  bool b;
  for(int i=0;i<7;i++){
    if(info1->daysOfWeek[i] != info2->daysOfWeek[i]) return info1->daysOfWeek[i] > info2->daysOfWeek[i];
  }
  return info1->arrTime < info2->arrTime;
}

listOfObjects<TrainInfoPerStation*> *pivot_func(){return NULL;}

listOfObjects<TrainInfoPerStation*> *partition(listOfObjects<TrainInfoPerStation*> *start,listOfObjects<TrainInfoPerStation*> *end){
  listOfObjects<TrainInfoPerStation*> *pivot = pivot_func();
  listOfObjects<TrainInfoPerStation*> *initial = start;
  listOfObjects<TrainInfoPerStation*> *final = end;
  while(true){
    while(priority(pivot->object,initial->object) && priority(initial->object,pivot->object)){
      if(priority(pivot->object,initial->object)) break;
      initial = initial->next;
    }
    while(priority(pivot->object,initial->object) && priority(initial->object,pivot->object)){
      if(priority(final->object,pivot->object)) break;
      final = final->prev;
    }
    if(priority(final->object,initial->object)){
      
    }
  } 
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation*> *eof_list)
{
  if(stnInfoList != NULL){
    listOfObjects<TrainInfoPerStation *> *divider = partition(stnInfoList,NULL);
    Quicksort(stnInfoList,divider);
    Quicksort(divider,NULL);
  }
  // Put your code here.
}
