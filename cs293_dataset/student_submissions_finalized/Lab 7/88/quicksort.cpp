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
bool isLessThan(listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right){
  for(int i=0;i<7;i++){
    if(left->object->daysOfWeek[i] && !(right->object->daysOfWeek[i])) return true;
    else if(!(left->object->daysOfWeek[i]) && right->object->daysOfWeek[i]) return false;
  }
  if(left->object->arrTime<right->object->arrTime) return true;
  else return false;
}

void swap(listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right){
  TrainInfoPerStation *temp = right->object;
  right->object = left->object;
  left->object = temp;
}

listOfObjects<TrainInfoPerStation *> *Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *pivot){
  listOfObjects<TrainInfoPerStation *> *left=stnInfoList;
  listOfObjects<TrainInfoPerStation *> *right=stnInfoList;
  while(right->next!=nullptr) {
    right=right->next;
  }
  while(true){
    while(left!=right && isLessThan(left,pivot)){
      left=left->next;
    }
    while(left!=right && !isLessThan(right,pivot)){
      right=right->prev;
    }
    if(left!=right){
      swap(left,right);
    }
    else break;
  }
  //cout<<*(left->object)<<endl;
  if(left->prev!=nullptr) left->prev->next=nullptr;
  return left;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  if(stnInfoList==nullptr) return;
  listOfObjects<TrainInfoPerStation *> *pivot=new listOfObjects<TrainInfoPerStation *>(stnInfoList->object);
  listOfObjects<TrainInfoPerStation *> *right=Partition(stnInfoList, pivot);
  if(right==stnInfoList){
    Quicksort(stnInfoList->next);
    if(stnInfoList->next!=nullptr) stnInfoList->next->prev=stnInfoList;
  }
  else{
    Quicksort(stnInfoList);
    Quicksort(right);
    right->prev->next=right; 
  }
}
