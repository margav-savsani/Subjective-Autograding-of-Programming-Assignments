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

const int K=4;

listOfObjects<TrainInfoPerStation*>* choosePivot(listOfObjects<TrainInfoPerStation*> *head){
  int index = rand()%K;
  while(index-- && head->next != nullptr) head = head->next;

  return head;
}

template <typename T>
void swapElements(listOfObjects<T> *one, listOfObjects <T>* two){
  if(one == nullptr || two == nullptr) return;

  listOfObjects<T>* temp = one->next;
  one->next = two->next;
  if(two->next != nullptr) two->next->prev = one;
  two->next = temp;
  if(temp != nullptr) temp->prev = two;

  temp = one->prev;
  one->prev = two->prev;
  if(two->prev != nullptr) two->prev->next = one;
  two->prev = temp;
  if(temp != nullptr) temp->next = two;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation*> *pivot=choosePivot(stnInfoList);  
}
