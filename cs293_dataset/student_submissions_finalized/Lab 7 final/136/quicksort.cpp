#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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

#include <time.h>
int dept_index(TrainInfoPerStation *q){
  for(int i=0;i<7;i++){
    if(q->daysOfWeek[i])
    {
      return i;
    }
  }
}
bool lessthan (TrainInfoPerStation *q,TrainInfoPerStation *p){
  int a=dept_index(q);
  int b=dept_index(p);
  if(a==b){
    return(q->depTime<p->depTime);
  }
  return (a<b);
}

int partition(int start, int finish, TrainInfoPerStation* pivot,listOfObjects<TrainInfoPerStation* >* stnInfoList){
  int i = start-1; // Index of smaller element and indicates the right position of pivot found so far
  listOfObjects<TrainInfoPerStation* >* r=stnInfoList;
  listOfObjects<TrainInfoPerStation* >* o=nullptr;
  for(int i=0;i<start;i++){
    r=r->next;
  }
  o=r;
  for(int i=start;i<=finish;i++){
    if(i!=start){
      r=r->next;
    }
    if(r->object==pivot){
      o=r;
    }
  }
  if(o!=nullptr){
  TrainInfoPerStation* temp1= r->object;
  r->object=o->object;
  o->object=temp1;}
  listOfObjects<TrainInfoPerStation *> *t =&stnInfoList[0];
  for(int i=0;i<start;i++){
    t=t->next;
  }
  listOfObjects<TrainInfoPerStation *> *p=t;
  for (int j=start; j<=finish-1; j++) 
  { 
    if(j!=start)
    {p=p->next;}
    if (lessthan(p->object,pivot)) 
    {
      i++;
      TrainInfoPerStation* temp= t->object;
      t->object=p->object;
      p->object=temp;
      t=t->next;
    }
  }
  p=p->next;
  TrainInfoPerStation * temp=t->object;
  t->object=p->object;
  p->object=temp;
  return (i + 1);
}

TrainInfoPerStation* random_pivot(listOfObjects<TrainInfoPerStation*>**first_elements,int start,int end,int k){
  srand(time(0));
  int n=end-start+1;
  int p=start+rand()%n;
  int integral=(p/k);
  int fract=p%k;
  listOfObjects<TrainInfoPerStation*>* d=first_elements[integral];
  for(int i=0;i<fract;i++){
    d=d->next;
  }
  return (d->object);
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  recursionLevel++;
  if(start<end)
  {
  int d=(end-start+1)/K;
  listOfObjects<TrainInfoPerStation *> *an=stnInfoList;
  static listOfObjects<TrainInfoPerStation*>* *p=new listOfObjects<TrainInfoPerStation*> *[d];
  if(recursionLevel==0){
    int i=0;
    int j=0;
    while(an->next!=nullptr){
      if(i%K==0){
        p[j]=an;
        j++;
      }
      i++;
      an=an->next;
    }
  }
  TrainInfoPerStation *pivot= random_pivot(p,start,end,K);
  int partition_index=partition(start,end,pivot,stnInfoList);
  QuicksortSimple(stnInfoList,start,partition_index-1);
  QuicksortSimple(stnInfoList,partition_index+1,end);

  }
  recursionLevel--;
  return;
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
