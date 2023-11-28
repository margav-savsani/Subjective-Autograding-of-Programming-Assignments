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

  int k=4;
  int a=0;
  while ((stnInfoList!=NULL))
  {
    a++;
    stnInfoList=stnInfoList->next;
  }
  


}
void Partition(listOfObjects<TrainInfoPerStation*>*stnInfo)
{

}

void random(listOfObjects<TrainInfoPerStation*> *stn)
{
  int a= rand(k);
}