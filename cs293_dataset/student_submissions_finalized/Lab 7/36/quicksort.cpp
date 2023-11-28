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

void swap(listOfObjects<TrainInfoPerStation *> *a,listOfObjects<TrainInfoPerStation *> *b) {
  TrainInfoPerStation t=*a->object;
  *a->object=*b->object;
  *b->object=t;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
}
