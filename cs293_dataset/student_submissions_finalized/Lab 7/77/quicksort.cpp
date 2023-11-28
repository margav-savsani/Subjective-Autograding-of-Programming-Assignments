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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  //Expansion of list


  //Length of the List
  listOfObjects<TrainInfoPerStation *> *currNode= stnInfoList ;
  listOfObjects<TrainInfoPerStation *> *prevNode =nullptr;
  while(currNode->next!=nullptr){
    for(int i=0;i<7;i++){
      if( currNode->object->daysOfWeek[i]){
        if(prevNode==nullptr){prevNode=new listOfObjects<TrainInfoPerStation *>(currNode)}
      }
    }
  } 
  //Find pivot

  //Remove pivot from list

  //Divide
}
