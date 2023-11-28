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

int len_list(listOfObjects<TrainInfoPerStation *> *list){
  int count = 0;
  while(list != nullptr){
    count ++;
    list = list->next;
  }
  return count;
}

int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end){
  TrainInfoPerStation *pivot;
  listOfObjects<TrainInfoPerStation *> *tmp0 = stnInfoList, *tmp1 = nullptr;
  while(tmp0 != nullptr){
    tmp1 = tmp0;
    tmp0 = tmp0->next;
  }
  pivot = tmp1->object;
  tmp0 = stnInfoList;

}

void quick(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end){
  if (start < end){
    int pivot = partition(stnInfoList, start, end);
    quick(stnInfoList, start, pivot - 1);
    quick(stnInfoList, pivot, end);
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  if (stnInfoList == nullptr) return;
  // split the trains on the basis of number of days in a week it runs
  quick(stnInfoList, 0, len_list(stnInfoList) - 1);
}
