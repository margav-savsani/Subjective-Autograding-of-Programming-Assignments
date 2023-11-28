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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  srand(0);
  listOfObjects<TrainInfoPerStation *> *counter = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *tail = NULL;
  int size = 0; // calculate the size of list
  while (counter != NULL)
  {
    size++;
    tail = counter;
    counter = counter->next;
  }
  if (size <= 1)
  {
    return; // base case
  }
  int index = rand() % size; // choose random pivot
  listOfObjects<TrainInfoPerStation *> *pivotPtr = stnInfoList;
  for (int i = 0; i < index; i++)
  {
    pivotPtr = pivotPtr->next;
  }
}
