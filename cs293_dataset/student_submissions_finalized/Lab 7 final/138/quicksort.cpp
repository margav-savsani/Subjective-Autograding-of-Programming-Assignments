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

int Planner::Partition(listOfObjects<TrainInfoPerStation *> *star,int start,int end ,listOfObjects<TrainInfoPerStation *> *last){
  //initialising pivot comparison variables
  int dayp;

  //finding the day of the pivot element
  for(int k=0;k<7;k++){
    if((last->object)->daysOfWeek[k]){
      dayp=k;
    }
  }

  int dep=(last->object)->depTime;
  //this will be variabke that will be returned
  int count=start-1;

  //initialising variables
  listOfObjects<TrainInfoPerStation*>* i=star->prev;
  listOfObjects<TrainInfoPerStation*>* j=star;

  // placing the pivot element at the right position
  for (int t=0;t<end-start;t++){

    //finding the comparison
    int dayj;

    // finding the day of the element to be compared
    for(int l=0;l<7;l++){
      if((j->object)->daysOfWeek[l]){
        dayj=l;
      }
    }

    //comparing the days
    if(dayj<dayp){
      if(i==NULL){
        i=star;
      }
      else{
        i=i->next;
      }
      count++;
      TrainInfoPerStation * t=i->object;
      i->object=j->object;
      j->object=t;
    }

    // if day is same and time is less
    else if(dayj==dayp && ((j->object)->depTime< dep)){
      if(i==NULL){
        i=star;
      }
      else{
        i=i->next;
      }
      count++;
      TrainInfoPerStation * t=i->object;
      i->object=j->object;
      j->object=t;
    }

    // shifting the j pointer
    j=j->next;
  }

  // if the pivot element is the smallest element
  if(i==NULL){
    i=star;
  }

  // in other cases
  else {
    i=i->next;
  }

  //swapping the pivot at its right position
  TrainInfoPerStation * t=i->object;
  i->object=last->object;
  last->object=t;

  // returning the index of the pivot element
  return count+1;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;

  //compressed array
  static listOfObjects<TrainInfoPerStation*>** ref;

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

  int n=end-start+1;
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    //allocate additional space to the array
    if(n%K==0){
      ref = new listOfObjects<TrainInfoPerStation*>* [n/K] ;
    }
    else{
      ref = new listOfObjects<TrainInfoPerStation*>*[(n/K)+1] ;
    }
    int N=0;
    int i=0;

    // storing the n/k elements in compressed array
    listOfObjects<TrainInfoPerStation *> *sta=stnInfoList;
    while(N!=end-start+1){
      if(N%K==0){
        ref[i]=sta;
        i++;
      }
      N++;
      sta=(sta)->next;
    }

    //pre processing complete
  }
  // Put your code for the core of QuicksortSimple here

  if (start < end){
    //generating random number
    srand(time(0));
    int piv=start+(rand()%n);
    int quo=piv/K;
    int rem=piv%K;

    //reraching the pivot pointer
    listOfObjects<TrainInfoPerStation*>* to_reach=ref[quo];
    for (int i=0;i<rem;i++){
      to_reach=to_reach->next;
    }

    //finding last listOfObject in the linked list
    int last_q=end/K;
    int last_r=end%K;
    listOfObjects<TrainInfoPerStation *> *last=ref[last_q];
    for (int i=0;i<last_r;i++){
      last=last->next;
    }

    // last is of l* type
    //have to exchange to_reach->object and last->object
    //object is of TrainInfoPerStation* type
    //exchanging
    TrainInfoPerStation * t=to_reach->object;
    to_reach->object=last->object;
    last->object=t;

    // the position of the pivot element is returned
    int parti;
    parti=Partition(stnInfoList,start,end,last);


    //reaching the ptr to pivot+1 th element
    int quot=(parti+1)/K;
    int rema=(parti+1)%K;

    //reaching the next of pivot pointer
    listOfObjects<TrainInfoPerStation*>* next_of_part=ref[quot];
    for (int i=0;i<rema;i++){
      next_of_part=next_of_part->next;
    }

    //recursive calls
    QuicksortSimple(stnInfoList,start,parti-1);
    QuicksortSimple(next_of_part,parti+1,end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;

  return;
}

#endif
