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

listOfObjects<TrainInfoPerStation *> * pivot(listOfObjects<TrainInfoPerStation *> * start,listOfObjects<TrainInfoPerStation *> *end){
  return pivot;
}


void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *end=stnInfoList;
  while(end->next!=NULL)end=end->next;
  listOfObjects<TrainInfoPerStation *> *piv=pivot(stnInfoList,end);

}
