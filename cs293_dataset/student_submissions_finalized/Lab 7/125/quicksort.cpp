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
int K = 4;

//function to choose the pivot
listOfObjects<TrainInfoPerStation *> * choosePivot(listOfObjects<TrainInfoPerStation *> *stnInfoList){

}


void partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *pivot){

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *pivot;
  partition(stnInfoList, pivot);
  Quicksort(stnInfoList);
  Quicksort(pivot);
}
