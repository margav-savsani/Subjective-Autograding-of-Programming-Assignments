#include <time.h>
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
// and departure time within the day (next). Thus Sun 900 < Sun 1100
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
bool lessThan(TrainInfoPerStation *obj1, TrainInfoPerStation *obj2)
{
  for (int i = 0; i < 7; i++)
  {
    if (obj1->daysOfWeek[i] && obj2->daysOfWeek[i])
    {
      // cout<<obj1->object->daysOfWeek[i] << obj2->object->daysOfWeek[i]<<endl;
        // cout<<"hi1"<<endl;
      if (obj1->depTime < obj2->depTime)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else if (obj2->daysOfWeek[i])
    {
      // cout<<"hi2"<<endl;
      // cout<<obj1->object->daysOfWeek[i] << obj2->object->daysOfWeek[i]<<endl;
      return false;
    }
    else if (obj1->daysOfWeek[i])
    {
        // cout<<"hi3"<<endl;
      // cout<<obj1->object->daysOfWeek[i] << obj2->object->daysOfWeek[i]<<endl;
      return true;
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
  static listOfObjects<TrainInfoPerStation *> **checkpoints;
  int length = 1;
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
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
  static listOfObjects<TrainInfoPerStation *> **checkpoints;
  int length = 1;
  if(start<end){
  // cout<<start<<" "<<end<<endl;
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;

  // cout<<recursionLevel<<endl;
  if (recursionLevel == 0)
  {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    while (ptr->next != nullptr)
    {
      length++;
      
      ptr = ptr->next;
    }
    checkpoints = new listOfObjects<TrainInfoPerStation *> *[(length / K) + 1];
    listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;
    int count = 0, index = 0;
    while (ptr != nullptr)
    {
      if (count % K == 0)
      {
        checkpoints[index] = ptr;
        
        index++;
      }
      ptr = ptr->next;
      count++;
    }
  }

  // Put your code for the core of Quicksort here
  srand(time(0));
  int random = start + (rand() % (end - start + 1));
  
  int counter = 0;
  listOfObjects<TrainInfoPerStation *> *ptr2 = checkpoints[random / K];
  while (counter != random % K)
  {
    ptr2 = ptr2->next;
    counter++;
  }
  listOfObjects<TrainInfoPerStation *> *pivot = ptr2;
  counter = 0;
  // pointer from 
  listOfObjects<TrainInfoPerStation *> *j = checkpoints[end/K];
  while (counter != end % K)
  {
    j = j->next;
    
    counter++;
  }
  counter = 0;
  // pointer from First
  listOfObjects<TrainInfoPerStation *> *i = checkpoints[start/K];
  while (counter != start % K)
  {
    i = i->next;
    // cout<<counter<<endl;
    counter++;
  }
  counter = 0;
  
  int partition_index = start;
  int last_index = end;
  TrainInfoPerStation* pivot_object = pivot->object;
  
  while (true)
  {
    while(lessThan(pivot_object, j->object))
    {
      j = j->prev;
      last_index--;
    }
    while (lessThan(i->object, pivot_object))
    {
      i = i->next;
      partition_index++;
    }
    if (partition_index < last_index)
    {
      // cout<<"hi4"<<endl;
      TrainInfoPerStation *temp = i->object;
      i->object = j->object;
      j->object = temp;
      
    }
    else{ 
    // cout<<"partitions"<<partition_index<< " "<<last_index<<endl;
    
    QuicksortSimple(stnInfoList, start, partition_index-1);
    // // cout << "q1" << endl;
    QuicksortSimple(stnInfoList, partition_index + 1, end);
    break;
    }
  }
  // Decrement recursion level before leaving the function
  }
  recursionLevel--;
  return;
}

#endif
