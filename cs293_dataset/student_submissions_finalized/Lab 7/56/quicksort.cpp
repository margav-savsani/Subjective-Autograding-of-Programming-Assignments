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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, int len)
{
  // Put your code here.

  
}

TrainInfoPerStation* findPivot(int& index, listOfObjects<TrainInfoPerStation *>* stnInfoList){
  int temp = 0;
}

void Partition(listOfObjects<TrainInfoPerStation *>* stnInfoList, listOfObjects<TrainInfoPerStation *>* pivot){
  listOfObjects<TrainInfoPerStation*>* point1 = stnInfoList; 
  listOfObjects<TrainInfoPerStation*>* point2 = stnInfoList;
  while(point2 != nullptr){
    if(isGreaterThan(pivot, point2)){
      point2 = point2->next;
    }
    else{
      
    }
  }

}

bool isGreaterThan(listOfObjects<TrainInfoPerStation *>* t1, listOfObjects<TrainInfoPerStation *>* t2){
  int i;
  for(i = 0; i < 7; i++){
    if(t1->object->daysOfWeek[i]){
      break;
    }
  }
  int j;
  for(j = 0; j < 7; j++){
    if(t2->object->daysOfWeek[j]){
      break;
    }
  }
  if(i > j){
    return true;
  }
  if(t1->object->arrTime > t2->object->arrTime){
    return true;
  }
  return false;
}




