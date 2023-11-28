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

#include <cmath>
#include <cassert>
#include <vector>

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

int day(TrainInfoPerStation *info){ // an extra function which returns the day given a pointer, this helps in sorting a lot
  for (int i = 0; i < 7; i++){
    if (info->daysOfWeek[i]) return i;
  }
  return -1;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static vector<listOfObjects<TrainInfoPerStation *> *>pivot_tmp; // a vector which helps in randomization
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
    pivot_tmp.clear(); // clear it first before using
    listOfObjects<TrainInfoPerStation *> *tmp = stnInfoList;
    int count = 0;
    while (tmp != nullptr){
      if (count == 0) pivot_tmp.push_back(tmp); // append only when count is 0 modulo K, so only n/K trains will get entered
      tmp = tmp->next;
      count = (count + 1) % K;
    }
  }
  // Put your code for the core of QuicksortSimple here
  if (start < end){
    int comp = 0;
    listOfObjects<TrainInfoPerStation *> *tmp = stnInfoList;
    for (int i = 0; i < end; i++){
      tmp = tmp->next; // tmp stores the 'end' pointer
    }
    listOfObjects<TrainInfoPerStation *> *pivot = nullptr; // pivot contains the pointer to randomized pivot
    int l = (int)ceil(start/K), m = end/K, pos = l + rand() % (m - l + 1); // 'l' & 'm' gives a bound for the random number
    pivot = pivot_tmp[pos]; // take the pointer at that location, and then
    int steps = rand() % K, foo = 0; // go a certain random number of steps ahead so as to take each number equally
    while (foo < steps && pos*K + foo < end){ // it might happen that while going 'steps' many steps, we reach the end as n might not pe divisible by K.
      pivot = pivot->next; // In that case we take the last element as pivot
      foo ++;
    }
    int p = day(pivot->object); // p is the day of pivot
    TrainInfoPerStation *tmpfoo = pivot->object;
    pivot->object = tmp->object;
    tmp->object = tmpfoo;
    listOfObjects<TrainInfoPerStation *> *i = stnInfoList, *j = tmp; // i starts from 'start' while j starts from 'end'
    for (int k = 0; k < start; k++){
      i = i->next;
    }
    int i1 = start, j1 = end;
    while (true){
      while(i != nullptr && day(i->object) <= p){
        if (day(i->object) == p && i->object->arrTime > pivot->object->arrTime) break; // this is done to incorporate sorting by arrival time
        i1 ++;
        i = i->next;
      }
      while(j != nullptr && day(j->object) > p){
        j1 --;
        j = j->prev;
      }
      if (i1 >= j1){
        break;
      }
      else{ // swap 'i' and 'j'
        comp ++;
        TrainInfoPerStation *tmp = i->object;
        i->object = j->object;
        j->object = tmp;
      }
    }
    if (comp > 0){ // this check helps to pass certain edge cases
      QuicksortSimple(stnInfoList, start, j1);
      QuicksortSimple(stnInfoList, j1 + 1, end);
    }
    else{ // if no comparisons are done then 'j' hasn't(might) shifted from its position. So doing the above recursive call will lead to infiinite loop.
      QuicksortSimple(stnInfoList, start, j1 - 1);
      QuicksortSimple(stnInfoList, j1 + 1, end);
    }
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return; // I have tried to cover as many edge cases as I could, but there still might be a few ones left. Since the algo is randomized, if for any testcase my program fails,
  // please repeat the testcase a few times for my program to pass.
}

#endif
