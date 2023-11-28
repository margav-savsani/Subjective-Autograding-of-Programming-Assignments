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

TrainInfoPerStation* partition(int k = 4, listOfObjects<TrainInfoPerStation*>*start, listOfObjects<TrainInfoPerStation*>*end){
  srand(time(0));
  listOfObjects<TrainInfoPerStation*>* partition;
  if(rand()%2){
    int num = rand()%k;
    partition = start;
    for(int i = 0; i < k; i++){
      partition = partition->next;
    }
    return partition->object;
  }
  else{
    int num = rand()%k;
    partition = end;
    for(int i = 0; i < k; i++){
      partition = partition->prev;
    }
    return partition->object;
  }
  
  return nullptr;
}

bool lessThan(TrainInfoPerStation*a, TrainInfoPerStation*b){
  if(a->depTime < b->depTime) return true;
  else return false;
}

void swap(TrainInfoPerStation*a, TrainInfoPerStation*b){
  TrainInfoPerStation temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation*> *tail= stnInfoList;
  while(tail->next != nullptr)tail = tail->next;
  myquicksort(stnInfoList,tail);
  return;
}

void myquicksort(listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *>*end){
  listOfObjects<TrainInfoPerStation*>* mystart = start, *myend = end;
  if(mystart == myend) return;
  if(mystart->next == myend){
    if(lessThan(mystart->object,myend->object)){
      return;
    }
    else{
      swap(mystart->object,myend->object);
      return;
    }
  }
  TrainInfoPerStation* pivot = partition(4, mystart, myend);
  
  while(true){
    if(mystart->prev == myend || mystart == myend) break;
    while(lessThan(mystart->object, pivot)) mystart= mystart->next;
    while(lessThan(pivot, myend->object)) myend= myend->prev;
    swap(mystart->object, myend->object);
  }
  myquicksort(start,mystart->prev);
  myquicksort(myend->next,end);
  return;
}