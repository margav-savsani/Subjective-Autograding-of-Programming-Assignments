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
#include <ctime>

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
  
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  int piv_idx = 0;
  
  // Put your code for the core of Quicksort here


  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = (rand()%(end+1))+1; // Parameter to be experimented with

  //cout<< end << endl;
  //cout << K << endl;
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;

  int total = 0;  // extra variables initialised to use in iteration of loops, etc.
  int idx = 0;
  int itr = 0;
  int endd = end;
  int day_ele = 0;
  int day_pivot = 0;
  int day_start = 0;

  if(start == end){  // if only one element in list, then return
    return;
  }

  static listOfObjects<TrainInfoPerStation *> **piv_option;  // array of listOfObjects<TrainInfoPerStation *> to store K evenly spaced pointers of the objects in the linked list given 

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

  //cout << "cj dfhxnjsn" << endl;
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    //initialise the array with size according to the values of 'n' and 'K' (here n = end+1)
    if(end+1 > K){
      piv_option = new listOfObjects<TrainInfoPerStation*>*[((end+1)/K)+1];
    }
    if(end+1 == K){
     piv_option = new listOfObjects<TrainInfoPerStation*>*[((end+1)/K)];
    }

    if(stnInfoList->object == nullptr){ // base case
      return;
    }

    while(total < end+1){ //store K spaced objects from the linked list into the array we just formed
      if(total%K == 0){   // variable "total" is used to keep track of evenly spaced elements.
        piv_option[idx] = stnInfoList;
        idx++;
      }
      total++;
      stnInfoList = stnInfoList->next;  
    }
  }

  int piv_idx; //stores the random number generated between 0 to end

  if(end+1 > K){
    piv_idx = rand()%(end+1);  //
  }
  else if(end+1 == K){
    piv_idx = 0;
  }

  listOfObjects<TrainInfoPerStation *>  *extra;
  listOfObjects<TrainInfoPerStation *> *pivot;
  while(itr < piv_idx%K){
    piv_option[piv_idx/K] = piv_option[piv_idx/K]->next;
    itr++;
  }

  pivot = piv_option[piv_idx/K];

    while(piv_option[((end+1)/K)]->next != nullptr){
      piv_option[((end+1)/K)] = piv_option[((end+1)/K)]->next;
    }

  cout<< "hxasgdy" << endl;

    while(true){

      
      for(int i=0; i<7; i++){
        if(piv_option[((end+1)/K)]->object->daysOfWeek[i] == true){
          day_ele = i;
          break;
        }
      }
      for(int i=0; i<7; i++){
        if(pivot->object->daysOfWeek[i] == true){
          day_pivot = i;
          break;
        }
      }
      for(int i=0; i<7; i++){
        if(piv_option[start]->object->daysOfWeek[i] == true){
          day_start = i;
          break;
        }
      }

    cout<< "hxasgdy" << endl;
      while(!(day_ele <= day_pivot)){
        piv_option[((end+1)/K)] = piv_option[((end+1)/K)]->prev;
        for(int i=0; i<7; i++){
        if(piv_option[((end+1)/K)]->object->daysOfWeek[i] == true){
          day_ele = i;
          break;
        }
        }
        end--;
      }
      // while(!(piv_option[((end+1)/K)+1]->object->depTime <= pivot->object->depTime)){
      //   piv_option[((end+1)/K)+1] = piv_option[((end+1)/K)+1]->prev;
      //   end--;
      // }

      while(!(day_start >= day_pivot)){
        piv_option[start] = piv_option[start]->next;
        for(int i=0; i<7; i++){
        if(piv_option[start]->object->daysOfWeek[i] == true){
          day_start = i;
          break;
          cout<< "hxasgdy" << endl;
        }
        }
        start++;
      }

      // while(!(piv_option[start]->object->depTime >= pivot->object->depTime)){
      //   piv_option[start] = piv_option[start]->next;
      //   start++;
      // }
      if(start < end){
        extra = piv_option[start];
        piv_option[start] = piv_option[((end+1)/K)];
        piv_option[((end+1)/K)] = extra;
      }
      else{
        break;
      }
    }
    
    QuicksortSimple(stnInfoList, 0, end);
    QuicksortSimple(stnInfoList, end+1, endd);

    int check = 0;
    int day1 = 0;
    int day2 = 0;
    int str = 0;
    while(check<endd+1){
      for(int i=0; i<7; i++){
        if(piv_option[str]->object->daysOfWeek[i] == true){
          day1 = i;
          break;
        }
      }
      for(int i=0; i<7; i++){
        if(piv_option[str]->next->object->daysOfWeek[i] == true){
          day2 = i;
          break;
        }
      }
      if(day1 ==day2){
        if(piv_option[str]->object->depTime > piv_option[str]->next->object->depTime){
          extra = piv_option[str];
          piv_option[str] = piv_option[str]->next;
          piv_option[str]->next = extra;
        }
      }
      piv_option[str] = piv_option[str]->next;
      piv_option[str]->next = piv_option[str]->next->next;
    }


  
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
