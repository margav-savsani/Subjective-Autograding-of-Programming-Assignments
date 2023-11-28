#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#include <time.h>

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


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  int count=0;
  listOfObjects<TrainInfoPerStation *> *x=stnInfoList;
  while(x!=nullptr){
    x=x->next;
    count++;
  }
  QuicksortSimple(stnInfoList,0,count-1);
}

//returns true if a departs first. if dept time is same it returns true a arrives fast.
bool lessthan(TrainInfoPerStation *a,TrainInfoPerStation *b){
  for(int i=0;i<7;i++){
    bool b1 = a->daysOfWeek[i];
    bool b2 = b->daysOfWeek[i];
    if(b1==true && b2==false){return true;}
    else if(b1==false && b2==true){return false;}
    else if(b1==true && b2==true){
      if(a->depTime!=b->depTime){return (a->depTime < b->depTime);}
      else{return (a->arrTime < b->arrTime);}
    }
  }
  return false;
}

//returns a node x where x is node->next->next..(n times next).
listOfObjects<TrainInfoPerStation *> * nthelem(listOfObjects<TrainInfoPerStation *> *node, int n){
  listOfObjects<TrainInfoPerStation *> *x=node;
  for(int i=0;i<n;i++){
    if(x!=nullptr){x=x->next;}
  }
  return x;
}

// swaps objects with in x and y
void exchange(listOfObjects<TrainInfoPerStation *> *x,listOfObjects<TrainInfoPerStation *> *y){
  TrainInfoPerStation *obj=y->object;
  y->object=x->object;
  x->object=obj;
}

//creates a random pivot with o(K) time and additional array of n/k size
listOfObjects<TrainInfoPerStation *> *PIVOT(listOfObjects<TrainInfoPerStation *> *node, int n, int k)
{
  listOfObjects<TrainInfoPerStation *> **arr;
  arr = new listOfObjects<TrainInfoPerStation *> *[1+n/k];
  listOfObjects<TrainInfoPerStation *> *curr=node;
  for(int i=0;i<n;i++){     // preprocessing and storing arr[i]=nthelem(node,ik);
    if(i%k==0){
      arr[i/k]=curr;
    }
    curr=curr->next;
  }

  srand(time(0));
  int a=rand()%n;
  int b=a/k;
  int c=a%k;
  return (nthelem(arr[b],c)); // c may go upto k-1, so k-1 time next to arr[b] gives O(k) time
}

// puts the pivot in its sorted positon in linkedlist
int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, int k)
{
  listOfObjects<TrainInfoPerStation *> *pivot = PIVOT(nthelem(stnInfoList, start), end-start+1, k);
  listOfObjects<TrainInfoPerStation *> *pi=pivot;
  TrainInfoPerStation* piobj=pivot->object;
  listOfObjects<TrainInfoPerStation *> *curr=nthelem(stnInfoList,start);
  int x=start-1;
  for(int i=0;i<=end-start;i++){
    
    if(lessthan(curr->object,piobj)){
      x++;
      exchange(curr,nthelem(stnInfoList,x));
      if (piobj == curr->object) {pi = curr;}
    }
    curr=curr->next;
  }
  exchange(pi,nthelem(stnInfoList,x+1));
  return x+1;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  if(start < end){
    int part=partition(stnInfoList,start,end,K);
    QuicksortSimple(stnInfoList,start,part-1);
    QuicksortSimple(stnInfoList,part+1,end);
  }
  else{
      return;
  }
}

#endif
