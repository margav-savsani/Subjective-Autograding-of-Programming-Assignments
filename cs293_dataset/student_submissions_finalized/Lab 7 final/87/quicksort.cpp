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

listOfObjects<TrainInfoPerStation *> * Planner::lastNode(listOfObjects<TrainInfoPerStation*> *start){
    listOfObjects<TrainInfoPerStation*> *ss = start;
    while(ss->next != nullptr){
        ss = ss->next;
    }
    return ss;
}

listOfObjects<TrainInfoPerStation *> * Planner::Partition(listOfObjects<TrainInfoPerStation *> *start){
  listOfObjects<TrainInfoPerStation *> *comp = lastNode(start), *last = lastNode(start);
  listOfObjects<TrainInfoPerStation *> *i = start->prev;
  listOfObjects<TrainInfoPerStation *> *j = start;
  while (j != last){
    if (isLessThan(j, comp)){
      if (i == nullptr) i = start;
      else i = i->next;
      swap(i->object, j->object);
    }
    j = j->next;
  }
    if (i == nullptr) i = start;
    else i = i->next;
    swap(i->object, last->object);
    return i;
}

listOfObjects<TrainInfoPerStation *> * Planner::Partition_rp(listOfObjects<TrainInfoPerStation *> *start, int k){
  listOfObjects<TrainInfoPerStation *> *pivot = pivotChoice(start, k);
  listOfObjects<TrainInfoPerStation *> *last = lastNode(start);
  swap(pivot->object, last->object);
  return Partition(start);
}

bool Planner::isLessThan(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *m){
  int ll, mm, i=0, j=0;
  while (i < 7)
  {
    if ((l->object)->daysOfWeek[i]){
      ll = i;
      break;
    }
    i++;
  }
  while (j < 7)
  {
    if ((m->object)->daysOfWeek[j]){
      mm = j;
      break;
    }
    j++;
  }
  
  if ( ll < mm ){
    return true;
  }
  else if (ll == mm){
    if ((l->object)->depTime < (m->object)->depTime){
      return true;
    }
  }
  return false;
}

void Planner::Swap(TrainInfoPerStation* l, TrainInfoPerStation* m ){
  TrainInfoPerStation temp = *l;
  *l = *m;
  *m = temp;
}

listOfObjects<TrainInfoPerStation *> * Planner::pivotChoice(listOfObjects<TrainInfoPerStation *> *stnInfoList, int k){
  listOfObjects<TrainInfoPerStation *> *last;
  last = lastNode(stnInfoList);
  return last;
}

listOfObjects<TrainInfoPerStation *> ** Planner::Array(listOfObjects<TrainInfoPerStation *> *start, int k){
  int size = 0, i = 0, j = 0;
  listOfObjects<TrainInfoPerStation *> *s = start, *ss = start;
  while (s != nullptr){
    size++;
    s = s->next;
  }
  listOfObjects<TrainInfoPerStation *> ** Arr;
  Arr = new listOfObjects<TrainInfoPerStation *>*[size/k];
  while (ss != nullptr){
    if (i%k == 0){
      Arr[j] = new listOfObjects<TrainInfoPerStation *>(ss->object);
      j++;
    }
    i++;
    ss = ss->next;
  }
  return Arr;
}

void Planner::Qui_sort(listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> *last, int k){
  if (last != nullptr && start != last && start != last->next){
    listOfObjects<TrainInfoPerStation *> *p = Partition_rp(start, k);
    Qui_sort(start, p->prev, k);
    Qui_sort(p->next, last, k);
  }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  listOfObjects<TrainInfoPerStation *> *last = lastNode(stnInfoList), *start = stnInfoList;
  Qui_sort(start, last, K);
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

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
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
