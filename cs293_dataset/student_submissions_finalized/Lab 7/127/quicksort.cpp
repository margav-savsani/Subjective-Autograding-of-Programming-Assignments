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

listOfObjects<TrainInfoPerStation*>* Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation*> *endStn)
{
  if(stnInfoList==nullptr) return nullptr;
  if(stnInfoList->next==nullptr) return stnInfoList;

  listOfObjects<TrainInfoPerStation*>* head=stnInfoList;
  listOfObjects<TrainInfoPerStation*>* cur_node=stnInfoList;
  listOfObjects<TrainInfoPerStation*>* temp_node;
  
  while(cur_node->next!=endStn) {
    if(((cur_node->next)->object)->arrTime<(head->object)->arrTime) {
      temp_node=cur_node->next;
      cur_node->next=(cur_node->next)->next;
      temp_node->next=head;
      head=temp_node;
    }
    cur_node=cur_node->next;
  }

  head=Quicksort(head, stnInfoList);
  stnInfoList->next=Quicksort(stnInfoList->next, endStn);

  return head;


  // Put your code here.
}
