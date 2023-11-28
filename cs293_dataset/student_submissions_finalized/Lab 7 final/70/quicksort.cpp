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
int findTrueDay(TrainInfoPerStation* stn){
  int trueDay = 1;
  for(int i = 0; i < 7; i++){
    if(stn->daysOfWeek[i]) break;
    trueDay++;
  }
  return trueDay;
}
listOfObjects<TrainInfoPerStation*> * findMyElement(listOfObjects<TrainInfoPerStation*>** nByKarray, int pos, int K){
  listOfObjects<TrainInfoPerStation*> *holder = nByKarray[(int)(pos/K)];
  listOfObjects<TrainInfoPerStation*> *element = nByKarray[(int)(pos/K)];
  int counterToElem = ((pos - ((int)(pos/K)*K)) % K);
  while(counterToElem > 0){
    element = element->next;
    counterToElem--;
  }
  nByKarray[(int)(pos/K)] = holder;
  return element;
}
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
    
    //finding number of elements in the listOfObjects
    }

    //creating an array to store pointers to 
    //first TrainInfoPerStation object of each n/K groups of elements
  
  // Put your code for the core of Quicksort here

  //choosing a random pivot


  // Decrement recursion level before leaving the function
  recursionLevel--; //don't know why
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
  if(start >= end) return;
  
  static int lengthOfBigList;
  static listOfObjects<TrainInfoPerStation*>** nByKarray;
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

    //creating an array to store pointers to 
    //first TrainInfoPerStation object of each n/K groups of elements
    lengthOfBigList = end - start + 1;
    nByKarray = new listOfObjects<TrainInfoPerStation*>* [(int)(lengthOfBigList/K)];
    int extraSpace = 0;
    int spearator = 1;
    listOfObjects<TrainInfoPerStation*> *tempElements = stnInfoList;
    if(lengthOfBigList > 0){
      nByKarray[0] = stnInfoList;
      extraSpace++;
    }
    while(stnInfoList!=nullptr){
      if(spearator == K+1){
        spearator = 1;
        nByKarray[extraSpace] = stnInfoList;
        extraSpace++;
      }
      else{
        spearator++;
      }
      stnInfoList = stnInfoList->next;
    }
    stnInfoList = tempElements;
  }
  
  // Put your code for the core of QuicksortSimple here
  int length = end - start + 1;
  //choosing a random pivot
  srand(time(0));
  int pivotPos = start + (rand() % length);
  listOfObjects<TrainInfoPerStation*>* pivot = findMyElement(nByKarray, pivotPos, K);

  //now the partition part
  listOfObjects<TrainInfoPerStation*> *tempstartElem = findMyElement(nByKarray, start, K);
  listOfObjects<TrainInfoPerStation*> *holder = nByKarray[(int)(start/K)];
  listOfObjects<TrainInfoPerStation*> *tempendElem = findMyElement(nByKarray, end, K);
  
  int nGreaterThanPivot = 0;

  while(tempstartElem!=tempendElem){
    if(findTrueDay(tempstartElem->object) > findTrueDay(pivot->object)){
      nGreaterThanPivot++;
    }
    else if(findTrueDay(tempstartElem->object) == findTrueDay(pivot->object)){
      if(tempstartElem->object->depTime >= pivot->object->depTime){
        nGreaterThanPivot++;
      }
    }
    tempstartElem = tempstartElem->next;
  }
  nByKarray[(int)(start/K)] = holder;

  int pivotIndex = end - nGreaterThanPivot;
  listOfObjects<TrainInfoPerStation*> *pseudoPivot = findMyElement(nByKarray, pivotIndex, K);

  //swap pivot and pseudoPivot
  TrainInfoPerStation* tempPivot = pivot->object;
  pivot->object = pseudoPivot->object;
  pseudoPivot->object = tempPivot;

  pivot = pseudoPivot;

  //identify starting element
  listOfObjects<TrainInfoPerStation*>* holderStart = nByKarray[(int)(start/K)];
  listOfObjects<TrainInfoPerStation*> *startElem = findMyElement(nByKarray, start, K);

  //identify ending element
  listOfObjects<TrainInfoPerStation*>* holderEnd = nByKarray[(int)(end/K)];
  listOfObjects<TrainInfoPerStation*> *endElem = findMyElement(nByKarray, end, K);

  int tempStart = start;
  int tempEnd = end;
  while(tempStart < pivotIndex && tempEnd > pivotIndex){
    while((findTrueDay(startElem->object) < findTrueDay(pivot->object)) || ((findTrueDay(startElem->object) == findTrueDay(pivot->object)) && (startElem->object->depTime < pivot->object->depTime))){
      tempStart++;
      startElem = startElem->next;
      
    }
    while((findTrueDay(endElem->object) >= findTrueDay(pivot->object)) || ((findTrueDay(endElem->object) == findTrueDay(pivot->object)) && (endElem->object->depTime >= pivot->object->depTime))){
      tempEnd--;
      endElem = endElem->prev;
    }
    if(startElem!=pivot && endElem!=pivot){
      TrainInfoPerStation* tempo = startElem->object;
      startElem->object = endElem->object;
      endElem->object = tempo;
      startElem = startElem->next;
      endElem = endElem->prev;
      tempStart++;
      tempEnd--;
    }
  }
  nByKarray[(int)(start/K)] = holderStart;
  nByKarray[(int)(end/K)] = holderEnd;

  // Decrement recursion level before leaving the function
  //recursionLevel--;
  QuicksortSimple(stnInfoList, start, pivotIndex - 1);
  QuicksortSimple(stnInfoList, pivotIndex + 1, end);
  //return;
}

#endif
