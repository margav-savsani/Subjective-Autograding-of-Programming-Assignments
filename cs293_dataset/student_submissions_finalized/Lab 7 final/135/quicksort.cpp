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
// integer parameters "stnInfoList" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "stnInfoList" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we stnInfoList
// counting elements of the list stnInfoListing from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices stnInfoList, stnInfoList+1, ... until end
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

bool lessthan(TrainInfoPerStation *a, TrainInfoPerStation *b){
  int i,j;
  for(i=0; i<7; i++){
    if(a->daysOfWeek[i]==1) break;
  }
  for(j=0; j<7; j++){
    if(b->daysOfWeek[j]==1) break;
  }
  if(i!=j) return i<j;
  else if(a->depTime != b->depTime) return a->depTime < b->depTime;
  else if(a->arrTime != b->arrTime) return a->arrTime < b->arrTime;
  else return true;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  if(stnInfoList==nullptr) return;
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
  static listOfObjects<TrainInfoPerStation*>* *arr;
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation*>* curr = stnInfoList;
    int len=0, arrlen;
    while(curr != nullptr){
      curr = curr->next;
      len++;
    }
    curr = stnInfoList;
    arrlen = len/K;
    if(len%K){
      arrlen++;
    }
    arr = new listOfObjects<TrainInfoPerStation*>*[arrlen];
    int i=0;
    while(curr != nullptr){
      arr[i] = curr;
      i++;
      for(int j=0;j<K && curr != nullptr;j++){
        curr = curr->next;
      }
    }
  }
  
  // Put your code for the core of Quicksort here
  listOfObjects<TrainInfoPerStation*>* begin = stnInfoList;
  listOfObjects<TrainInfoPerStation*>* last = stnInfoList;
  int i=0;
  int j=0;
  while(last->next != nullptr){
    last = last->next;
    j++;
  }
  if(j==0){
    recursionLevel--;
    return;
  }

  int p = rand()%(j+1);
  int ind = p/K;
  int tra = p%K;
  listOfObjects<TrainInfoPerStation*>* curr = arr[ind];
  for(int in = 0; in<tra; in++){
    curr = curr->next;
  }
/* ------------------------------------------------------------------------------------------------ */
  TrainInfoPerStation* pivot = curr->object;
/* ------------------------------------------------------------------------------------------------ */
  // cout << "Pivot: " << pivot->journeyCode << "\n";
  while(true){
    while(begin != nullptr && begin->next != nullptr && lessthan(begin->object,pivot)){
      begin = begin->next;
      i++;
    }
    while(last != nullptr && last->prev != nullptr && lessthan(pivot,last->object)){
      last = last->prev;
      j--;
    }
    if(i<j){
      TrainInfoPerStation* temp = begin->object;
      begin->object = last->object;
      last->object = temp;
      // begin = begin->next;
      // last = last->prev;
      // i++;
      // j--;
    }
    else break;
  }
  // print(stnInfoList);
  // cout << begin->object<<"\n";
  if(last->prev == nullptr){
    last->next->prev = nullptr;
    Quicksort(last->next);
    last->next->prev = last;
  }
  else if(begin->next == nullptr){
    begin->prev->next = nullptr;
    Quicksort(stnInfoList);
    begin->prev->next = begin;
  }
  else{
    last->next->prev = nullptr;
    Quicksort(last->next);
    last->next->prev = last;
    begin->prev->next = nullptr;
    Quicksort(stnInfoList);
    begin->prev->next = begin;
  }

  // listOfObjects<TrainInfoPerStation*>* currlist = stnInfoList;
  // while(currlist != nullptr){
  //   cout << currlist->object->depTime << "\n";
  //   currlist = currlist->next;
  // }
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
  }
  
  // Put your code for the core of QuicksortSimple here
  Quicksort(stnInfoList);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
