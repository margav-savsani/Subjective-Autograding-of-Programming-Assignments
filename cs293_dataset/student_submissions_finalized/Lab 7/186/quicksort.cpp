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

listOfObjects<TrainInfoPerStation *> *lastNode(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
  while(currNode->next != nullptr){
    currNode = currNode->next;
  }
  return currNode;
}

listOfObjects<TrainInfoPerStation *> *pivot(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  return nullptr;
}

void quickSort(listOfObjects<TrainInfoPerStation *> *head, listOfObjects<TrainInfoPerStation *> *tail){
  listOfObjects<TrainInfoPerStation *> *pivot = tail;
  if(head!= nullptr){
    listOfObjects<TrainInfoPerStation *> *partitionNode = partition(head,tail);
    quickSort(head,partitionNode->prev);
    quickSort(partitionNode->next,tail);
  }

}

listOfObjects<TrainInfoPerStation *> *partition(listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right){

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *tail = lastNode(stnInfoList);
  
  quickSort(stnInfoList,tail);

}






