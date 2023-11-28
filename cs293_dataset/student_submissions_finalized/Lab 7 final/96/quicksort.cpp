#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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

void swap(TrainInfoPerStation *a,TrainInfoPerStation *b){
  TrainInfoPerStation t=*a;
  *a=*b;
  *b=t;
}

listOfObjects<TrainInfoPerStation *> *choosePivot(listOfObjects<TrainInfoPerStation *> *head , listOfObjects<TrainInfoPerStation *> *tail){
  int n=1;
  listOfObjects<TrainInfoPerStation *> *curr=head;
  while(curr!=tail){
    curr=curr->next;
    n++;
  }
  if(n==1) return head;
  int m=rand()%n;
  curr=head;
  for(int i=0;i<m;i++){
    curr=curr->next;
  }
  return curr;
}

listOfObjects<TrainInfoPerStation *>* partition(listOfObjects<TrainInfoPerStation *> *head , listOfObjects<TrainInfoPerStation *> *tail){
  listOfObjects<TrainInfoPerStation *> *pivot=choosePivot(head,tail);
  
  bool *week=pivot->object->daysOfWeek;
  int w1=0;
  for(;w1<7;w1++){
    if (week[w1]==true) break;
  }
  int arr1=pivot->object->arrTime;
  int dep1=pivot->object->arrTime;

  swap(pivot->object,tail->object);

  listOfObjects<TrainInfoPerStation *> *i=head->prev;
  for(listOfObjects<TrainInfoPerStation *> *j=head;j!=tail;j=j->next){
    bool *week2=j->object->daysOfWeek;
    int w2=0;
    for(;w2<7;w2++){
      if (week2[w2]==true) break;
    }
    int arr2=j->object->arrTime;
    int dep2=j->object->arrTime;
    if(w2<w1 || (w2==w1 && (arr2<arr1 || (arr2==arr1 && dep2<dep1)))){
      i = (i == NULL)? head : i->next; 
      swap((i->object), (j->object)); 
    }
  }
  i = (i == NULL)? head : i->next;
  swap((i->object), (tail->object)); 
  return i;
}

void recQuicksort(listOfObjects<TrainInfoPerStation *> *head , listOfObjects<TrainInfoPerStation *> *tail){
  if (tail != NULL && head != tail && head != tail->next) 
    { 
        listOfObjects<TrainInfoPerStation *> *p = partition(head, tail); 
        recQuicksort(head, p->prev); 
        recQuicksort(p->next, tail); 
    }
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{ 
  listOfObjects<TrainInfoPerStation *> *tail = stnInfoList;
  while(tail->next != nullptr){
    tail=tail->next;
  }
  recQuicksort(stnInfoList,tail);
  return;
}


#endif
