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

//O(n)
/*int numElements(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  int count=0;
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  while(temp!=nullptr){
    count++;
    temp=temp->next;
  }
  return count;
}

listOfObjects<TrainInfoPerStation *> selectPivot(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  int len = numElements(stnInfoList);
  int random_num = rand()%len;
  int middle = len/2;
  if(random_num>middle){
    
  }
}*/

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  int random_num = rand()%NUM_CHARS;
  //divide into k arrays
  
}
