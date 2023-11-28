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

listOfObjects<TrainInfoPerStation *> **RandomGen(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *s = stnInfoList;
  int size = 0;
  while (s != nullptr)
  {
    s = s->next;
    size++;
  }
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
}
