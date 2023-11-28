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

#include<cstdlib>

//cannot use an array to copy elements from list to the array and neither
//are we allowed to always choose the last node in the list as pivot as that
//is not the most efficient algorithm

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{  
  int K=4;//take it as four for now for the purupose of completing
  int random = rand();
  int skipper = random%K;

  //Now we have a skipper that has value less than k 
  //So what we can do is now using this skipper we can reach that element and then
  //figure out a way to skip k places at a time.
  //This will give a proper way , but we have to do it in O(k) time.

  listOfObjects<TrainInfoPerStation *> *z= stnInfoList; 
  //k time used here
  for(int i=0;i<K;i++){
    z = z->next;
  } 

}
