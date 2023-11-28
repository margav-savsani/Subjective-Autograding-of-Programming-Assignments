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

#include <cstdlib>
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

int Planner::Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int finish, listOfObjects<TrainInfoPerStation *> *pivot)
{
  // Setting the Day and deptarture time variable so that I don't
  // need to access the pivot everytime I want to use it for comparison
  // which is quite often
  int Day, dept_time;
  dept_time = pivot->object->depTime;

  // Loop to check on which day the train runs
  for (int day = 0; day < 7; day++)
  {
    if (pivot->object->daysOfWeek[day])
    {
      Day = day;
      break;
    }
  }

  // Starting my main partition function similar to any quicksort partition
  int i = start;
  // In array simply updating i works but here I need to keep track of pointer too
  // so that I can perform the exchnage of the object
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  for (int j = start; j < finish; j++)
  {
    // Setting the Day and deptarture time variable so that I don't
    // need to access the iterator everytime I want to use it for comparison and exchange
    int Day_iter, dept_time_iter;
    dept_time_iter = stnInfoList->object->depTime;

    // Loop to check on which day the train runs
    for (int day = 0; day < 7; day++)
    {
      if (stnInfoList->object->daysOfWeek[day])
      {
        Day_iter = day;
        break;
      }
    }

    // First checking the condition based on the day of departure
    if (Day_iter < Day)
    {
      // Swap the value

      // If day of iterator is less than day of pivot, then I perform the
      // exchange of the small element location with the current element
      TrainInfoPerStation *changing_obj = temp->object;
      temp->object = stnInfoList->object;
      stnInfoList->object = changing_obj;

      // In the end update temp similarly to i
      i++;
      temp = temp->next;
    }
    // Other possibility would be based on time of departure on same day
    else if (Day_iter == Day)
    {
      // If the day is same then compare the departure time
      if (dept_time_iter < dept_time)
      {
        // Swap the value

        // If departure time of iterator is less than departure time of pivot, then I perform the
        // exchange of the small element location with the current element
        TrainInfoPerStation *changing_obj = temp->object;
        temp->object = stnInfoList->object;
        stnInfoList->object = changing_obj;

        // In the end update temp similarly to i
        i++;
        temp = temp->next;
      }
    }
    // Finally update the iterator pointer
    stnInfoList = stnInfoList->next;
  }
  // Finally swap the pivot with its current location
  TrainInfoPerStation *changing_obj = temp->object;
  temp->object = pivot->object;
  pivot->object = changing_obj;

  // Returns the index value of the pivot's current location
  return i;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Creating an array to store the N/K pointers to list of objects
  static listOfObjects<TrainInfoPerStation *> **compress_array;

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
  // overall. So you MUST NOT allocate space in each recursive call.
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

    // Setting up the pre-processing steps
    srand(time(0));
    listOfObjects<TrainInfoPerStation *> *iter = stnInfoList;

    // n is the count of elements in the list
    int n = end + 1;

    // An array storing the pointer to the list of objects

    // Two cases based on how many elements are to be stored
    if (n % K != 0)
    {
      compress_array = new listOfObjects<TrainInfoPerStation *> *[(n / K) + 1];
    }
    else
    {
      compress_array = new listOfObjects<TrainInfoPerStation *> *[n / K];
    }

    // After initialising the array in above steps
    // populating the array with the pointer values
    int k = 0;
    iter = stnInfoList;
    while (k != n)
    {
      // Storing only those pointers that are in step of K
      if (k % K == 0)
      {
        compress_array[k / K] = iter;
      }
      k++;
      iter = iter->next;
    }
  }

  // Base case would be if start >= end, in that case return void

  // Perform the recursion calls when base case is not achieved
  if (start < end)
  {
    // Generating the random pivot in O(K) time
    int pivot = start + (rand() % (end - start + 1));

    // iter would be the pointer to pivot node
    listOfObjects<TrainInfoPerStation *> *iter;
    iter = compress_array[pivot / K];
    for (int j = 0; j < pivot % K; j++)
    {
      iter = iter->next;
    }

    // Taking pivot to the last node
    TrainInfoPerStation *exch = iter->object;
    listOfObjects<TrainInfoPerStation *> *demo = compress_array[end / K];
    for (int m = 0; m < end % K; m++)
    {
      demo = demo->next;
    }
    // Performing the exchange
    iter->object = demo->object;
    demo->object = exch;

    // after the exchange of the location of pivot value, my new pivot node
    // pointer is demo

    // Note here pivot_place means the final sorted location of the
    // pivot that was generated in the partition
    int pivot_place = Partition(stnInfoList, start, end, demo);

    // using the correct pivot location index, I go to the right node of the pivot
    // so that I can call the quicksortsimple on it, iter here is that node
    iter = compress_array[pivot_place / K];
    for (int j = 0; j < pivot_place % K; j++)
    {
      iter = iter->next;
    }

    // recursively calling the quicksort for the left side of pivot list
    // and the right side of the pivot list
    QuicksortSimple(stnInfoList, start, pivot_place - 1);
    QuicksortSimple(iter->next, pivot_place + 1, end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}
#endif
