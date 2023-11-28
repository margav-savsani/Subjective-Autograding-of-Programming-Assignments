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

listOfObjects<TrainInfoPerStation *> *getpivot(listOfObjects<TrainInfoPerStation *> *stnInfoList,int n)
{
  int k=rand()%n;
  listOfObjects<TrainInfoPerStation *> *sample;
  sample=stnInfoList;
  for(int i=0;i<k;i++)
    sample=sample->next;
  return sample;
}
listOfObjects<TrainInfoPerStation *> *getlast(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *sample=stnInfoList;
  while(sample->next != nullptr)
    sample=sample->next;
  return sample;
}
void partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation *> *pivot)
{
  if (stnInfoList == getlast(stnInfoList))
    return;
  else
  {
    
  }
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
}
