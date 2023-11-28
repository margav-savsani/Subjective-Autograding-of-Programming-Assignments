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

void swap(listOfObjects<TrainInfoPerStation *>* a , listOfObjects<TrainInfoPerStation *>* b){
  listOfObjects<TrainInfoPerStation *> a1 = *a;
  listOfObjects<TrainInfoPerStation *> b1 = *b;

}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *first = stnInfoList;
  int n = 1;
  while(first->next != nullptr){
    n++;
    first = first->next;
  }

  
}
