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

bool lt(TrainInfoPerStation *i1, TrainInfoPerStation *i2)
{
  return i1->arrTime < i2->arrTime;;
}

void Quicksortimpl(listOfObjects<TrainInfoPerStation *> *partStnInfoList, int len)
{

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *&stnInfoList)
{
  // Put your code here.
  int num=0;
  listOfObjects<TrainInfoPerStation *> *cpstnInfoList=new listOfObjects<TrainInfoPerStation *>(stnInfoList->object);
  listOfObjects<TrainInfoPerStation *> *curr=stnInfoList;
  while(curr!=nullptr)
  {
    num++;
    curr=curr->next;
  }
  // int part= num/K;
  // listOfObjects<TrainInfoPerStation *> *headstninfoList=new listOfObjects<TrainInfoPerStation *>[part];

  // curr=stnInfoList;
  // for(int i=0; i<num; i++)
  // {
  //   if(i%part==0)
  //   {
  //     headstninfoList[i/part]=curr;
  //     Quicksortimpl(curr, K);
  //   }
  // }
}
