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

listOfObjects<TrainInfoPerStation*>* 
pivot_selector(listOfObjects<TrainInfoPerStation *> *stnInfoList, int k = 4){
  return stnInfoList;
  

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, int k = 4)
{
  // Put your code here.
  int n = 1;
  listOfObjects<TrainInfoPerStation*>* currNode = stnInfoList;
  while(currNode != NULL){
    currNode = currNode->next;
    n++;
  }

  listOfObjects<TrainInfoPerStation *>* hash[n/k + 1];

  currNode = stnInfoList;
  int index = 0;
  hash[0] = currNode;
  while (currNode != NULL)
  {
    currNode = currNode->next;
    index++;
    if (index % k == 0){
      hash[index/k] = currNode;
    }
  }

}
