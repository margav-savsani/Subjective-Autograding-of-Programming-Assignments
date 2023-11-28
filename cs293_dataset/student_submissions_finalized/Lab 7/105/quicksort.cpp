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

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e. 
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.
/*

int partitionsimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end,listOfObjects<TrainInfoPerStation *> *pivot){
  int i = start, j = end;
  while(true){
    listOfObjects<TrainInfoPerStation *> *currList1 = stnInfoList;
    listOfObjects<TrainInfoPerStation *> *currList2 = stnInfoList;
    for(int k = 0;k<i;k++){
      currList1 = currList1->next;      
    }
    for(int k = 0;k<j;k++){
      currList2 = currList2->next;      
    }
    while(isgreaterThan(currList2->object,pivot->object)){      
      j = j-1;            
      currList2 = currList2->prev;
      if(currList2==nullptr)break;
    }
    while(isgreaterThan(pivot->object,currList1->object)){
      i = i+1;
      currList1 = currList1->next;
      if(currList1==nullptr)break;      
    }
    if(i<j){
      TrainInfoPerStation *node = currList1->object;
      currList1->object = currList2->object;
      currList2->object = node;
    }
    else return j;
  }
}
*/
bool checkequal(TrainInfoPerStation a,TrainInfoPerStation b){
  if((a.arrTime=b.arrTime)&&(b.depTime==a.depTime) ){
    for(int i=0;i<7;i++){
      if(a.daysOfWeek[i]=b.daysOfWeek[i]){
        continue;
      }
      else return false;
      
    }
    return true;
  }
  else return false;
}

bool compare(TrainInfoPerStation* obj1,TrainInfoPerStation* obj2){
  for(int i=0;i<7;i++){
    if((obj1->daysOfWeek[i]) && !(obj2->daysOfWeek[i])){
      return true;
    }
    if(!(obj1->daysOfWeek[i]) && (obj2->daysOfWeek[i])){
      return false;
    }
    if((obj1->daysOfWeek[i]) && (obj2->daysOfWeek[i])){
      if(obj1->depTime==obj1->depTime){
        if(obj1->arrTime<obj2->arrTime) return true;
        else return false;
      }
      else if(obj1->depTime < obj2->depTime) return true;
      else return false;
    }
  }
  return true;
}

//int p=Partition(*stnInfoList,start,end,s[q]);
int Partition(listOfObjects<TrainInfoPerStation *> *A,int start,int end,listOfObjects<TrainInfoPerStation*> *pivot){
  int i = start, j = end;
  TrainInfoPerStation p=*(pivot->object);
  listOfObjects<TrainInfoPerStation *> *list1=A;
  listOfObjects<TrainInfoPerStation *> *list2=A;
    for(int k = 0;k<i;k++){
      list1 = list1->next;      
    }
    for(int k = 0;k<j;k++){
      list2 = list2->next;      
    }
  while(true){
    
    while(compare(&p,list2->object)){ 
      j = j-1;            
      list2 = list2->prev;
      if(checkequal(p,*(list2->object))) break;
      if(list2==nullptr)break;
    }
    while(compare(list1->object,&p)){
      i = i+1;
      list1 = list1->next;
      if(checkequal(p,*(list1->object))) break;
      if(list1==nullptr)break;      
    }
    if(i<j){
      TrainInfoPerStation x = *(list1->object);
      *(list1->object) = *(list2->object);
      *(list2->object) = x;
    }
    else return j;
  }
}

void Planner::Quicksort(listOfObjects <TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
   
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it once using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.

  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.So you MUST NOT allocate space in each recursive call.
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

void Planner::QuicksortSimple(listOfObjects <TrainInfoPerStation *> *stnInfoList, int start, int end)
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
  
  //static listOfObjects <listOfObjects<TrainInfoPerStation *>*> *L=new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(stnInfoList);
  static int N=1;
  if(recursionLevel==0){
  listOfObjects <TrainInfoPerStation *> *SIL= stnInfoList;
  while(SIL->next!=nullptr){
    SIL=SIL->next;
    N+=1;
  }
  }
  static listOfObjects<TrainInfoPerStation*> **s=new listOfObjects<TrainInfoPerStation*>*[((N-1)/K)+1];

  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    
    listOfObjects <TrainInfoPerStation *> *SILK= stnInfoList;
    int j=0;
    while(SILK!=NULL){
      s[j]=SILK;
      j+=1;
      for(int i=0;i<K;i++){
        //if(SILK->next==NULL){
         // break;
        //}
        if(SILK==NULL) break;
        SILK=SILK->next;
      }
      //L->next->prev=L;
      //L->next=new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(stnInfoList);
      //L->next->prev=L;
      //L=L->next;
    }  
  }
  
  // Put your code for the core of QuicksortSimple here
  if(start<end){
    srand((unsigned)time(NULL)); 
    int ran = (rand()%(end-start)) + start; //numbers generated by equal probabilitiy between a and b
    int q=ran/K;int r=ran%K;
    
    listOfObjects<TrainInfoPerStation*>* pivot=s[q];
    for(int i=0;i<r;i++){
      pivot=pivot->next;
    }
    int p=Partition(stnInfoList,start,end,pivot);
    //if((q==end)||(q+1==start)){
     // recursionLevel--;
     // return;
    //}
    QuicksortSimple(stnInfoList,start,p);
    QuicksortSimple(stnInfoList,p+1,end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
