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

#define K 5

bool lessThan(TrainInfoPerStation* train1, TrainInfoPerStation* train2){
  int day_train1, day_train2;
  for (int i = 6; i >= 0; i--){
    if(train1->daysOfWeek[i]){
      day_train1 = i;
    }

    if(train2->daysOfWeek[i]){
      day_train2 = i;
    }
  }

  return (2400*day_train1 + train1->depTime < 2400*day_train2 + train2->depTime);
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  if(stnInfoList == nullptr)
    return;
  
  int count = 1;
  listOfObjects<TrainInfoPerStation*> *currNode = stnInfoList;
  while(currNode->next != nullptr){
    count++;
    currNode = currNode->next;
  }

  listOfObjects<TrainInfoPerStation*> *lastNode = currNode;

  if(count < K){
    //Implement insertion sort
  }

  else{
    listOfObjects<TrainInfoPerStation*> *partitions[int(count / K)];
    int index = 0;
    currNode = stnInfoList;
    //Make Partitions
  }  
}
