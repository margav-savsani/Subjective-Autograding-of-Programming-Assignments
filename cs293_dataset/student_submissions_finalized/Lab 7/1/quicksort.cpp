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

bool less_than(TrainInfoPerStation *lhs, TrainInfoPerStation *rhs){
  for(int i = 0; i < 7; i++){
    if(lhs->daysOfWeek[i] && !rhs->daysOfWeek[i]) return true;
    else if(!lhs->daysOfWeek[i] && rhs->daysOfWeek[i]) return false;
    else if(lhs->daysOfWeek[i] && rhs->daysOfWeek[i]) break;
  }
  return lhs->depTime <= rhs->depTime;
}

void partition(listOfObjects<TrainInfoPerStation *> *curr_list){
  listOfObjects<TrainInfoPerStation *> *temp = curr_list;
  while(temp->next != NULL){temp= temp->next;}
  TrainInfoPerStation pivot = *(temp->object);
  //now pivot points to the address of the last info class.
  listOfObjects<TrainInfoPerStation *> *ptr1 = curr_list, *ptr2 = curr_list;
  while(less_than(ptr1->object, &pivot)){
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
    if(ptr1 == NULL) return;
  }
  while(!less_than(ptr2->object, &pivot)){
    ptr2 = ptr2->next;
    if(ptr2 == NULL) return;
  }
  
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
}
