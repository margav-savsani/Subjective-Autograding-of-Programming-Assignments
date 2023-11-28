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

bool compare(TrainInfoPerStation* a,TrainInfoPerStation* b){
  int x,y;
  x=a->arrTime; //sorted based on arrival time as per the question
  y=b->arrTime;
  int i;
  for(i=0;i<7;i++){
    if(a->daysOfWeek[i]) break;
  }
  x=x+i*10000;  //as arrival time can atmax be 2400
  for(i=0;i<7;i++){
    if(b->daysOfWeek[i]) break;
  }
  y=y+i*10000;
  return (x<y);
}


void swap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  TrainInfoPerStation* temp;  //to swap the TrainInfo per station
  temp = a->object;
  a->object=b->object;
  b->object=temp;
}
int Planner::Partition(int start,int finish,listOfObjects<TrainInfoPerStation *> *startlist,listOfObjects<TrainInfoPerStation *> *finallist,listOfObjects<TrainInfoPerStation *> *x){
  int i = start-1;
  int j = finish+1;
  TrainInfoPerStation* val=x->object;
  swap(x,startlist);
  while(1){
    do{
      j--;
      if (j!=finish)  finallist=finallist->prev;
    }
    while(compare(val,finallist->object));
    do{
      i++;
      if (i!=start) startlist=startlist->next; 
    }
    while(compare(startlist->object,val));
    if(i<j){
      swap(startlist->object,finallist->object);
    }
    else return j;
  }
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
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int size=0;
  static listOfObjects<TrainInfoPerStation *> **s;
  // Increment recursion level on entering the function
  recursionLevel++;
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.


    size=end+1; // as the index of last element is given 
    s = new listOfObjects<TrainInfoPerStation *>*[size/K+1];  //extra 1 size is for the case in which remainder!=0
    listOfObjects<TrainInfoPerStation *> *te = stnInfoList;
    for(int i=0;i<size;i++){  //storing adresses in an array
      if (i%K==0)
      {
        s[i/K]=te;
      }
      te=te->next; 
    }
  }
  // Put your code for the core of QuicksortSimple here
  int z = start+(rand()%(end-start+1));
  listOfObjects<TrainInfoPerStation *> *x;
  listOfObjects<TrainInfoPerStation *> *p;
  p = s[z/K];
  for(int i=0;i<z%K;i++){
    p=p->next;
  }
  x=p;  //pivot is chosen
  if(start<end){
    p=s[start/K];
    for(int i=0;i<start%K;i++){
     p=p->next; 
    }
    listOfObjects<TrainInfoPerStation *> *startlist=p;
    listOfObjects<TrainInfoPerStation *> *l;
    l=s[end/K];
    for(int i=0;i<end%K;i++){
     l=l->next; 
    }
    listOfObjects<TrainInfoPerStation *> *finallist=l;
    int q = Partition(start,end,startlist,finallist,x);
    QuicksortSimple(stnInfoList,start,q);
    QuicksortSimple(stnInfoList,q+1,end);
  }
  recursionLevel--;
  return;
}

#endif
