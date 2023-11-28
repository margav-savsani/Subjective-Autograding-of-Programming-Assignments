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

int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  return -1;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  if(stnInfoList == nullptr)
  {
    return;
  }
  else
  {
    int pi = partition(stnInfoList);
    Quicksort(stnInfoList);
    Quicksort(&stnInfoList[pi]);
  }

  
  // Put your code here.
}
