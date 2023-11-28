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

void Planner::swap(listOfObjects<TrainInfoPerStation *> *node1, listOfObjects<TrainInfoPerStation *> *node2){
    
    // This function will swap the object of two node.
  static TrainInfoPerStation* obj;
  obj = node1->object;
  node1->object = node2->object;
  node2->object = obj;
}

bool Planner::isLess(listOfObjects<TrainInfoPerStation *> *node1, listOfObjects<TrainInfoPerStation *> *node2){
    
    // This function will return true if node1 is to be put before node2 else false.
    
    for(int i = 0; i<7; i++){
        if(node1->object->daysOfWeek[i] == 0 && node2->object->daysOfWeek[i] == 0){ // when both trains are not available on that day.
            continue;
        }
        else if(node1->object->daysOfWeek[i] == 1 && node2->object->daysOfWeek[i] == 0){  // when node1 is available before node2.
            return true;
        }
        
        else if(node1->object->daysOfWeek[i] == 0 && node2->object->daysOfWeek[i] == 1){  // When node2 is available before node1.
            return false;
        }
        else if(node1->object->daysOfWeek[i] == 1 && node2->object->daysOfWeek[i] == 1){  // When both are available on the same day we will check for time and return accordingly.
            if(node1->object->depTime < node2->object->depTime){
                return true;
            }
            else if(node1->object->depTime > node2->object->depTime){
                return false;
            }
        }
    }
    
  //return true;
}

listOfObjects<TrainInfoPerStation *>* Planner::randomPivot(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *node, int start, int end, int K, int N){  // will choose pivot randomly and return a pivot.
    
    // First i created an array of n/k elements pointing to the pointers of of stnInfoList in an interval of k. I have passed the array as an argument to the function.
    
    // Then I choose a random pointer from arr using rand thats in the interval start to end then again use rand to traverse from the choosed point to rand()%Kth pointer from the previously choosen pointer. Therefore the traversal time will be less than K. And return pivot accordingly.
  
    static int start_arr = 0;
    static int n = 0;
    static listOfObjects<TrainInfoPerStation *>* a;
  
    start_arr = 0;
    n = 0;
  if(start%K == 0){
    start_arr = start/K;
  }
  else{
    start_arr = start/K + 1;
  }
  if((end-start+1)/K != 0){
    n = rand()%((end-start+1)/K);
  }
  start_arr += n;
  if(start_arr<(N/K)){
    a = arr[start_arr];
    n = rand()%K;
    for(int i = 0; i < n; i++){
      a = a->next;
    }
  }
  else{
      a = arr[start_arr - n];
  }
  n = 0;
  start_arr = 0;
  return a;

}

listOfObjects<TrainInfoPerStation *> * Planner::Partition(listOfObjects<TrainInfoPerStation *> *head, listOfObjects<TrainInfoPerStation *> *tail, listOfObjects<TrainInfoPerStation *> *pivot){
    
    static listOfObjects<TrainInfoPerStation *> *j;
    static listOfObjects<TrainInfoPerStation *> *i;
    static listOfObjects<TrainInfoPerStation *> *x;
    
    
    x = pivot;
    i = head->prev;
    
    swap(pivot, tail);
    //will swap pivot and tail then will traverse from start and start-1 and swap accordingly.
    
    for(j = head;j != tail; j = j->next){
        if(isLess(j, x)){ //when j is less than x we swap i and j.
            if(i != nullptr){
                i = i->next;
            }
            else{
                i = head;
            }
            swap(i, j);
        }
    }
    if(i != nullptr){
        i = i->next;
    }
    else{
        i = head;
    }
    swap(i, tail);
    return i;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;

    static int j = 0;  // keep tarck of the current index.

    static listOfObjects<TrainInfoPerStation *> *node;
    static listOfObjects<TrainInfoPerStation *> *tail;
    static listOfObjects<TrainInfoPerStation *> *head;
    static listOfObjects<TrainInfoPerStation *> *j1;
    static int N; // will store the total number of list object.
   
    static listOfObjects<TrainInfoPerStation *> **arr;
    
    if (recursionLevel == 0){
        
        N = end - start +1;
      arr = new listOfObjects<TrainInfoPerStation *> *[(end-start+1)/K];

      for(int i = 0; i < (end - start+1)/K; i++){
        if(i % K == 0){
          arr[j] = stnInfoList;
          j++;
        }
        stnInfoList = stnInfoList->next;
      }
    stnInfoList = arr[0];
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  if((start == end)&&(end - start == 1)){  //when there is only one element or no element.
    return;
  }

  else if(start - end == 2){
      // when there is two element
    if(isLess(stnInfoList->next, stnInfoList)){
      swap(stnInfoList, stnInfoList->next);
    }
  }

  else{
    node = randomPivot(arr, stnInfoList, start, end, K, N);
    tail = stnInfoList;
    head = stnInfoList;
    while(tail->next != nullptr){
      tail = tail->next;
    }
      
      j1 = Partition(head, tail, node); // will partition and returns a node about which we do the next partion.
      node = head;
      j = 0;
      while(node != j1){
          node = node->next;
          j++;
      }
      
      QuicksortSimple(head, start, j-1);
      QuicksortSimple(j1->next, j+1, end);
    }
      //pivot_index = 0;


  
  
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
  
  
  
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
