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

#include <bits/stdc++.h>
using namespace std;

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
bool lessThan(TrainInfoPerStation *a, TrainInfoPerStation *b){
  for (int i = 0; i < 7; i++){
    if (a->daysOfWeek[i] && !b->daysOfWeek[i]) return true;
    else if (!a->daysOfWeek[i] && b->daysOfWeek[i]) return false;
    else continue;
  }

  if (a->arrTime < b->arrTime) return true;
  else return false;
  
}

bool equalTo(TrainInfoPerStation *a, TrainInfoPerStation *b){
  for (int i = 0; i < 7; i++){
    if (a->daysOfWeek[i] && !b->daysOfWeek[i]) return false;
    else if (!a->daysOfWeek[i] && b->daysOfWeek[i]) return false;
    else continue;
  }

  if (a->arrTime == b->arrTime) return true;
  else return false;
  
}

void myswap(TrainInfoPerStation *a, TrainInfoPerStation *b){
  TrainInfoPerStation temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int *arrayOfPoints;
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

  if (recursionLevel == 0)
  {
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
TrainInfoPerStation *mypivot(int k, listOfObjects<TrainInfoPerStation *> **array, listOfObjects<TrainInfoPerStation *> *start, int startIndex, int endIndex){
  srand(time(0));
  int num = startIndex + rand()%(endIndex-startIndex+1);
  int num2 = num/k;
  int num3 = num - num2*k;
  listOfObjects<TrainInfoPerStation*>* ans = array[num2];
  for (int i = 0; i < num3; i++)
  {
    ans = ans->next;
  }
  
  return ans->object;
}

void myquicksort(listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> *end, int k, listOfObjects<TrainInfoPerStation *> **array, int startIndex, int endIndex){
  if (start == nullptr || end == nullptr) return;
  listOfObjects<TrainInfoPerStation *> *mystart = start, *myend = end;
  if (mystart == myend || mystart->prev == myend) return;
  if (mystart->next == myend){
    if (lessThan(mystart->object, myend->object)) return;
    else{
      myswap(mystart->object, myend->object);
      return;
    }
  }
  TrainInfoPerStation pivot = *mypivot(k, array, start, startIndex, endIndex);
  int mystartIndex=endIndex, myendIndex = startIndex;
  while (true){
    if (mystart->prev == myend || mystart == myend) break;
    while (lessThan(mystart->object, &pivot)){
      mystart = mystart->next;
      myendIndex++;
      if (mystart->prev == myend || mystart == myend){
        break;
      }
    }
    if (mystart->prev == myend || mystart == myend) break;
    while (lessThan(&pivot, myend->object)){
      myend = myend->prev;
      mystartIndex--;
      if (mystart->prev == myend || mystart == myend){
        break;
      }
    }
    if (mystart->prev == myend || mystart == myend)break;
    myswap(mystart->object, myend->object);
  }
  myquicksort(start, mystart->prev, k, array,startIndex, myendIndex-1);
  myquicksort(myend->next, end, k, array, mystartIndex+1, endIndex);
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
                    // level of the recursion you are in

  // Increment recursion level on entering the function

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

  listOfObjects<TrainInfoPerStation *> **array;
  int n = 1;
  listOfObjects<TrainInfoPerStation *> *tail = stnInfoList;
  while (tail->next != nullptr)
  {
    tail = tail->next;
    n++;
  }
  int parts = ceil(n / K);
  array = new listOfObjects<TrainInfoPerStation *> *[parts];
  listOfObjects<TrainInfoPerStation *> *store = stnInfoList;
  int n1 = 0;
  while (store->next != nullptr)
  {
    if ((n1) % K == 0)
    {
      array[(n1) / K] = store;
    }
    store = store->next;
    n1++;
  }
  if ((n1) % K == 0)
  {
    array[(n1) / K] = store;
  }
  myquicksort(stnInfoList, tail, K, array, start, end);
  return;
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
}

#endif
