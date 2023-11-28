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

#include<vector>

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

bool larger(listOfObjects<TrainInfoPerStation*> *first,listOfObjects<TrainInfoPerStation*> *second){
  for(int i=0; i<7; i++){
    if(first->object->daysOfWeek[i]){
      for(int j=0; j<7; j++){
        if(second->object->daysOfWeek[j]){
          if(i>j) return true;
          else if(i==j){
            if(first->object->arrTime > second->object->arrTime) return true;
            else return false;
          }
          else return false;
        }
      }
    }
  }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  int n=0;
  listOfObjects<TrainInfoPerStation *> *temp=stnInfoList;
  while(temp!=nullptr){
    n++;
    temp=temp->next;
  }
  QuicksortSimple(stnInfoList,0,n-1);
  return;
}  

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{

  if(start>=end) return;

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
  // 
  
  static vector<listOfObjects<TrainInfoPerStation *>*> all_train;
  static int n;
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    srand(time(0));
    listOfObjects<TrainInfoPerStation*> *temp1=stnInfoList;
    n=end-start+1;
    all_train.clear();
    for(int i=0; i<n; i++){
      if(i%K==0) all_train.push_back(temp1);
      temp1=temp1->next;
    }
    
  }


  // Put your code for the core of QuicksortSimple here
  
  int pivot=start+rand()%(end-start+1);
  int j=0;
  listOfObjects<TrainInfoPerStation*> *t_pivot=all_train[pivot/K];
  while(j<pivot%K ){
    t_pivot=t_pivot->next;
    j++;
  }
  
  j=0;
  listOfObjects<TrainInfoPerStation*> *temp=all_train[start/K];
  while(j<start%K ){
    temp=temp->next;
    j++;
  }
  
  j=0;
  listOfObjects<TrainInfoPerStation*> *t_end=all_train[end/K];
  while(j<end%K ){
    t_end=t_end->next;
    if(t_end==nullptr) cout<<j<<endl; 
    j++;
  }

  listOfObjects<TrainInfoPerStation*> *higher=temp;


  listOfObjects<TrainInfoPerStation*> *rel_pivot=new listOfObjects<TrainInfoPerStation*> (t_pivot->object);


  listOfObjects<TrainInfoPerStation*> *lesser=t_end;
  int s=start,e=end;

  while(!larger(higher,rel_pivot)){
    higher=higher->next;
    if(higher==nullptr) break;
    s++;
  }

  while(larger(lesser,rel_pivot)){
    lesser=lesser->prev;
    if(lesser==nullptr) break;
    e--;
  }

  
  while(s<e){

    TrainInfoPerStation *abc=lesser->object;
    lesser->object=higher->object;
    higher->object=abc;

    higher=higher->next;
    s++;
    lesser=lesser->prev;
    e--;

    while(!larger(higher,rel_pivot)){
      higher=higher->next;
      if(higher==nullptr) break;
      s++;
    }
    while(larger(lesser,rel_pivot)){
      lesser=lesser->prev;
      if(lesser==nullptr) break;
      e--;
    }
   
  }


  if(end-start==1){
    if(larger(temp,t_end)){
      TrainInfoPerStation *abc=temp->object;
      temp->object=t_end->object;
      t_end->object=abc;
    }
  }
  if(s>start){
    QuicksortSimple(stnInfoList,start,s-1);
    QuicksortSimple(stnInfoList,s,end);
  }
  else{
    QuicksortSimple(stnInfoList,start,s);
    QuicksortSimple(stnInfoList,s+1,end);
  }

  recursionLevel--;
  return;
}

#endif
