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

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <time.h>

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

void interchange(int &a, int &b) {
  a = a + b;
  b = a - b;
  a = a - b;
}

void interchange(unsigned short &a, unsigned short &b) {
  a = a + b;
  b = a - b;
  a = a - b;
}

void exchange(listOfObjects<TrainInfoPerStation *> *first, listOfObjects<TrainInfoPerStation *> *second)
{
  interchange(first->object->arrTime,second->object->arrTime);
  interchange(first->object->depTime,second->object->depTime);
  interchange(first->object->journeyCode,second->object->journeyCode);
  interchange(first->object->stopSeq,second->object->stopSeq);

  int a = -1, b = -1;
  for (int temp = 0; temp < 7; temp++)
  {
    if (first->object->daysOfWeek[temp] != second->object->daysOfWeek[temp])
    {
      if (first->object->daysOfWeek[temp] == true)
        a = temp;
      else
        b = temp;
    }
  }
  if (a != -1)
  {
    first->object->daysOfWeek[a] = false;
    first->object->daysOfWeek[b] = true;
    second->object->daysOfWeek[a] = true;
    second->object->daysOfWeek[b] = false;
  }
}

bool compare(listOfObjects<TrainInfoPerStation *> *first, listOfObjects<TrainInfoPerStation *> *second)
{
  if(first == nullptr || second == nullptr) return true;
  for (int temp = 0; temp < 7; temp++)
  {
    if (first->object->daysOfWeek[temp] != second->object->daysOfWeek[temp])
    {
      if (first->object->daysOfWeek[temp] == true)
        return true;
      else
        return false;
    }
  }

  if (first->object->depTime < second->object->depTime)
    return true;
  else
    return false;

  return false;
}

void quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, int length, listOfObjects<TrainInfoPerStation *> **arr, int arr_len, listOfObjects<TrainInfoPerStation *> *last, int piv_, int K)
{
  if (length == 0 || length == 1)
    return;

  if (length == 2) {
    if (compare(stnInfoList,last)) {
      return;
    }
    else {
      exchange(stnInfoList,last);
      return;
    }
  }

  //std::srand(static_cast<unsigned int>(std::time(nullptr))); 
  int _piv_ = rand() % length;
  if(_piv_ == 0 || _piv_ == length-1) _piv_ = 1;
  int piv = piv_ + _piv_;
  int i = (piv) / K;
  int j = piv % K;

  listOfObjects<TrainInfoPerStation *> *pivot;
  listOfObjects<TrainInfoPerStation *> *active = arr[i];

  for (int temp = 0; temp < K; temp++, active = active->next)
  {
    if (temp == j)
    {
      pivot = active;
      break;
    }
    else if (active->next == nullptr)
    {
      pivot = active;
      break;
    }
  }

  active = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *active_l = last;

  while (true)
  {
    while (compare(active, pivot))
      active = active->next;
    while (compare(pivot, active_l))
      active_l = active_l->prev;
    if (active != pivot && active_l != pivot)
    {
      exchange(active, active_l);
    }
    else if (active == pivot && active_l != pivot)
    {
      if(pivot != stnInfoList) {
        quicksort(stnInfoList, _piv_, arr, arr_len, pivot->prev, piv_, K);
      }
      quicksort(pivot, length - _piv_, arr, arr_len, last, piv, K);
      return;
    }
    else if (active != pivot && active_l == pivot)
    {
      quicksort(stnInfoList, _piv_+1, arr, arr_len, pivot, piv_, K);
      if (pivot != last) {
        quicksort(pivot->next, length - _piv_-1, arr, arr_len, last, piv+1, K);
      }
      return;
    }
    else
    {
      quicksort(stnInfoList, _piv_, arr, arr_len, pivot->prev, piv_, K);
      quicksort(pivot->next, length - _piv_ - 1, arr, arr_len, last, piv + 1, K);
      break;
    }
  }
}
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
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

  static int length = 0;
  int arr_len = 0;
  listOfObjects<TrainInfoPerStation *> *active = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *last;

  if (recursionLevel == 0)
  {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    active = stnInfoList;
    length = 1;

    while (active->next != nullptr)
    {
      length++;
      active = active->next;
    }
    last = active;

    arr_len = (length / K) + 1;
  }

  listOfObjects<TrainInfoPerStation *> *arr[arr_len];

  if (recursionLevel == 0)
  {
    active = stnInfoList;
    for (int temp = 0; active != nullptr; active = active->next, temp++)
    {
      if (temp % K == 0)
      {
        arr[temp / K] = active;
      }
    }
  }

  // Put your code for the core of Quicksort here
  // select pivot
  //std::srand(static_cast<unsigned int>(std::time(nullptr))); 
  int piv = rand() % length;
  if(piv == 0 || piv == length-1) piv = 1;
  int i = (piv) / K;
  int j = piv % K;

  listOfObjects<TrainInfoPerStation *> *pivot;
  active = arr[i];

  for (int temp = 0; temp < K; temp++, active = active->next)
  {
    if (temp == j)
    {
      pivot = active;
      break;
    }
    else if (active->next == nullptr)
    {
      pivot = active;
      break;
    }
  }

  active = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *active_l = last;

  while (true)
  {
    while (compare(active, pivot))
      active = active->next;
    while (compare(pivot, active_l))
      active_l = active_l->prev;
    if (active != pivot && active_l != pivot)
    {
      exchange(active, active_l);
    }
    else if (active == pivot && active_l != pivot)
    {
      if (pivot != stnInfoList) {
        quicksort(stnInfoList, piv, arr, arr_len, pivot->prev, 0, K);
      }
      quicksort(pivot, length - piv, arr, arr_len, last, piv, K);
      return;
    }
    else if (active != pivot && active_l == pivot)
    {
      quicksort(stnInfoList, piv+1, arr, arr_len, pivot, 0, K);
      if (pivot->next != last) {
        quicksort(pivot->next, length - piv-1, arr, arr_len, last, piv+1, K);
      }
      return;
    }
    else
    {
      quicksort(stnInfoList, piv, arr, arr_len, pivot->prev, 0, K);
      quicksort(pivot->next, length - piv - 1, arr, arr_len, last, piv + 1, K);
      break;
    }
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
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

  if (recursionLevel == 0)
  {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
