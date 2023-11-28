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

#ifndef TIME_H
#include <time.h>
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

bool lees(TrainInfoPerStation *a, TrainInfoPerStation *b){
  int day_a ;
  for ( int i = 0 ; i < 7 ; i++){
    if (a->daysOfWeek[i]){
      day_a = i;
    }
  }
  int day_b ;
  for ( int i = 0 ; i < 7 ; i++){
    if (b->daysOfWeek[i]){
      day_b = i;
    }
  }
  if ( day_a < day_b ){
    return true;
  }
  else if ( day_a > day_b ){
    return false;
  }
  else{
    if (a->depTime == -1){
      return false;
    }
    else if ( b->depTime == -1 ){
      return true;
    }
    if ( a->depTime < b->depTime ){
      return true;
    }
    else {
      return false;
    }
  }

}

bool lessthan(listOfObjects< TrainInfoPerStation* > *a , listOfObjects< TrainInfoPerStation* > *b ){
  return lees( (a->object) , (b->object) );
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Increment recursion level on entering the function
  recursionLevel++;

  static int size = 1;
  static int extra_space;
  if (recursionLevel==0){
    
    //The case if empty list is passed
    if (stnInfoList==nullptr){
      size = 0;
      return;
    }

    //Determine the size of the list
    size = 1;
    while(stnInfoList->next!=nullptr){
      stnInfoList = stnInfoList->next;
      size++;
    }

    //Put stnInfoList into the correct place again
    while(stnInfoList->prev!=nullptr){
      stnInfoList = stnInfoList->prev;
    }

    //The extra space that will be required
    extra_space = (size-1)/K+1;
  }

  //Calculate the "Extra_array", which stores every kth element of the linked list
  static listOfObjects <TrainInfoPerStation *> **extra_array;
    if (recursionLevel == 0){
      extra_array = new listOfObjects <TrainInfoPerStation *>*[extra_space];
      for (int i = 0 ; i < extra_space ; i++ ){
        extra_array[i] = stnInfoList;
        if (i!=extra_space-1){
          for (int j = 0 ; j < K ; j++){
            stnInfoList = stnInfoList->next;
          }
        }
      }
    }


  //DECLARE ALL THE VARIABLES THAT WILL BE USED ONLY ONCE
  static int start = 0;
  static int end = size-1;
  static listOfObjects<TrainInfoPerStation *> *pivot;
  static listOfObjects<TrainInfoPerStation *> *start_node;
  static listOfObjects<TrainInfoPerStation *> *end_node;
  static listOfObjects<TrainInfoPerStation *> *left_iter;
  static listOfObjects<TrainInfoPerStation *> *right_iter;
  static listOfObjects<TrainInfoPerStation *> *temp; 
  if (recursionLevel == 0){
    TrainInfoPerStation *add = new TrainInfoPerStation(0,0,0,0);
    listOfObjects <TrainInfoPerStation *> a(add);
  pivot = new listOfObjects<TrainInfoPerStation *>(a);
  start_node = new listOfObjects<TrainInfoPerStation *>(a);
  end_node = new listOfObjects<TrainInfoPerStation *>(a);
  left_iter= new listOfObjects<TrainInfoPerStation *>(a);
  right_iter = new listOfObjects<TrainInfoPerStation *>(a);
  temp = new listOfObjects<TrainInfoPerStation *>(a);
  end = size-1;
  }
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

  // Check the size of the part of linked list to be quicksorted
  int temp_size = end - start + 1 ;
  if (temp_size <= 1){      //If quicksort is called on a single element, just do nothing and return
    if (recursionLevel == 0){
      delete extra_array;
    }
    recursionLevel--;
    return;
  }

  // PICK THE PIVOT WITH O(K) TIME
  int pivot_index = rand()%temp_size; 
  //Random number, so every pivot is equally likely
  pivot_index = start + pivot_index;
  int index = pivot_index/K;
  pivot = extra_array[index];
  int move_ahead = pivot_index%K;
  for (int i = 0 ; i < move_ahead ; i++){       // O(K) for pivot
    pivot = pivot->next;
  }

  // THE PARTITION FUNCTION
  // Let's find the start node O(K)
  start_node =  extra_array[start/K];
  for ( int i = 0 ; i < start%K ; i++ ){
    start_node = start_node->next;
  }
  // Let's find the end node O(K)
  end_node = extra_array[end/K];
  for ( int i = 0 ; i < end%K ; i++ ){
    end_node = end_node->next;
  }
  
  // Partitioning the array O(N) and store the address of the pivot
  // Partition makes two arrays, one small and one big
  // Equal train departure times can be either in small or big
  
  //Declare and update the varibales for partitioning
  int partition;
  int left = start;
  int right  = end;
  left_iter =  start_node;
  right_iter =  end_node;
  int position = 0;
  temp = start_node;
  int count = 0;

  //Number of elements in linked list, smaller than or equal to pivot
  while( temp!=end_node){
    //if (temp->object<=pivot->object){
    if (  !lessthan(pivot, temp) ){
      position++;
    }
    count++;
    temp = temp->next;
  }
  if ( !lessthan(pivot,end_node)){
    position++;
  }
  for ( int ks = 0 ; ks < 7 ; ks++){
    if(pivot->object->daysOfWeek[ks]){
    }
  }
  position = start+position-1;

  //Exchange the element at the position'th place with the pivot (so that pivot is at the correct spot)
  temp = extra_array[position/K];
  for ( int i = 0 ; i < position%K ; i++){
    temp = temp->next;
  }
  TrainInfoPerStation* storage = pivot->object;
  pivot->object = temp->object;
  temp->object = storage;
  pivot = temp;

  //Run the loops from both sides to the pivot
  while( 1 ){
    while ( !(lessthan(pivot,left_iter)) && left < position ){

      left_iter = left_iter->next;
      left++;
    }
    while ( lessthan(pivot,right_iter) && right > position){
 
      right_iter = right_iter->prev;
      right--;
    }
    if ( left >= position ){
      break;
    }
    else{
      TrainInfoPerStation* store = left_iter->object;
      left_iter->object = right_iter->object;
      right_iter->object = store;
    }
  }

  // Call the quicksort on smaller subsets
  int memorize_end = end;
  int memorize_start = start;
  end = position-1;
  Quicksort(start_node);
  end = memorize_end;
  start = position+1;
  Quicksort(pivot->next);
  start = memorize_start;

  //Delete the memory alloted to the array
  if (recursionLevel==0){
    delete extra_array;
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}


void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start_, int end_)
{
  // A few static variable declarations
  static int K = 10; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Increment recursion level on entering the function
  recursionLevel++;

  static int size = 1;
  static int extra_space;
  if (recursionLevel==0){
    
    //The case if empty list is passed
    if (stnInfoList==nullptr){
      size = 0;
      return;
    }

    //Determine the size of the list
    size = 1;
    while(stnInfoList->next!=nullptr){
      stnInfoList = stnInfoList->next;
      size++;
    }

    //Put stnInfoList into the correct place again
    while(stnInfoList->prev!=nullptr){
      stnInfoList = stnInfoList->prev;
    }

    //The extra space that will be required
    extra_space = (size-1)/K+1;
  }

  //Calculate the "Extra_array", which stores every kth element of the linked list
  static listOfObjects <TrainInfoPerStation *> **extra_array;
    if (recursionLevel == 0){
      extra_array = new listOfObjects <TrainInfoPerStation *>*[extra_space];
      for (int i = 0 ; i < extra_space ; i++ ){
        extra_array[i] = stnInfoList;
        if (i!=extra_space-1){
          for (int j = 0 ; j < K ; j++){
            stnInfoList = stnInfoList->next;
          }
        }
      }
    }

  //DECLARE ALL THE VARIABLES THAT WILL BE USED ONLY ONCE
  static int start = 0;
  static int end = size-1;
  static listOfObjects<TrainInfoPerStation *> *pivot;
  static listOfObjects<TrainInfoPerStation *> *start_node;
  static listOfObjects<TrainInfoPerStation *> *end_node;
  static listOfObjects<TrainInfoPerStation *> *left_iter;
  static listOfObjects<TrainInfoPerStation *> *right_iter;
  static listOfObjects<TrainInfoPerStation *> *temp; 
  if (recursionLevel == 0){
    TrainInfoPerStation *add = new TrainInfoPerStation(0,0,0,0);
    listOfObjects <TrainInfoPerStation *> a(add);
  pivot = new listOfObjects<TrainInfoPerStation *>(a);
  start_node = new listOfObjects<TrainInfoPerStation *>(a);
  end_node = new listOfObjects<TrainInfoPerStation *>(a);
  left_iter= new listOfObjects<TrainInfoPerStation *>(a);
  right_iter = new listOfObjects<TrainInfoPerStation *>(a);
  temp = new listOfObjects<TrainInfoPerStation *>(a);
  end = size-1;
  }
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

  // Check the size of the part of linked list to be quicksorted
  int temp_size = end - start + 1 ;
  if (temp_size <= 1){      //If quicksort is called on a single element, just do nothing and return
    if (recursionLevel == 0){
      delete extra_array;
    }
    recursionLevel--;
    return;
  }

  // PICK THE PIVOT WITH O(K) TIME
  int pivot_index = rand()%temp_size; 
  //Random number, so every pivot is equally likely
  pivot_index = start + pivot_index;
  int index = pivot_index/K;
  pivot = extra_array[index];
  int move_ahead = pivot_index%K;
  for (int i = 0 ; i < move_ahead ; i++){       // O(K) for pivot
    pivot = pivot->next;
  }

  // THE PARTITION FUNCTION
  // Let's find the start node O(K)
  start_node =  extra_array[start/K];
  for ( int i = 0 ; i < start%K ; i++ ){
    start_node = start_node->next;
  }
  // Let's find the end node O(K)
  end_node = extra_array[end/K];
  for ( int i = 0 ; i < end%K ; i++ ){
    end_node = end_node->next;
  }
  
  // Partitioning the array O(N) and store the address of the pivot
  // Partition makes two arrays, one small and one big
  // Equal train departure times can be either in small or big
  
  //Declare and update the varibales for partitioning
  int partition;
  int left = start;
  int right  = end;
  left_iter =  start_node;
  right_iter =  end_node;
  int position = 0;
  temp = start_node;
  int count = 0;

  //Number of elements in linked list, smaller than or equal to pivot
  while( temp!=end_node){
    //if (temp->object<=pivot->object){
    if (  !lessthan(pivot, temp) ){
      position++;
    }
    count++;
    temp = temp->next;
  }
  if ( !lessthan(pivot,end_node)){
    position++;
  }
  position = start+position-1;

  //Exchange the element at the position'th place with the pivot (so that pivot is at the correct spot)
  temp = extra_array[position/K];
  for ( int i = 0 ; i < position%K ; i++){
    temp = temp->next;
  }
  TrainInfoPerStation* storage = pivot->object;
  pivot->object = temp->object;
  temp->object = storage;
  pivot = temp;

  //Run the loops from both sides to the pivot
  while( 1 ){
    while ( !(lessthan(pivot,left_iter)) && left < position ){

      left_iter = left_iter->next;
      left++;
    }
    while ( lessthan(pivot,right_iter) && right > position){
 
      right_iter = right_iter->prev;
      right--;
    }
    if ( left >= position ){
      break;
    }
    else{
      TrainInfoPerStation* store = left_iter->object;
      left_iter->object = right_iter->object;
      right_iter->object = store;
    }
  }

  // Call the quicksort on smaller subsets
  int memorize_end = end;
  int memorize_start = start;
  end = position-1;
  QuicksortSimple(start_node,start,position-1);
  end = memorize_end;
  start = position+1;
  QuicksortSimple(pivot->next,position+1,end);
  start = memorize_start;

  //Delete the memory alloted to the array
  if (recursionLevel==0){
    delete extra_array;
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
