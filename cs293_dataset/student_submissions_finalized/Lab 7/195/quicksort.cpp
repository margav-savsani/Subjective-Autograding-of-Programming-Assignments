#ifndef STD_HEADERS
#include "std_headers.h"
#endif
#include<cmath>
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
  listOfObjects<TrainInfoPerStation*>* temp=stnInfoList;
  int z=0;
  while(stnInfoList!=nullptr){
    z=z+1;
    stnInfoList=stnInfoList->next;
  }
  stnInfoList=temp;
  int n=ceil(z/4);
  listOfObjects<TrainInfoPerStation*>* s[n];
  for(int p=0;p<n;p++){
    s[p]=nullptr;
  }
  int k=0;
  for(int j=0;j<n;j++){
    int i=0;
    s[j]=stnInfoList;
    while(stnInfoList->next!=nullptr && i<4){
      stnInfoList=stnInfoList->next;
      i=i+1;
    }
  }

  // Put your code here.
}
