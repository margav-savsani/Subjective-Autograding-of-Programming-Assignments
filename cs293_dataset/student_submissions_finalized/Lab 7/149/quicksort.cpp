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

TrainInfoPerStation *partition(){}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
}
void shuffle(TrainInfoPerStation *a, TrainInfoPerStation *b){
  TrainInfoPerStation c = *a;
  *a = *b;
  *b = c;
}
