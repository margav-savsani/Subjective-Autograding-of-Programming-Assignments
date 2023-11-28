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
#include<ctime>
listOfObjects<TrainInfoPerStation *> *pivot(listOfObjects<TrainInfoPerStation *> *stn){
  listOfObjects<TrainInfoPerStation *> *a = stn;
  int count = 0;
  while(a != NULL){
    a = a->next;
    count++;
  }
  int c = count*(rand()/RAND_MAX);
  return &stn[c];
}
listOfObjects<TrainInfoPerStation *> partition(listOfObjects<TrainInfoPerStation *> *stn,int start, int finish){
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

}
