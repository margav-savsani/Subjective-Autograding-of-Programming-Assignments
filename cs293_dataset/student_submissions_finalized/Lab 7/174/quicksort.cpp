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
TrainInfoPerStation* random(listOfObjects<TrainInfoPerStation *> *stnInfoList){

}
listOfObjects<TrainInfoPerStation *>* partition(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  TrainInfoPerStation* b=random(stnInfoList);
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *>* a;
  a=partition(stnInfoList);
  Quicksort(a->prev);
  Quicksort(a->next);
}
