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

listOfObjects<TrainInfoPerStation *> **random_gen(listOfObjects<TrainInfoPerStation *> *stnInfoList) {
  listOfObjects<TrainInfoPerStation *>* i;
  int count = 0;
  while(i != nullptr){
    i = i->next;
    count++;
  }
  int k=4;
  int ratio;
  if(count%k == 0) ratio = count/k;
  else ratio = count/k + 1;
  listOfObjects<TrainInfoPerStation *> *random_gen[ratio];
  int x=0;
  listOfObjects<TrainInfoPerStation *> *currentNode = stnInfoList;
  for(int j=0;j<count;j++){
    if(j%k == 0){
      random_gen[x] = currentNode;
      x++;
    }
    j++;
    currentNode = currentNode->next;
  }
  return random_gen;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.

}
