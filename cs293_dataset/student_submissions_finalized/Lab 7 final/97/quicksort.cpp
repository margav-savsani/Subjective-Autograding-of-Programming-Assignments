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
#include <random>

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
  int end = 0;
  listOfObjects<TrainInfoPerStation *> * temp = stnInfoList;
  while(temp != nullptr){
      temp = temp ->next;
      end++;
  }
  QuicksortSimple(stnInfoList, 0, end-1);
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

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}
// assigns a number to the days in the week, used to order the days in the list
int arrToInt(bool* arr, int n){
  int i, k = 0;
  for (i = 0; i < n; i++)
      k = 10 * k + arr[i];
  return k;
}
//Partitions the linked list around the random pivot selected, returns the index of the pivot
int Planner::partition(vector<listOfObjects<TrainInfoPerStation* >* > ptr, int k, int start, int end){
  //this is used in creating a random distribution
  random_device dev;
  mt19937 rng(dev());
  // Base case, ends call if incorrect input
  if(start > end){
    return start;
  }
  //uniform distribution
  uniform_int_distribution<mt19937::result_type> dist1(start, end);
  int num = dist1(rng);
  int a = num/k;
  listOfObjects<TrainInfoPerStation* >* curr = ptr[a], *pivot,*first= ptr[start/k], *last= ptr[end/k];
  //initialize the front pointer
  for(int i = 0; i < start%k; i++){
    first = first->next;
  }
  //initialize the back pointer
  for(int i = 0; i < end%k; i++){
    if(last->next == nullptr)
      break;
    last = last->next;
  }
  //correctly position the pivot pointer
  for(int i = 0; i < num%k; i++){
    if(curr->next == nullptr){
        break;
    }
    curr = curr->next;
  }
  pivot = curr;
  //loopp to peform partition
  while(true){
    while(arrToInt(first->object->daysOfWeek, 7) > arrToInt(pivot->object->daysOfWeek, 7))
      first = first->next;
    
    while(arrToInt(last->object->daysOfWeek, 7) < arrToInt(pivot->object->daysOfWeek, 7))
      last = last->prev;
    //swap elements if position is improper
    if(arrToInt(first->object->daysOfWeek, 7) < arrToInt(last->object->daysOfWeek, 7)){
      TrainInfoPerStation* temp = first->object;
      first->object = last->object;
      last->object = temp;
      if(pivot->object == first->object)
        pivot = last;
      else if(pivot->object == last->object)
        pivot = first;
    }
    // if the values are the same, they can either be coincident with the pivot, or 2 trains on the same day might exist
    if(arrToInt(first->object->daysOfWeek, 7) == arrToInt(last->object->daysOfWeek, 7)){
      //if the 2 objects are coincident, the partition process is complete, and can return to calling function
      if(first->object == last->object){
        listOfObjects<TrainInfoPerStation* >* check = ptr[0];
        //finds the index of the pivot in the list
        int idx = 0;
        while(check != pivot){
          check = check->next;
          idx++;
        }
        return idx;
      }
      else{
        //if there are 2 trains on the same day, then compare their time and swap them if necessary
        if(first->object->arrTime  > last->object->arrTime){
          TrainInfoPerStation* temp = first->object;
          first->object = last->object;
          last->object = temp;
          if(pivot->object == first->object)
            pivot = last;
          else if(pivot->object == last->object)
            pivot = first;
        }
        //continues the partitioning
        if(first != pivot)
          first = first->next;
        if(last != pivot)
          last = last->prev;
      } 
    }
  }
}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  //static variable defined here
  static vector<listOfObjects<TrainInfoPerStation* >* > ptr;
  recursionLevel++;
  
  if (recursionLevel == 0) {
    // Allocates additional n/K + 1 space and stores it in a vector, as they are a safer form of memory allocation
    listOfObjects<TrainInfoPerStation* > *temp = stnInfoList;
    int i = 0;
    while(temp->next != nullptr){
      if(i % K == 0){
          ptr.push_back(temp);
      }
      temp = temp->next;
      i++;
    }
    ptr.push_back(temp);
  }
  // recursive calls to function to quicksort
  if(start < end){
    int pivot = partition(ptr, K,  start, end);
    QuicksortSimple(stnInfoList, start, pivot-1);
    QuicksortSimple(stnInfoList, pivot+1, end);
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
