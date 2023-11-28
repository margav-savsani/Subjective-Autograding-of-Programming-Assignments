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

bool compare(TrainInfoPerStation* t1, TrainInfoPerStation* t2){ // implementation of lesser than
  int firstDayOfWeek1=-1, firstDayOfWeek2=-1;
  for(int i = 0; i < 7; i++){
    if(firstDayOfWeek1==-1 && t1->daysOfWeek[i])
      firstDayOfWeek1 = i;
    if(firstDayOfWeek2==-1 && t2->daysOfWeek[i])
      firstDayOfWeek2 = i;
  }
  if(firstDayOfWeek1 == firstDayOfWeek2){
    if(t1->depTime == t2->depTime)
      return t1->arrTime < t2->arrTime;
    return t1->depTime < t2->depTime;
  }
  return firstDayOfWeek1 < firstDayOfWeek2;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation*>** cache = nullptr;
  static int start=-1, end=-1; // star and end indices

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
    int N = 0; // Index counter
    listOfObjects<TrainInfoPerStation*>* currObject = stnInfoList; // Pointer to current object
    int size = 0; // Size of the cache
    while(currObject != nullptr){ // Traverse
      currObject = currObject->next;
      if(N%K == 0) {size++;} // Increase cache size as needed
      N++;
    }
    cache = new listOfObjects<TrainInfoPerStation*>*[size]; // Initialise cache

    int ctr = 0; // Index counter
    currObject = stnInfoList;
    while(currObject != nullptr){ // Traverse
      if(ctr%K == 0){
        cache[ctr/K] = currObject; // Add to cache
      }
      ctr++;
      currObject = currObject->next;
    }

    start = 0; // start is 0
    end = N-1; // start is N-1
  }
  
  // Put your code for the core of Quicksort here
  if(start >= end){ // If number of elements in partition is <= 1, then partition is trivially sorted
    return ;
  } else{
    int pivotIdx = (int)(start + rand()%(end-start+1)); // Choose pivot index randomly
    listOfObjects<TrainInfoPerStation*>* pivot; // Pivot
    listOfObjects<TrainInfoPerStation*>* startObject; // Object at index start
    listOfObjects<TrainInfoPerStation*>* endObject; // Object at index end
    listOfObjects<TrainInfoPerStation*>* traverser = stnInfoList; // Traverser
    int idx = 0; // Index counter
    while(idx <= end){ // Traverse
      if(idx == start){ // If index is start
        startObject = traverser; // startObject found
      }
      if(idx == pivotIdx){ // If index is pivotIdx
        pivot = traverser; // pivot found
      }
      if(idx == end){ // If index is end
        endObject = traverser; // endObject found
      }
      traverser = traverser->next;
      idx++;
    }

    listOfObjects<TrainInfoPerStation*>* currObject = startObject; // Traversing object
    listOfObjects<TrainInfoPerStation*>* terminatorObject = endObject->next; // Object at which to immediately terminate traversing
    while(currObject != pivot){ // Traverse till pivot
      listOfObjects<TrainInfoPerStation*>* nextObject = currObject->next; // Next object
      if(!compare(currObject->object, pivot->object)){ // If currObject >= pivot
        /* Place current object to the right of pivot */
        if(currObject->prev != nullptr){
          currObject->prev->next = currObject->next;
        } else{
          stnInfoList = currObject->next;
        }
        currObject->next->prev = currObject->prev;

        currObject->prev = pivot;
        currObject->next = pivot->next;
        pivot->next = currObject;
        if(currObject->next != nullptr){
          currObject->next->prev = currObject;
        }

        pivotIdx--; // Decrement pivotIdx
      }
      currObject = nextObject;
    }
    currObject = currObject->next; // At pivot now, move to next object
    while(currObject != terminatorObject){ // Traverse till terminator Object
      listOfObjects<TrainInfoPerStation*>* nextObject = currObject->next; // Next object
      if(compare(currObject->object, pivot->object)){ // If currObject < pivot
        /* Place current object to the left of pivot */
        currObject->prev->next = currObject->next;
        if(currObject->next != nullptr){
          currObject->next->prev = currObject->prev;
        }

        currObject->next = pivot;
        currObject->prev = pivot->prev;
        pivot->prev = currObject;
        if(currObject->prev != nullptr){
          currObject->prev->next = currObject;
        }

        if(stnInfoList == pivot){
          stnInfoList = currObject;
        }

        pivotIdx++; // Increment pivotIdx
      }
      currObject = nextObject;
    }

    int start_left = start; // start of left partition
    int end_left = pivotIdx-1; // end of left partition
    int start_right = pivotIdx+1; // start of right partition
    int end_right = end; // end of right partition

    start = start_left; end = end_left; 
    Quicksort(stnInfoList); // Quicksort left partition

    start = start_right; end = end_right;
    Quicksort(stnInfoList); // Quicksort right partition
  }
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
  static listOfObjects<TrainInfoPerStation *>** cache;

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
    int N = 0; // Index counter
    listOfObjects<TrainInfoPerStation*>* currObject = stnInfoList; // Pointer to current object
    int size = 0; // Size of the cache
    while(currObject != nullptr){ // Traverse
      currObject = currObject->next;
      if(N%K == 0) {size++;} // Increase cache size as needed
      N++;
    }
    cache = new listOfObjects<TrainInfoPerStation*>*[size]; // Initialise cache

    int ctr = 0; // Index counter
    currObject = stnInfoList;
    while(currObject != nullptr){ // Traverse
      if(ctr%K == 0){
        cache[ctr/K] = currObject; // Add to cache
      }
      ctr++;
      currObject = currObject->next;
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  if(start >= end){ // If number of elements in partition is <= 1, then partition is trivially sorted
    return ;
  } else{
    int pivotIdx = (int)(start + rand()%(end-start+1)); // Choose pivot index randomly
    listOfObjects<TrainInfoPerStation*>* pivot; // Pivot
    listOfObjects<TrainInfoPerStation*>* startObject; // Object at index start
    listOfObjects<TrainInfoPerStation*>* endObject; // Object at index end
    listOfObjects<TrainInfoPerStation*>* traverser = stnInfoList; // Traverser
    int idx = 0; // Index counter
    while(idx <= end){ // Traverse
      if(idx == start){ // If index is start
        startObject = traverser; // startObject found
      }
      if(idx == pivotIdx){ // If index is pivotIdx
        pivot = traverser; // pivot found
      }
      if(idx == end){ // If index is end
        endObject = traverser; // endObject found
      }
      traverser = traverser->next;
      idx++;
    }

    listOfObjects<TrainInfoPerStation*>* currObject = startObject; // Traversing object
    listOfObjects<TrainInfoPerStation*>* terminatorObject = endObject->next; // Object at which to immediately terminate traversing
    while(currObject != pivot){ // Traverse till pivot
      listOfObjects<TrainInfoPerStation*>* nextObject = currObject->next; // Next object
      if(!compare(currObject->object, pivot->object)){ // If currObject >= pivot
        /* Place current object to the right of pivot */
        if(currObject->prev != nullptr){
          currObject->prev->next = currObject->next;
        } else{
          stnInfoList = currObject->next;
        }
        currObject->next->prev = currObject->prev;

        currObject->prev = pivot;
        currObject->next = pivot->next;
        pivot->next = currObject;
        if(currObject->next != nullptr){
          currObject->next->prev = currObject;
        }

        pivotIdx--; // Decrement pivotIdx
      }
      currObject = nextObject;
    }
    currObject = currObject->next; // At pivot now, move to next object
    while(currObject != terminatorObject){ // Traverse till terminator Object
      listOfObjects<TrainInfoPerStation*>* nextObject = currObject->next; // Next object
      if(compare(currObject->object, pivot->object)){ // If currObject < pivot
        /* Place current object to the left of pivot */
        currObject->prev->next = currObject->next;
        if(currObject->next != nullptr){
          currObject->next->prev = currObject->prev;
        }

        currObject->next = pivot;
        currObject->prev = pivot->prev;
        pivot->prev = currObject;
        if(currObject->prev != nullptr){
          currObject->prev->next = currObject;
        }

        if(stnInfoList == pivot){
          stnInfoList = currObject;
        }

        pivotIdx++; // Increment pivotIdx
      }
      currObject = nextObject;
    }

    QuicksortSimple(stnInfoList, start, pivotIdx-1); // Quicksort left partition
    QuicksortSimple(stnInfoList, pivotIdx+1, end); // Quicksort right partition
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
