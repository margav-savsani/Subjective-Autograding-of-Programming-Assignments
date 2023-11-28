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
//#include<time.h>
//#include<cstdlib>

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

// Returns the value stored at the station
int value(TrainInfoPerStation *a)
{
  // cout<<"dept"<<a->depTime<<endl;
  for (int i = 0; i < 7; i++)
  {
    if (a->daysOfWeek[i])
      return i * 2400 + a->depTime;
  }
  return 0;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // cout << "Calling quicksort with " << start << " " << end << endl;
  static int start = 0;
  static int end = 0;

  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;

  static listOfObjects<TrainInfoPerStation *> **a;

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
    start = 0;
    listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;

    while (curr->next != NULL)
    {
      end++;
      curr = curr->next;
    }

    int n = (end - start + 1) / K + 1;
    a = new listOfObjects<TrainInfoPerStation *> *[n];
    // cout << "Array formed" << endl;
    // for (int i = 0; i < n; i++)
    //   a[i] = NULL;
    curr = stnInfoList;

    for (int i = 0; i < n; i++)
    {
      a[i] = curr;
      if (i == n - 1)
      {
        break;
      }
      for (int j = 0; j < K; j++)
      {
        curr = curr->next;
      }
    }
  }
  if (start >= end)
  {
    recursionLevel--;
    return;
  }
  // srand(time(0));
  int pivotnum = rand() % (end - start + 1) + start;
  // //cout << pivotnum << endl;
  int index = pivotnum / K;
  listOfObjects<TrainInfoPerStation *> *pivot = a[index];
  int remainder = pivotnum % K;
  // cout << "pivot" << pivotnum << endl;
  while (remainder > 0)
  {
    pivot = pivot->next;
    // cout << pivot->object->depTime << endl;
    remainder--;
  }
  // cout << "haha" << endl;
  int x = value(pivot->object);
  // cout << "haha" << endl;
  int i = start;
  int j = end;
  listOfObjects<TrainInfoPerStation *> *front = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *back = stnInfoList;
  for (int k = start; k < end; k++)
  {
    back = back->next;
  }
  swap(back->object, pivot->object);

  while (true)
  { // //cout<<"shifting"<<endl;
    while ((value(back->object) > x) && back != NULL)
    { // //cout<<"Entered"<<endl;
      // cout << "j" << j << endl;
      j--;
      back = back->prev;
    }
    while ((value(front->object) <= x) && front != NULL)
    {
      // cout << "i" << i << endl;
      i++;
      front = front->next;
      if (i >= j)
        break;
    }
    if (i < j)
    {
      swap(back->object, front->object);
    }
    else
      break;
  }
  int end1 = end;
  int start1 = start;
  if (j == end)
  {
    end = end - 1;
    Quicksort(stnInfoList);
  }
  else
  {
    end = j;
    Quicksort(stnInfoList);
    start = j + 1;
    end = end1;
    Quicksort(back->next);
  }

  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  // cout << recursionLevel << endl;
  end = end1;
  start = start1;
  recursionLevel--;
  // cout << "party" << endl;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // cout << "Calling quicksort with " << start << " " << end << endl;

  if (start >= end)
  {
    return;
  }
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;

  static listOfObjects<TrainInfoPerStation *> **a;

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
    int n = (end - start + 1) / K + 1;
    a = new listOfObjects<TrainInfoPerStation *> *[n];
    // cout << "Array formed" << endl;
    // for (int i = 0; i < n; i++)
    //   a[i] = NULL;
    listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;

    for (int i = 0; i < n; i++)
    {
      a[i] = curr;
      if (i == n - 1)
      {
        break;
      }
      for (int j = 0; j < K; j++)
      {
        curr = curr->next;
      }
    }
  }

  // srand(time(0));
  int pivotnum = rand() % (end - start + 1) + start;
  // //cout << pivotnum << endl;
  int index = pivotnum / K;
  listOfObjects<TrainInfoPerStation *> *pivot = a[index];
  int remainder = pivotnum % K;
  // cout << "pivot" << pivotnum << endl;
  while (remainder > 0)
  {
    pivot = pivot->next;
    // cout << pivot->object->depTime << endl;
    remainder--;
  }
  // cout << "haha" << endl;
  int x = value(pivot->object);
  // cout << "haha" << endl;
  int i = start;
  int j = end;
  listOfObjects<TrainInfoPerStation *> *front = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *back = stnInfoList;
  for (int k = start; k < end; k++)
  {
    back = back->next;
  }
  swap(back->object, pivot->object);

  while (true)
  { // //cout<<"shifting"<<endl;
    while ((value(back->object) > x) && back != NULL)
    { // //cout<<"Entered"<<endl;
      // cout << "j" << j << endl;
      j--;
      back = back->prev;
    }
    while ((value(front->object) <= x) && front != NULL)
    {
      // cout << "i" << i << endl;
      i++;
      front = front->next;
      if (i >= j)
        break;
    }
    if (i < j)
    {
      swap(back->object, front->object);
    }
    else
      break;
  }
  if (j == end)
  {
    QuicksortSimple(stnInfoList, start, j - 1);
  }
  else
  {
    QuicksortSimple(stnInfoList, start, j);
    QuicksortSimple(back->next, j + 1, end);
  }

  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  // cout << recursionLevel << endl;

  recursionLevel--;
  // cout << "party" << endl;
  return;
}

#endif
