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

void recursive_quicksort(){

}

listOfObjects<TrainInfoPerStation *> * randomChooser(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *pivot, int n){

  int k = rand() % n;

  for (int i = 0; i < k; i++) {
    pivot = stnInfoList->next;
  }

  return pivot;

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.

  // Count of elements
  int n = 0;

  // Get Tail
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *tail;

  while (temp != nullptr) {
    temp = temp->next;
    n += 1;
  }

  n += 1;

  tail = temp;

  // Get Pivot
  listOfObjects<TrainInfoPerStation *> *pivot;
  pivot = randomChooser(stnInfoList, pivot, n);

  recursive_quicksort();

}
