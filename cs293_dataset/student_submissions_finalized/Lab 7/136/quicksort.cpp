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

listOfObjects<TrainInfoPerStation *> random_pivot(listOfObjects<listOfObjects<TrainInfoPerStation> *> *first_elements,int n){
  int p=n*rand();
  int integral=(p/k);
  int fract=p%k;
  t=first_elements;
  r=first_elements->object;
  for(int i=0;i<integral;i++){
    t=t->next;
  }
  for(int i=0;i<fractional;i++){
    r=r->next;
  }
  return r;
}
int k=4;
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *a=stnInfoList;
  listOfObjects<listOfObjects<TrainInfoPerStation> *> *p;
  int i=0;
  while(stnInfoList->next!=nullptr){
    if(i%k==0){
      p->object=a;
      p=p->next;
    }
    i++;
    a=a->next;
  }
  listOfObjects<TrainInfoPerStation *> random_pivot(p,i);
}
