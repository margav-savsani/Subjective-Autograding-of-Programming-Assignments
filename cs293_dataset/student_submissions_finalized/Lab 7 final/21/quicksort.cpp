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


// compatring two info based on arrival date, time
bool isgreater(TrainInfoPerStation *info1, TrainInfoPerStation *info2 ){
  for (int i=0; i<7; i++){
    if (info1->daysOfWeek[i] == true && info2->daysOfWeek[i] == false) return false;
    if (info1->daysOfWeek[i] == true && info2->daysOfWeek[i] == true) {
      if (info1->arrTime == info2->arrTime) return (info1->depTime > info2->depTime);
      return (info1->arrTime > info2->arrTime);
    }
    if (info1->daysOfWeek[i] == false && info2->daysOfWeek[i] == true) return true;
  }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which level of the recursion you are in

  // static variables required for quick sort
  static int start;
  static int end;
  static int i;
  static int j;
  static listOfObjects<TrainInfoPerStation *> *stptr;
  static listOfObjects<TrainInfoPerStation *> *endptr;
  static listOfObjects<TrainInfoPerStation *>* pi; 
  static listOfObjects<TrainInfoPerStation *>* pj;

  static listOfObjects<TrainInfoPerStation *>* *arr; // declaring the n/K sized array as a static variable

  // Increment recursion level on entering the function
  recursionLevel++;
  
  if (recursionLevel == 0) {
    // this step is done only during the first call
    
    // forming the array of size n/K and also finding the last element and size of the linked list
    // in the process
    int j=1;
    int size = 0;
    arr = new listOfObjects<TrainInfoPerStation *>*(stnInfoList);
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList->next;
    listOfObjects<TrainInfoPerStation *> *last = nullptr;
    while (temp != nullptr){
      if (j%K == 0) arr[j/K] = temp;
      j++;
      size++;
      last = temp;
      temp = temp->next;
    }
    start = 0;
    end = size;
    stptr = stnInfoList;
    endptr = last;
  }
  
  // Put your code for the core of Quicksort here

  //choosing pivot
  if (start >= end) return;
  int x = rand()%(end-start+1);
  int y = start+x;
  int q = y/K;
  int r = y%K;
  listOfObjects<TrainInfoPerStation*> *pivot = arr[q];
  for (int k=0; k<r;k++){
    pivot = pivot->next;
  }
  
  //quick sort after choosing pivot
  i = start;
  pi = stptr; 
  j = end;
  pj = endptr;
  TrainInfoPerStation* o = pivot->object;  
  while(j>=i){

      while(isgreater(o,pi->object)) {
          pi = pi->next;
          i++; 
      }
      while(isgreater(pj->object,o)){
          pj = pj->prev;
          j--; 
      } 
      if( j >= i){
        swap(pi->object,pj->object); 
        i++;
        j--;
        pi = pi->next;
        pj = pj->prev;
      }
  }
  
  // temperory variables to whose values will be assigned to static vatiables before recursion call
  int tempi = i;
  listOfObjects<TrainInfoPerStation *>* temppi = pi;
  int tempend = end;
  int tempstart = start;
  listOfObjects<TrainInfoPerStation *>* tempendptr = endptr;
  listOfObjects<TrainInfoPerStation *>* tempstptr = stptr;
  
  if(start < j) {
    // sets the correct values for left side partition
    end = j;
    endptr = pj;
    Quicksort(stptr);
  }
  if(end > i) {
    // sets the correct values for right side partition
    start = tempi;
    stptr = temppi;
    end = tempend;
    endptr = tempendptr;
    Quicksort(stptr);
  }
  // setting the values for main array
  start = tempstart;
  stptr = tempstptr;
  end = tempend;
  endptr = tempendptr;
  
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

  static listOfObjects<TrainInfoPerStation *>* *arr;

  // Increment recursion level on entering the function
  recursionLevel++;
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    int j=1;
    int size = 0;
    arr = new listOfObjects<TrainInfoPerStation *>*(stnInfoList);
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList->next;
    while (temp != nullptr){
      if (j%K == 0) arr[j/K] = temp;
      j++;
      temp = temp->next;
    }
  }
  
  if (start >= end) return;
  int x = rand()%(end-start+1);
  int y = start+x;
  int q = y/K;
  int r = y%K;
  listOfObjects<TrainInfoPerStation*> *pivot = arr[q];
  for (int k=0; k<r;k++){
    pivot = pivot->next;
  }
  // Put your code for the core of QuicksortSimple here
  int i = start;
  int j = end;
  listOfObjects<TrainInfoPerStation*> *pi = stnInfoList;
  listOfObjects<TrainInfoPerStation*> *pj = arr[end/K];
  for (int k=0; k<(end%K);k++){
    pj = pj->next;
  } 

  TrainInfoPerStation* o = pivot->object;
  while(j>=i){

      while(isgreater(o,pi->object)) {
          pi = pi->next;
          i++; 
      }
      while(isgreater(pj->object,o)){
          pj = pj->prev;
          j--; 
      } 
      if( j >= i){
        swap(pi->object,pj->object); 
        i++;
        j--;
        pi = pi->next;
        pj = pj->prev;
      }
  }
  if(start < j) {
    // sets the correct values for left side partition
    QuicksortSimple(stnInfoList,start,j);
  }
  if(end > i) {
    // sets the correct values for right side partition
    QuicksortSimple(pi,i,end);
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
