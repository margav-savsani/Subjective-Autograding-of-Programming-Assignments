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
#include "time.h"
#include "stdlib.h"
#define k 4
// bool lessthan(TrainInfoPerStation *x1,TrainInfoPerStation *x2){

// }
TrainInfoPerStation* pivot(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  TrainInfoPerStation* curr=stnInfoList;
  TrainInfoPerStation* curr1=stnInfoList;
  int count=0;
  
  while(curr!=nullptr){
    curr=curr->next;
    count++;
  }

  int n=count;
  TrainInfoPerStation** lst;
  lst=new TrainInfoPerStation*[n/k];
  int i=0;
  while(curr1!=nullptr){
    if(i%k==0){   // new n/k size list
      lst[i/k]=curr1;
    }
    curr1=curr1->next;
    i++;
  }

  srand (time(NULL));
  int start= rand()%(n/k);
  int incr= rand()%k;

  //O(k) time
  for(int i=0;i<incr;i++){
    if(lst[start]->next==nullptr){break;}
    lst[start]=lst[start]->next;
  }

  return lst[start];
}

// TrainInfoPerStation *partition(listOfObjects<TrainInfoPerStation *> *stnInfoList)
// {
//   TrainInfoPerStation* x;
//   TrainInfoPerStation *piv=pivot(listOfObjects<TrainInfoPerStation *> *stnInfoList)
//   if(lessthan())
  
// }

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  // if()
}
