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

// Returns 1 if node1 must be before node2 , -1 if node1 must be after node2, 0 if node1 equals to node2
int prior(listOfObjects<TrainInfoPerStation*> *node1,listOfObjects<TrainInfoPerStation*> *node2){
  int i1;
  int i2;
  for(int i=0;i<7;i++){
    if(node1->object->daysOfWeek[i]) i1=i;   
    if(node2->object->daysOfWeek[i]) i2=i;
  }
  
  if(i1 < i2) return 1;                                         // first compare days
  if(i1 > i2) return -1;
  if(node1->object->depTime == node2->object->depTime) return 0;
  if(node1->object->depTime == -1) return -1;
  if(node2->object->depTime == -1) return 1; 
  if(node1->object->depTime < node2->object->depTime) return 1; 
  if(node1->object->depTime > node2->object->depTime) return -1;
  return 0;
}

int partition(listOfObjects<TrainInfoPerStation*> *stnInfoList,int start, int end, listOfObjects<TrainInfoPerStation*>* ext_array[],int K){

  static listOfObjects<TrainInfoPerStation*> *pivot;    // stores the pivot
  static listOfObjects<TrainInfoPerStation*> *init;     // stores the node which is at position start in the list 
  static listOfObjects<TrainInfoPerStation*> *fin;      // stores the node which is at position end in the list
  static TrainInfoPerStation* obj;                      // used while changing the objects of some nodes

  int p = (rand()%(end-start+1))+start;                 // p is an integer between start and end
  int index = p/K;                                      // p/K gives the index of the ext_array through which we can get 
  int pos = p % K;                                      // pivot in O(k) time. pos is position of the pivot linked to the 
                                                        // element of array of the given index
  pivot =ext_array[index];                              // finds the pivot
  for(int i=1;i<=pos && pivot->next != NULL;i++){pivot = pivot->next;}  
  pivot = new listOfObjects<TrainInfoPerStation*>(pivot->object);

  init = stnInfoList;                                   // finds the initial node (node at position start)
  for(int i=0;i<start;i++) init = init->next;           
  fin = init;                                           // finds the final node (node at position end)
  for(int i=start;i<end;i++) fin = fin->next;  
  
  int i=start-1;                                        // Standard quick sort process
  int j=end+1;
 
  while(true){
    while(true){            
      j=j-1;      
      if(prior(fin,pivot) != -1) {                       // if fin is more prior than pivot, then break 
        break;                                           
      }
      fin = fin->prev;
    }           
    while(true){
      i = i+1;
     
      if(prior(init,pivot) != 1){                       // if init is less prior than pivot, then break
        break;
      }
      init = init->next;
    }

    if(i < j){              
      obj = fin->object;                                
      fin->object = init->object;                       // change the fin's object with init obj
      init->object = obj;                               // and init object with fin's obj
      fin = fin->prev;
      init=init->next;      
    }
    else if(j == end) return j-1;                      // if j=end return j-1 to avoid infinite recursion
    else return j;                                     // else just return j
  }   
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

  static int list_len=end+1; //stores the length of the list
  // array of pointers of length n/k
  static listOfObjects<TrainInfoPerStation*> **ext_array = new listOfObjects<TrainInfoPerStation*>*[list_len/K];  
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    
    listOfObjects<TrainInfoPerStation*> *temp = stnInfoList; 
    int j=0;
    while(temp != NULL){
      if(j % K == 0) ext_array[j/K] = temp;                  //add th pointer to the array after every k steps
      temp = temp->next;
      j++;
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  if(start < end){    
    int q = partition(stnInfoList,start,end,ext_array,K);    // returns the index(same as of the original one)   
    QuicksortSimple(stnInfoList,start,q);                    // Same as of quicksort on a array
    QuicksortSimple(stnInfoList,q+1,end);                    // Same as of quicksort on a array
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
