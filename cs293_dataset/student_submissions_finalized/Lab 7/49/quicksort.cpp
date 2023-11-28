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

bool greater(TrainInfoPerStation stn1 , TrainInfoPerStation stn2){
  int k = -1, j = -1;
  for(int i = 0;i<7;i++){
    if(stn1.daysOfWeek[i])k = i;
    if(stn2.daysOfWeek[i])j = i;
  }
  if(k>j) return true;
  else{
    return stn1.depTime > stn2.depTime;
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *currList = stnInfoList;
  int k = 0;
  while(currList->next!=nullptr){
    k++;
    currList = currList->next;
  }
  

}
