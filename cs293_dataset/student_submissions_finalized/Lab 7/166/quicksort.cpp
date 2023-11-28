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

void swap(listOfObjects<TrainInfoPerStation *> *l1,listOfObjects<TrainInfoPerStation *> *l2){
  if(l1->prev == null && l2->next == nullptr){

  }
  
}

listOfObjects<TrainInfoPerStation *> g(listOfObjects<TrainInfoPerStation *> *pi,listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *fin){

}

void sort(listOfObjects<TrainInfoPerStation *> *s,listOfObjects<TrainInfoPerStation *> *f){
  listOfObjects<TrainInfoPerStation *> *pivot;
  if(s != f){
    listOfObjects<TrainInfoPerStation *> *te= g(pivot,s,f);
    sort(s,te);
    sort(te->next,f);
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
  listOfObjects<TrainInfoPerStation *> *finish;
  listOfObjects<TrainInfoPerStation *> *trial;
  trial=stnInfoList;
  while(trial->next !=nullptr){
    trial=trial->next;
  }
  finish=trial;
  trial=stnInfoList;
  sort(stnInfoList,finish);

}
