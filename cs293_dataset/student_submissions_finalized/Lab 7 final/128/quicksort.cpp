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


bool less_or_equal(listOfObjects<TrainInfoPerStation*>* a, listOfObjects<TrainInfoPerStation*>* b){
  for(int i=0; i<7; i++){
    if( a->object->daysOfWeek[i] && !b->object->daysOfWeek[i] ){
      return true;
    }
    else if( !a->object->daysOfWeek[i] && b->object->daysOfWeek[i]){
      return  false;
    }
  }
  return (a->object->arrTime <= b->object->arrTime);
}

void exchange( listOfObjects<TrainInfoPerStation*>* a, listOfObjects<TrainInfoPerStation*>* b){
  TrainInfoPerStation* temp = a->object;
  a->object = b->object;
  b->object = temp;

}

int Partition(listOfObjects<TrainInfoPerStation *>* start_stn ,
                 listOfObjects<TrainInfoPerStation *> *pivot, int start, int end){
  
  if(start_stn == nullptr || pivot == nullptr){
    return -1;}


  //push pivot to end of array
    listOfObjects<TrainInfoPerStation *>* first_node = start_stn; 
    listOfObjects<TrainInfoPerStation *>* last_node = start_stn;
    listOfObjects<TrainInfoPerStation *>* currNode = start_stn;
    for(int i=start; i < end; i++){
      last_node = last_node->next;
    }

    exchange(pivot, last_node);
    pivot = last_node;

    int i = start;
    for( int j = start; j<end; j++){

        if( less_or_equal(currNode, last_node)){
            exchange(first_node, currNode);
            first_node = first_node->next;

            i++;
        }
        currNode = currNode->next;
    }

    exchange(last_node, first_node);
    return i;
  
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
  // across all recursion

  static listOfObjects<TrainInfoPerStation *> ** hash;
  
  listOfObjects<TrainInfoPerStation*>* currNode = stnInfoList;
  static int size;



  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    size = 0;
    while(currNode != NULL){
      currNode = currNode->next;
      size++;
    }

    hash = new listOfObjects<TrainInfoPerStation *>* [ size/K + ((size%K == 0)? 0 : 1)];
    
    currNode = stnInfoList;
    int index = 0;
    hash[0] = currNode;
    while (currNode != NULL)
    {
      currNode = currNode->next;
      index++;
      
      if (index % K == 0){
        hash[index/K] = currNode;
      }
    }
  }

  static int start = 0;
  static int end = size - 1;

  if ( end <= start){
    recursionLevel--;

    if(recursionLevel == -1){

      delete[] hash;
    }
    return;
  }
  
  // Put your code for the core of Quicksort here

  //pivot generation
  int random = rand();

  int random_pivot = start + (random%(end - start + 1));

  currNode = hash[random_pivot/K];
  random_pivot %= K;
  while(random_pivot > 0){
    currNode = currNode->next;
    random_pivot--;
  }

  int pivot_index = Partition(stnInfoList, currNode, start, end);
  
  int i = pivot_index;
  currNode = hash[i/K];
  i %= K;
  while(i > 0){
    currNode = currNode->next;
    i--;
  }

  
  int oldend = end;
  int oldstart = start;  
  end = pivot_index - 1;
  Quicksort(stnInfoList);

  start = pivot_index + 1;
  end = oldend;
  Quicksort(currNode->next);

  start = oldstart;
  end = oldend;

  // Decrement recursion level before leaving the function
  recursionLevel--;

  if(recursionLevel == -1){
    delete[] hash;
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
  // across all recursion

  static listOfObjects<TrainInfoPerStation *> ** hash;

  if ( end <= start ){
    recursionLevel--;

    if(recursionLevel == -1){

      delete[] hash;
    }
    return;
  }
  listOfObjects<TrainInfoPerStation*>* currNode = stnInfoList;
  int size = end - start + 1;



  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    hash = new listOfObjects<TrainInfoPerStation *>* [ size/K + ((size%K == 0)? 0 : 1)];

    currNode = stnInfoList;
    int index = 0;
    hash[0] = currNode;
    while (currNode != NULL)
    {
      currNode = currNode->next;
      index++;
      if (index % K == 0){
        hash[index/K] = currNode;
      }
    }
  }
  
  // Put your code for the core of QuicksortSimple here

  //pivot generation
  int index = start + rand()%size;
  currNode = hash[index/K];
  index %= K;
  while(index > 0){
    currNode = currNode->next;
    index--;
  }

  int pivot_index = Partition(stnInfoList, currNode, start, end);
  
  index = pivot_index;
  currNode = hash[index/K];
  index %= K;
  while(index > 0){
    currNode = currNode->next;
    index--;
  }

  QuicksortSimple(stnInfoList, start, pivot_index - 1 );
  QuicksortSimple(currNode->next, pivot_index + 1, end);

  // Decrement recursion level before leaving the function
  recursionLevel--;

  if(recursionLevel == -1){
    delete[] hash;
  }

  return;
}

#endif
