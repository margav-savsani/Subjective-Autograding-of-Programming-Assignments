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
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *last = new listOfObjects<TrainInfoPerStation *>(nullptr);
  listOfObjects<TrainInfoPerStation *> *pivot = new listOfObjects<TrainInfoPerStation*>(nullptr);
  int len = 1;
  listOfObjects<TrainInfoPerStation *> *node = stnInfoList;
  while (node != nullptr)
  {
    len++;
    last = node;
    node = node->next;
  }

  int pivotpos = len*rand()/RAND_MAX;
  for (int i = 0; i < pivotpos; i++)
  {
    if (pivot == nullptr)
    {
      pivot = stnInfoList;
    }
    pivot = pivot->next;
  }
  
  listOfObjects<TrainInfoPerStation *> *left = new listOfObjects<TrainInfoPerStation *>(nullptr);
  listOfObjects<TrainInfoPerStation *> *right = new listOfObjects<TrainInfoPerStation *>(nullptr);
  for (int i = 0; i < len; i++)
  {
    if (left == nullptr)
    {
      left = stnInfoList;
    }
    
  }
  
}
