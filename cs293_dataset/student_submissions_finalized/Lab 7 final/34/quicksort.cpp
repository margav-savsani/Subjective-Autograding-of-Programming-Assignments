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

  //the following three variables are defined for quicksort operation.
  listOfObjects<TrainInfoPerStation *> *list_end = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *list_start = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *list_front = stnInfoList;
  
  // the below variables start and end will act as the parameter provided in QuickSortSimple.
  static int start = 0;
  static int end = 0;
  // When recursionlevel is zero, I initialized the end since in next recursion I can modify it according to pivot_index.
  // Simillarly assigned correct value to list_end.
  if(recursionLevel == 0){
    while(list_end->next != nullptr){
      list_end = list_end->next;
      end++;
    }
  }
  else{
    for(int i = start; i < end; i++){
      list_end = list_end->next;
    }
  }
  // when the recursive call will end the values will be restored to previous values of temp_start and temp_end.
  int temp_start = start;
  int temp_end = end;

  

  int size_list = end - start + 1;
  int size_arr = 1 + size_list/K;
  if(size_list < 2){
    recursionLevel--;
    return;
  }
  static listOfObjects<TrainInfoPerStation *>**K_array = new listOfObjects<TrainInfoPerStation *>*[size_arr];

  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
    for(int i = 0; i < size_list; i++){
      if(i%K == 0){
        K_array[i/K] = temp;
      }
      temp = temp->next;
    }
  }
  
  // Put your code for the core of Quicksort here

  //calculating pivot.
  int pivot_index = start + rand() % size_list;
  int nth_K_index = pivot_index / K;
  int kth = pivot_index % K;

  listOfObjects<TrainInfoPerStation *> *pivot = K_array[nth_K_index];
  for(int i = 0; i < kth; i++){
    pivot = pivot->next;
  }
  TrainInfoPerStation* temp = pivot->object;
  pivot->object = list_end->object;
  list_end->object = temp;
  
  int pivot_day;
  for(int i = 0; i < 7; i++){
    if(list_end->object->daysOfWeek[i])pivot_day = i;
  }
  //partitioning wrt pivot.
  pivot_index = start;
  for(int i = start; i < end; i++){
    int stn_day;
    for(int i = 0; i < 7; i++){
      if(list_start->object->daysOfWeek[i])stn_day = i;
    }
    if(pivot_day > stn_day){
      temp = list_start->object;
      list_start->object = list_front->object;
      list_front->object = temp;
      list_front = list_front->next;
      pivot_index++;
    }
    else if(pivot_day == stn_day){
      if(list_end->object->depTime > list_start->object->depTime){
        temp = list_start->object;
        list_start->object = list_front->object;
        list_front->object = temp;
        list_front = list_front->next;
        pivot_index++;
      }
    }
    list_start = list_start->next;
  }
  temp = list_end->object;
  list_end->object = list_front->object;
  list_front->object = temp;
  // Decrement recursion level before leaving the function
  end = pivot_index - 1;
  Quicksort(stnInfoList);
  end = temp_end;
  start = pivot_index + 1;
  Quicksort(list_front->next);
  //restoring values to start and end.
  start = temp_start;
  end = temp_end;
  recursionLevel--;
  if(recursionLevel == -1){
    end = 0;
  }
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
  int size_list = end - start + 1;
  int size_arr = 1 + size_list/K;
  if(size_list < 2){
    recursionLevel--;
    return;
  }
  static listOfObjects<TrainInfoPerStation *>**K_array = new listOfObjects<TrainInfoPerStation *>*[size_arr];
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
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
    for(int i = 0; i < size_list; i++){
      if(i%K == 0){
        K_array[i/K] = temp;
      }
      temp = temp->next;
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  int pivot_index = start + rand() % size_list;
  int nth_K_index = pivot_index / K;
  int kth = pivot_index % K;

  listOfObjects<TrainInfoPerStation *> *pivot = K_array[nth_K_index];
  for(int i = 0; i < kth; i++){
    pivot = pivot->next;
  }

  listOfObjects<TrainInfoPerStation *> *list_end = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *list_start = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *list_front = stnInfoList;

  for(int i = start; i < end; i++){
    list_end = list_end->next;
  }

  TrainInfoPerStation* temp = pivot->object;
  pivot->object = list_end->object;
  list_end->object = temp;
  
  int pivot_day;
  for(int i = 0; i < 7; i++){
    if(list_end->object->daysOfWeek[i])pivot_day = i;
  }
  pivot_index = start;
  for(int i = start; i < end; i++){
    int stn_day;
    for(int i = 0; i < 7; i++){
      if(list_start->object->daysOfWeek[i])stn_day = i;
    }
    if(pivot_day > stn_day){
      temp = list_start->object;
      list_start->object = list_front->object;
      list_front->object = temp;
      list_front = list_front->next;
      pivot_index++;
    }
    else if(pivot_day == stn_day){
      if(list_end->object->depTime > list_start->object->depTime){
        temp = list_start->object;
        list_start->object = list_front->object;
        list_front->object = temp;
        list_front = list_front->next;
        pivot_index++;
      }
    }
    list_start = list_start->next;
  }
  temp = list_end->object;
  list_end->object = list_front->object;
  list_front->object = temp;
  QuicksortSimple(stnInfoList, start, pivot_index-1);
  QuicksortSimple(list_front->next, pivot_index+1, end);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
