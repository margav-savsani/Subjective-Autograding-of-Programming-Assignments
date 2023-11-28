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

listOfObjects<TrainInfoPerStation>* Quick_sort(listOfObjects<TrainInfoPerStation> *start, listOfObjects<TrainInfoPerStation> *end, int total_stn, int K){
  int max_space = total_stn/K;
  /*
    the code for pivot.
  */
  //  lets say pivot is selected and it is first index;
  TrainInfoPerStation pivot = start->object;
  int day = -1;
  for(int i = 0; i < 7; i++){
    if(pivot.daysOfWeek[i])day = i;break;
  }
};

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  // int total_stn = 0;
  // while(stnInfoList != nullptr){
  //   total_stn++;
  //   stnInfoList = stnInfoList->next;
  // }
  // int K = total_stn/2;
  // bool isInt = false;
  // int extra_space = total_stn/K;
  // if((total_stn*1.0)/K - int(total_stn/K) == 0)isInt = true;

  listOfObjects<TrainInfoPerStation> *expanded;
  TrainInfoPerStation *dummy = new TrainInfoPerStation(-1,0,-1,-1);
  expanded = new listOfObjects<TrainInfoPerStation>(*dummy);
  listOfObjects<TrainInfoPerStation> *curr = expanded;
  while(stnInfoList != nullptr){
    for(int i = 0; i < 7; i++){
      if(stnInfoList->object->daysOfWeek[i]){
        TrainInfoPerStation* temp = new TrainInfoPerStation(stnInfoList->object->journeyCode, stnInfoList->object->stopSeq, stnInfoList->object->arrTime, stnInfoList->object->depTime);
        temp->setDayOfWeek(i);
        expanded->next = new listOfObjects<TrainInfoPerStation>(*temp);
        expanded->next->prev = expanded;
        expanded = expanded->next;
      }
    }
    stnInfoList = stnInfoList->next;
  }
  expanded = curr;
  int total_stn = 0;
  while(expanded != nullptr){
    total_stn++;
    expanded = expanded->next;
  }
  int K = 2;
  Quick_sort(curr, expanded, total_stn, K);
}
