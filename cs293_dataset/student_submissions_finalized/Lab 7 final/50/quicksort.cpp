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


bool lessThan(listOfObjects<TrainInfoPerStation *> *lesser, listOfObjects<TrainInfoPerStation *> *greater){
  int l = 0, g = 0;
  for(; l < 7; l++){
    if(lesser->object->daysOfWeek[l]) break;
  }
  for(; g < 7; g++){
    if(greater->object->daysOfWeek[g]) break;
  }
  if(lesser->object->depTime != -1 && greater->object->depTime != -1){
    if(2400*l+lesser->object->depTime < 2400*g+greater->object->depTime) return true;
    else return false;
  }
  else if(lesser->object->depTime == -1 && greater->object->depTime != -1){
    return false;
  }
  else if(lesser->object->depTime != -1 && greater->object->depTime == -1){
    return true;
  }
  else{
    if(l < g) return true;
    else return false;
  }
}

void swap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  TrainInfoPerStation *temp;
  temp = a->object;
  a->object = b->object;
  b->object = temp;
  return;
}

listOfObjects<TrainInfoPerStation *> *getEle(int i, int K, listOfObjects<TrainInfoPerStation *> **store){
  listOfObjects<TrainInfoPerStation *> *curr = store[i/K];
  for(int a = 0; a < i%K; a++){
    curr = curr->next;
  }
  return curr;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  static int n = 0;                              

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
    listOfObjects<TrainInfoPerStation *> *curr;
    curr = stnInfoList;
    while(curr != nullptr){
      n++;
      curr = curr->next;
    }
    static listOfObjects<TrainInfoPerStation *> **store;
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

  static int n = 0;
  static listOfObjects<TrainInfoPerStation *> **store;

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
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation *> *curr;
    curr = stnInfoList;
    while(curr != nullptr){
      n++;
      curr = curr->next;
    }
    curr = stnInfoList;
    store = new listOfObjects<TrainInfoPerStation *> *[n/K+1];
    for(int i = 0; i < n/K+1; i++){
      store[i] = curr; 
      for(int j = 0; j < K; j++){
        curr = curr->next;
        if(curr == nullptr) break;
      }
    }
    curr = stnInfoList;
  }
  
  // Put your code for the core of QuicksortSimple here
  if(start < end){
    int pivotIndex = (rand()%(end-start+1))+start;
    listOfObjects<TrainInfoPerStation *> *pivot = getEle(pivotIndex, K, store);
    listOfObjects<TrainInfoPerStation *> *last = getEle(end, K, store);
    swap(pivot, last);
    int x = start-1;
    for(int y = start; y < end; y++){
      if(lessThan(getEle(y, K, store), last)){
        x++;
        swap(getEle(x, K, store), getEle(y, K, store)); 
      }
    }
    swap(last, getEle(x+1, K, store));
    QuicksortSimple(stnInfoList ,start, x);
    QuicksortSimple(stnInfoList, x+2, end);
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
