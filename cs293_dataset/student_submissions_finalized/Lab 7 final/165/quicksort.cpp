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
#include<bits/stdc++.h>
bool earliercomparison(listOfObjects<TrainInfoPerStation *> *var1,listOfObjects<TrainInfoPerStation *> *var2);



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

bool earliercomparison(listOfObjects<TrainInfoPerStation *> *var1,listOfObjects<TrainInfoPerStation *> *var2){
    for(int i=0;i<7;i++){
    
      if(var1->object->daysOfWeek[i]==true and var2->object->daysOfWeek[i]==false){//if first train arrives first return true

        return true;
        
      }
      else if(var1->object->daysOfWeek[i] and var2->object->daysOfWeek[i]){//if both trains arrive on same day compare arrival time


        //
        if(var1->object->arrTime < var2->object->arrTime)
          return true;
        else
          return false;
      }
      else if(var1->object->daysOfWeek[i]==false and var2->object->daysOfWeek[i]==true){//train 2 arrives some day before train 1

        return false;
      }
    }
}
int Planner::partition(int start,int end,listOfObjects<TrainInfoPerStation *>* *startptr, listOfObjects<TrainInfoPerStation *>* *endptr, int K, listOfObjects<TrainInfoPerStation*>* * arr){

  srand(time(0));


  int reqd = (start+rand()%(end-start+1));
  listOfObjects<TrainInfoPerStation *> pivot = *arr[reqd/K];
  int rem = reqd % K;
  for(int i=1;i<=rem;i++){
    pivot = *(pivot.next);
  }
  
  //find process for choosing pivot

  int i = start;
  int j = end;
  if(i==j){
    return j;//base case-if only one element is present
  }
  while(i<j){
    while(earliercomparison(*startptr,&pivot) && *startptr!=*endptr){// i comes before pivot
          *startptr = (*startptr)->next;
          i++;
    }

    while(earliercomparison(&pivot,*endptr) && *startptr!=*endptr){//j comes after pivot
          *endptr = (*endptr)->prev;
          j--;
    }
    swap((*startptr)->object,(*endptr)->object);
    if(i==j)return j;
  }

}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{

  if(start >= end) return;
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
  static listOfObjects<TrainInfoPerStation *> *endstnInfoList;
  static int listlength=1;

  static listOfObjects<TrainInfoPerStation *> *startptr ;
  static listOfObjects<TrainInfoPerStation *> *endptr ;
  static listOfObjects<TrainInfoPerStation *>*   *arr;
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
   listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;
   while(curr->next!=nullptr){
      curr = curr->next;
      listlength++;
    }
    endstnInfoList = curr;
    startptr = stnInfoList;
    endptr = endstnInfoList;
    curr = stnInfoList;
    int arrlen = ceil(1.0*listlength/K);
    arr = new listOfObjects<TrainInfoPerStation *>*[arrlen];
    int count = 0;
    while(curr!=nullptr && count<listlength){
  
      arr[count] = curr;
      count ++;
      for(int i=1;i<=K && curr!=nullptr;i++){
        curr = curr->next;
      }
    }
  }

  
  // Put your code for the core of QuicksortSimple here


  listOfObjects<TrainInfoPerStation *> *tempstart = startptr, *tempend = endptr;
  int pi = partition(start,end,&startptr,&endptr, K, arr);
  //consdiering start and end are the starting and ending points of the partial linked lists at every recursion level;

  if(pi < 0 || pi > listlength - 1){
    recursionLevel--;
    return;
  }

  listOfObjects<TrainInfoPerStation *> *tempstartnew = startptr, *tempendnew = endptr;
  startptr = tempstart;
  endptr = tempstartnew->prev;

  QuicksortSimple(stnInfoList, start, pi-1);  // Before pi
  startptr = tempendnew->next;

  endptr = tempend;

  QuicksortSimple(stnInfoList, pi+1, end); // After pi

  startptr = tempstart;
  endptr = tempend;
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}


#endif
