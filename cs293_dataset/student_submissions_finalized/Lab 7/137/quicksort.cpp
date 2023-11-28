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

listOfObjects<TrainInfoPerStation *> * findEnd(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  while(temp->next != NULL)
  {
    temp = temp->next;
  }
  return temp;
}

listOfObjects<TrainInfoPerStation *> * partition(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  TrainInfoPerStation *pivot = stnInfoList->object;
  TrainInfoPerStation *start = stnInfoList->object;
  TrainInfoPerStation *end = findEnd(stnInfoList);
  while()
}
