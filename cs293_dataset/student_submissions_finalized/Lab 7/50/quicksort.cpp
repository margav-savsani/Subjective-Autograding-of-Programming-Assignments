#include <random>

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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, int k)
{
  listOfObjects<TrainInfoPerStation *> *pivot = stnInfoList, *move = stnInfoList;
  int i = 0;
  for(; move->next != nullptr; i++){
    i++;
  }
  for(int j = 0; j < i; j++){
    
  }
}
