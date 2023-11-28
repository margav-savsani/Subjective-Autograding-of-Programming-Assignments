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
#include <ctime>

int size_of_list(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *end) {
  int cnt=1;
  listOfObjects<TrainInfoPerStation *> *tmp;
  tmp = start;
  while(tmp!=end) {
    cnt++;
    tmp = tmp->next;
  }
  return cnt;
}
listOfObjects<TrainInfoPerStation*> rand_pivot(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *end,int size) {
  int rand_val = rand()%(size/4);
  listOfObjects<TrainInfoPerStation *> *tmp = start
  for (int i=0;i<rand_val;i++) {
    tmp = tmp->next;
  }
  return tmp;
}
listOfObjects<TrainInfoPerStation*> rand_partition(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *end,int size) {
  listOfObjects<TrainInfoPerStation *> *pivot = rand_pivot(start,end,size);
}

void my_quick(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *end) {
  if(stnInfoList->next==nullptr) return;
  int size = size_of_list(start,end);
  listOfObjects<TrainInfoPerStation *> *part = rand_partition(start,end,size);
  my_quick(stnInfoList,part);
  my_quick(part->next ,nullptr);
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList) {
  my_quick(stnInfoList,nullptr);
}