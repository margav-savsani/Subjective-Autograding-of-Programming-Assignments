#ifndef STD_HEADERS
#include "std_headers.h"
#include<vector>
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

int getsize(listOfObjects<TrainInfoPerStation *> *stnInfoList){ //
  listOfObjects<TrainInfoPerStation*> * a=stnInfoList;
  int size=0;
  while(a->next!=NULL){
    size++;
  }
  return size;

}
partitions(listOfObjects<TrainInfoPerStation *> *stnInfoList,int K){
TrainInfoPerStation *a;
int size=getsize(stnInfoList);
a=vector<TrainInfoPerStation*>;
//a.pushback()dd;



}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.





}
