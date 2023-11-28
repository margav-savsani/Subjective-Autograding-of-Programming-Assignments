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
TrainInfoPerStation** preprocessing(listOfObjects<TrainInfoPerStation *> *stnInfoList){

  int length=0;
  listOfObjects<TrainInfoPerStation*>*t1=stnInfoList;
  while(t1!=NULL){
    length=length+1;
     t1=t1->next;
  }
  TrainInfoPerStation* s[length];
  listOfObjects<TrainInfoPerStation*>*t2=stnInfoList;
  int i=0;int j=0;
  while(t2!=NULL){
    if(i%4==0){
       s[j]=t2->object;
       j+=1;
    }
    i=(i+1)%4;
    t2=t2->next;
  }
  return s;

}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  TrainInfoPerStation** s=preprocessing(stnInfoList);
  





}

int pivot(int a,int b){
  return (a+b)/2;
}
