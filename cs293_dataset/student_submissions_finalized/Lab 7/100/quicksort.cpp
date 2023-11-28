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

int length(listOfObjects<TrainInfoPerStation *> *node){
  listOfObjects<TrainInfoPerStation *> *curr=node;
  if(curr==nullptr)return 0;
  return 1+length(curr->next);
}

bool isLessThan(TrainInfoPerStation *larg,TrainInfoPerStation *rarg){
  for(int i=0;i<7;i++){
    if(larg->daysOfWeek[i]==1 && rarg->daysOfWeek[i]==0)return true;
    if(larg->daysOfWeek[i]==0 && rarg->daysOfWeek[i]==1)return false;
    if(larg->daysOfWeek[i]==1 && rarg->daysOfWeek[i]==1){
      if(larg->arrTime <= rarg->arrTime==0)return true;
      else return false;
    }
  }
  return true;
}

void exchangeValues(listOfObjects<TrainInfoPerStation *> *first,listOfObjects<TrainInfoPerStation *> *second){
  listOfObjects<TrainInfoPerStation *> *temp;
  temp->object=first->object;
  first->object=second->object;
  second->object=temp->object;
}

listOfObjects<TrainInfoPerStation *> *choosePivot(listOfObjects<TrainInfoPerStation *> *head , int n){
  int k;

    listOfObjects<TrainInfoPerStation *> *pivot=head;

    k=rand()%n;

    for (int i=0; i < k; i++)
    {
        pivot=pivot->next;
    }
  return pivot;
}

listOfObjects<TrainInfoPerStation *> *partition(listOfObjects<TrainInfoPerStation *> *head,listOfObjects<TrainInfoPerStation *> *tail){
  int n=length(head);
  listOfObjects<TrainInfoPerStation *> *pivot=choosePivot(head,n);
  TrainInfoPerStation *x = pivot->object; 
  
    // similar to i = l-1 for array implementation 
    listOfObjects<TrainInfoPerStation *> *i = head->prev; 
  
    // Similar to "for (int j = l; j <= h- 1; j++)" 
    for (listOfObjects<TrainInfoPerStation *> *j = head; j != tail; j = j->next) 
    { 
        if (isLessThan(j->object,x)) 
        { 
            // Similar to i++ for array 
            i = (i == NULL)? head : i->next; 
  
            exchangeValues(i, j); 
        } 
    } 
    i = (i == NULL)? head : i->next; // Similar to i++ 
    exchangeValues(i, tail); 
    return i;

}

void recurrQuickSort(listOfObjects<TrainInfoPerStation *> *head,listOfObjects<TrainInfoPerStation *> *tail){
  if(head==tail)return;
  listOfObjects<TrainInfoPerStation *> *temp=partition(head,tail);
  recurrQuickSort(head,temp);
  recurrQuickSort(temp->next,tail);

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *last=stnInfoList;
  while(last!=nullptr){
    if(last->next==nullptr)break;
    else last=last->next;
  }
  if(last==nullptr)return;
  recurrQuickSort(stnInfoList,last);
}
