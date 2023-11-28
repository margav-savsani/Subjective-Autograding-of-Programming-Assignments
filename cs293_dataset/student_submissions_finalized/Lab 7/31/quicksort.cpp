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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  
}

void partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int i)
{
  // Put your code here.
  bool k = false;
  listOfObjects<TrainInfoPerStation*> *node1 = stnInfoList;
  listOfObjects<TrainInfoPerStation*> *node2 = stnInfoList;
  while(node2->next!=NULL){
    node2 = node2->next;
  }

  while(true){
    while((node2->(TrainInfoPerStation->daysOfWeek[i])!=true){
      node2 = node2->prev;
      if(node2 = node1->prev){
        k = true;
      }
    }
    while((node1->(TrainInfoPerStation->daysOfWeek[i])!=false){
      node1 = node1->next;
      if(node1 = node2->next){
        k = true;
      }
    }
    if(k==false){
      if(node1->prev!=NULL){
        (node1->prev)->next = node2;
        node2->prev = node1->prev;
      }
      node2->next = node1->next;
      if(node1->next!=NULL){
        (node1->next)->prev = node2;
      }
    }
    else
      return;
  }


}

void Quicksort2(){}
