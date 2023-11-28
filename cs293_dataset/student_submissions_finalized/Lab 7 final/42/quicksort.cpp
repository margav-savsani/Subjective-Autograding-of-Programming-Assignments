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

bool operator<(TrainInfoPerStation t1, TrainInfoPerStation t2)
{

  for (int i = 0; i < 7; i++)
  {
    if (t1.daysOfWeek[i] < t2.daysOfWeek[i])
      return false;
    else if (t1.daysOfWeek[i] > t2.daysOfWeek[i])
      return true;
  }
  return (t1.arrTime < t2.arrTime);
}

listOfObjects<TrainInfoPerStation *> *goTo(int n, int K, int rand_num, listOfObjects<TrainInfoPerStation *> **&arr, listOfObjects<TrainInfoPerStation *> *&pivot)
{
  int index = (rand_num + K) / (2 * K);
  if (index > (n - 1) / (2 * K))
    index = (n - 1) / (2 * K);
  int diff = rand_num - 2 * K * index;
  pivot = arr[index];
  if (diff > 0)
  {
    for (int i = 0; i < diff; i++)
    {
      pivot = pivot->next;
    }
  }
  else
  {
    for (int i = 0; i < -1 * diff; i++)
    {
      pivot = pivot->prev;
    }
  }
  return pivot;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  listOfObjects<TrainInfoPerStation *> *trav;
  static TrainInfoPerStation *garb;
  static listOfObjects<TrainInfoPerStation *> *pivot;
  static int n = 0;
  static int start = 0;
  static int end = 0;
  static listOfObjects<TrainInfoPerStation *> *start_ptr;
  static listOfObjects<TrainInfoPerStation *> *end_ptr;
  // Increment recursion level on entering the function
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation *> **arr;

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
    n = 0;
    start = 0;
    end = 0;
    trav = stnInfoList;
    while (trav != nullptr)
    {
      n++;
      trav = trav->next;
    }
    trav = stnInfoList;
    arr = new listOfObjects<TrainInfoPerStation *> *[(n - 1) / (2 * K) + 1];
    arr[0] = trav;
    while (trav->next != nullptr)
    {
      end++;
      trav = trav->next;
      if (end % (2 * K) == 0)
      {
        arr[end / (2 * K)] = trav;
      }
    }
    cout<<n<<endl;
    cout<<end<<endl;
  }

  int rand_num = start + (std::rand() % (end - start + 1));
  pivot = goTo(n, K, rand_num, arr, pivot);

  start_ptr = goTo(n, K, start, arr, trav);
  end_ptr = goTo(n, K, end, arr, trav);

  int i = start;
  int j = end;
  int count1 = 0;
  int count2 = 0;

  while (i < j)
  {
    if (count1){
      i++;
      start_ptr = start_ptr->next;
    }
    while (*(start_ptr->object) < *(pivot->object))
    {
      i++;
      start_ptr = start_ptr->next;
    }
    count1++;
    if (count2){
      j--;
      end_ptr = end_ptr->prev;
    }
    while ((*(pivot->object) < *(end_ptr->object)) && j > start)
    {
      j--;
      end_ptr = end_ptr->prev;
    }
    count2++;
    if (i < j)
      std::swap(start_ptr->object, end_ptr->object);
    else{
        if (i == start){
          i++;
          std::swap(start_ptr->object, pivot->object);
          break;
        }
    }
  }

  int pivot_index = i;
  int next_end = end;
  int next_start = start;
  end = i - 1;
  if (start < end) Quicksort(stnInfoList);

  start = pivot_index;
  end = next_end;

  if (start < end) Quicksort(stnInfoList);

  start = next_start;


  // Decrement recursion level before leaving the function
  recursionLevel--;
  if (recursionLevel == -1)
  {
    delete[] arr;
    arr = nullptr;
  }
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
