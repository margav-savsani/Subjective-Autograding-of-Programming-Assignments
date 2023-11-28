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

bool isLessThan(TrainInfoPerStation *one, TrainInfoPerStation *two)
{                 // simple comparision operator
  int day1, day2; // final value will be 24*day1 + depTime
  for (int i = 0; i < 7; i++)
  {
    if (one->daysOfWeek[i])
    {
      day1 = i;
      break;
    }
  }
  for (int i = 0; i < 7; i++)
  {
    if (two->daysOfWeek[i])
    {
      day2 = i;
      break;
    }
  }
  return ((2400 * day1) + (one->depTime) < (2400 * day2) + (two->depTime));
}

void swapTrain(listOfObjects<TrainInfoPerStation *> *one, listOfObjects<TrainInfoPerStation *> *two)
{
  // AN ALTERNATE IMPLEMENTATION THAT OCCURRED TO ME IS IN THE COMMENTS BELOW

  // listOfObjects<TrainInfoPerStation *> *onePrev = one->prev;
  // listOfObjects<TrainInfoPerStation *> *oneNext = one->next;
  // listOfObjects<TrainInfoPerStation *> *twoPrev = two->prev;
  // listOfObjects<TrainInfoPerStation *> *twoNext = two->next;

  // if (!(onePrev == NULL))
  //   onePrev->next = two;
  // if (!(oneNext == NULL))
  //   oneNext->prev = two;
  // if (!(twoPrev == NULL))
  //   twoPrev->next = one;
  // if (!(twoNext == NULL))
  //   twoNext->prev = one;

  // one->next = twoNext;
  // one->prev = twoPrev;
  // two->next = oneNext;
  // two->prev = onePrev;

  TrainInfoPerStation *temp = (one->object);
  one->object = (two->object);
  two->object = temp;
}

TrainInfoPerStation *choosePivot(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation *> **sublistArr, int K) // choose a pivot
{
  int leastSublistIndex = (start % K == 0) ? start / K : start / K + 1;  // least multiple of K >= start
  int greatestSublistIndex = (end % K == K - 1) ? end / K : end / K - 1; // greatest multiple of K < end

  if (leastSublistIndex > greatestSublistIndex) // the array to be sorted has very few elements
  {
    if (greatestSublistIndex < 0) // corner case
    {
      greatestSublistIndex = 0;
    }
    // locating "start" in the stnInfoList from the nearest multiple of K
    listOfObjects<TrainInfoPerStation *> *iterator = sublistArr[greatestSublistIndex];
    int iteratorIndex = greatestSublistIndex * K;
    int pivotIndex = start + rand() % (end - start + 1);
    for (; iteratorIndex < pivotIndex; iteratorIndex++)
    {
      iterator = iterator->next;
    }
    // iterator is now at pivot
    return iterator->object;
  }
  else
  {
    // first pick randomly from [lSI, gSI]
    int sublistPivotIndex = leastSublistIndex + rand() % (greatestSublistIndex - leastSublistIndex + 1);
    listOfObjects<TrainInfoPerStation *> *sublistPivot = sublistArr[sublistPivotIndex];
    // then pick randomly from [0, K-1]
    int randK = rand() % K;
    for (int i = 0; i < randK; i++)
    {
      sublistPivot = (sublistPivot->next);
    }
    return sublistPivot->object;
  }
}

int Planner::Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation *> **sublistArr, int K, TrainInfoPerStation *pivot) // Partition the first K elements starting from subList by naveen sir algorithm
{
  int startSublistIndex = start / K; // greatest multiple of K <= start
  int endSublistIndex = end / K;     // greates multiple of K <= end
  listOfObjects<TrainInfoPerStation *> *startIterator = sublistArr[startSublistIndex];
  listOfObjects<TrainInfoPerStation *> *endIterator = sublistArr[endSublistIndex];
  for (int i = K * (start / K); i < start; i++)
  {
    startIterator = startIterator->next;
  }
  for (int i = K * (end / K); i < end; i++)
  {
    endIterator = endIterator->next;
  }
  int startIteratorIndex = start;
  int endIteratorIndex = end;
  while (true)
  {
    while (endIteratorIndex >= start && !isLessThan((endIterator->object), pivot))
    {
      endIterator = endIterator->prev;
      endIteratorIndex--;
    }
    while (startIteratorIndex <= end && isLessThan((startIterator->object), pivot))
    {
      startIterator = startIterator->next;
      startIteratorIndex++;
    }
    if (startIteratorIndex < endIteratorIndex)
    {
      swapTrain(startIterator, endIterator);
      // AN ALTERNATE IMPLEMENTATION THAT OCCURRED TO ME
      // listOfObjects<TrainInfoPerStation *> *temp = startIterator; // need to swap pointers also
      // startIterator = endIterator;
      // endIterator = temp;

      // if (startIteratorIndex == 0)  // need to modify stnInfoList
      // {

      // }

      // if (startIteratorIndex % K == 0 && endIteratorIndex % K != 0)
      // { // need to swap sublistArr pointers also
      //   sublistArr[startIteratorIndex / K] = startIterator;
      // }
      // else if (startIteratorIndex % K != 0 && endIteratorIndex % K == 0)
      // { // need to swap sublistArr pointers also
      //   sublistArr[endIteratorIndex / K] = endIterator;
      // }
      // else if (startIteratorIndex % K == 0 && endIteratorIndex % K == 0)
      // { // need to swap sublistArr pointers also
      //   sublistArr[startIteratorIndex / K] = startIterator;
      //   sublistArr[endIteratorIndex / K] = endIterator;
      // }
    }
    else
    {
      return endIteratorIndex;
    }
  }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  int size = 0;
  listOfObjects<TrainInfoPerStation *> *iterator = stnInfoList;
  while (iterator != NULL)
  {
    size++;
    iterator = iterator->next;
  }
  QuicksortSimple(stnInfoList, 0, size - 1);
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **sublistArr = NULL;
  static int size;

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

  if (recursionLevel == 0) // I will store the 0th, kth, 2kth elements of the stninfoList in a separate list called sublistArr (list of sublists)
  {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    srand(1); // determinate output
    size = end - start + 1;
    sublistArr = (listOfObjects<TrainInfoPerStation *> **)malloc(((end - start + 1) / K + 1) * sizeof(listOfObjects<TrainInfoPerStation *> *));
    listOfObjects<TrainInfoPerStation *> *mainIterator = stnInfoList;
    for (int i = start; i <= end; i++)
    { // start = 0 and end = size - 1
      if (i % K == 0)
      {
        memcpy(&sublistArr[i / K], &(mainIterator), sizeof(listOfObjects<TrainInfoPerStation *> *));
      }
      mainIterator = mainIterator->next;
    }
    // as of now sublistArr contains every kth element
  }

  // Put your code for the core of QuicksortSimple here
  if (start >= end)
  {
    recursionLevel--;
    return;
  }
  // now start < end
  TrainInfoPerStation *pivot = choosePivot(stnInfoList, start, end, sublistArr, K);
  int middle = Partition(stnInfoList, start, end, sublistArr, K, pivot);
  QuicksortSimple(stnInfoList, start, middle);
  if (middle == start - 1)
  {
    // check if array has all identical elements
    bool allIdentical = true;
    int startSublistIndex = start / K; // greatest multiple of K <= start
    listOfObjects<TrainInfoPerStation *> *startIterator = sublistArr[startSublistIndex];
    for (int i = K * (start / K); i < start; i++)
    {
      startIterator = startIterator->next;
    }
    int startIteratorIndex = start;
    while (startIteratorIndex < end)
    {
      if (!(!isLessThan(startIterator->object, startIterator->next->object) && !isLessThan(startIterator->next->object, startIterator->object))) // if they are unequal
      {
        allIdentical = false;
        break;
      }
      startIterator = startIterator->next;
      startIteratorIndex++;
    }
    if (allIdentical)
    {
      recursionLevel--;
      return;
    }
  }
  QuicksortSimple(stnInfoList, middle + 1, end);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
