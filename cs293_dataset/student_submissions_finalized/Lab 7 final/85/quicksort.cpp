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

listOfObjects<TrainInfoPerStation *> *Planner::choose(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  int f;
  if ((end - start) <= 4)
  {
    f = 1;
  }
  if ((end - start) % 4 == 0)
  {
    f = (end - start) / 4;
  }
  else
  {
    f = (end - start) / 4;
    f++;
  }

  listOfObjects<TrainInfoPerStation *> *arr[f];

  static listOfObjects<TrainInfoPerStation *> *c;

  c = stnInfoList->next;
  
  int v = 0;
  for (int i = 0; i < f; i++)
  {
    arr[i] = c;
     
    for (int u = 0; u < 3; u++)
    {
      while (c->next != NULL)
      {
        c = c->next;
      }
    }
  }
  
  int y = random() % (f + 1);
  return arr[y]->next;
}
int dayno(listOfObjects<TrainInfoPerStation *> *n){
  int a;
  int b;
  for(a=0;a<7;a++){
    if(n->object->daysOfWeek[a]==true){b=a;}
    
  }
  return b;
}
int Planner::partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  if(start >= end) {return -1;}
  int search=0;
  static listOfObjects<TrainInfoPerStation *> *starting;
  static listOfObjects<TrainInfoPerStation *> *ending;
  while(stnInfoList != nullptr)
  {
    if(search == start) {starting = stnInfoList;}
    else if(search == end) {ending = stnInfoList;}
    stnInfoList = stnInfoList->next;
    search++;
  }
 
  static listOfObjects<TrainInfoPerStation *> *pivot=starting->next->next;
  
  static TrainInfoPerStation *trial = pivot->object;
  pivot->object = ending->object;
  ending->object = trial;

  int left = start; int right = end;
  int pivotday = dayno(ending);
  int deptime = ending->object->depTime;
   while(true)
  {
        while ((pivotday <= dayno(ending)) && (right > start))
        {
            if(pivotday == dayno(ending))
            {
              if(deptime > ending->object->depTime) break;
              else{
                ending = ending->prev;
                right--;
              }
            }
            else
            {
            ending = ending->prev;
            right--;
            }
        }
        
        while ((pivotday >= dayno(starting)) && (left < end))
        {
            if(pivotday == dayno(starting))
            {
              if(deptime < starting->object->depTime) break;
              else{
                starting = starting->next;
                left++;
              }
            }
            else
            {
            starting = starting->next;
            left++;
            }
        }
        if (left < right)
        {
            TrainInfoPerStation *just = new TrainInfoPerStation(1,1,1,1);
            listOfObjects<TrainInfoPerStation *> *temp=new listOfObjects<TrainInfoPerStation *>(just);
            temp->object=ending->object;
            ending->object=starting->object;
            starting->object=temp->object;
        }
        else
            {return right;}
  }
  return right;
  }
          

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  // recursionLevel++;

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
  /**
    if (recursionLevel == 0)
    {
      // Allocate additional space for upto n/K TrainInfoPerStation objects
      // if needed.
      // Do other things that you may want to do only at the beginning
      // as a pre-processing step.
    }
  */
  // Put your code for the core of QuicksortSimple here
  if (start >= end)
  {
    return;
  }
  else
  {

    int pivot = partition(stnInfoList, start, end);

    if (pivot >= end)
    {
      QuicksortSimple(stnInfoList, start, pivot - 1);
      return;
    }
    else
    {
      QuicksortSimple(stnInfoList, start, pivot);
      QuicksortSimple(stnInfoList, pivot + 1, end);
      return;
    }
  }
  // Decrement recursion level before leaving the function
  // recursionLevel--;
}

#endif
