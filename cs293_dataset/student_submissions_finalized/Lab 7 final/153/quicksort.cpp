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

int Planner::recursionLevel=-1, Planner::stat_start=0, Planner::stat_end=0, Planner::stat_len=0, Planner::K=4, Planner::stat_len_head=0;
listOfObjects<TrainInfoPerStation*>** Planner::stat_headArr=nullptr;

template <typename T>
void swapElements(listOfObjects<T> *one, listOfObjects <T>* two){
  if(one == nullptr || two == nullptr) return;

  T temp = one->object;
  one->object = two->object;
  two->object = temp;
}

bool lessThan(TrainInfoPerStation* one, TrainInfoPerStation* two){
  for(int i=0; i<7; i++){
    if(one->daysOfWeek[i] && !two->daysOfWeek[i]) return true;
    if(!one->daysOfWeek[i] && two->daysOfWeek[i]) return false;
  }

  if(one->depTime == -1) return false;
  if(two->depTime == -1) return true;
  return one->depTime < two->depTime; 
}
bool greaterThan(TrainInfoPerStation* one, TrainInfoPerStation* two){
  for(int i=0; i<7; i++){
    if(one->daysOfWeek[i] && !two->daysOfWeek[i]) return false;
    if(!one->daysOfWeek[i] && two->daysOfWeek[i]) return true;
  }

  if(one->depTime == -1) return true;
  if(two->depTime == -1) return false;
  return one->depTime > two->depTime; 
}
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
  static int K=4;
  static int recursionLevel=-1, stat_start=0, stat_end=0, stat_len=0, stat_len_head=0;
  static listOfObjects<TrainInfoPerStation*>** stat_headArr=nullptr;

  cout << stat_start << "\t" << stat_end << "\n";

  if(recursionLevel!=-1 && stat_start >= stat_end) return;

  // Increment recursion level on entering the function
  recursionLevel++;
  cout<<"Quicksorting at level "<<recursionLevel<<"\n";
  
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
    stat_len=0;
    listOfObjects<TrainInfoPerStation*> *cur = stnInfoList;
    while(cur != nullptr){stat_len++;cur=cur->next;}

    stat_len_head = (stat_len/K);
    if(stat_len_head * K < stat_len) stat_len_head++;
    stat_headArr = (listOfObjects<TrainInfoPerStation*> **) malloc(stat_len_head * sizeof(listOfObjects<TrainInfoPerStation *>*));
    
    cur = stnInfoList;
    for(int i=0; i<stat_len_head; i++){
      stat_headArr[i]=cur;
      for(int j=0; j<K,i<stat_len_head-1; j++){
        cur=cur->next;
        if(cur == nullptr) break;
      }
    }

    stat_start=0;
    stat_end=stat_len-1;
  }

  int cur_end = stat_end;
  
  // Put your code for the core of Quicksort here
  int partition_index;listOfObjects<TrainInfoPerStation*> *partition_node=stnInfoList;

  // partition_node = this->partition(stnInfoList, partition_index);
  partition_index = stat_start;
  listOfObjects<TrainInfoPerStation*> *pivot=stnInfoList, *cur=stnInfoList;
  TrainInfoPerStation* pivot_obj = nullptr;

  int choice = (rand() % (stat_end-stat_start+1)) + stat_start;
  listOfObjects<TrainInfoPerStation*> *choose_cur = stat_headArr[choice/K];

  for(int i=0; i<(choice%K),choose_cur->next!=nullptr; i++) choose_cur=choose_cur->next;

  pivot_obj = choose_cur->object;

  for(int i=stat_start; i<=stat_end, cur!=nullptr; i++){
    if(lessThan(cur->object, pivot_obj)){
      if(partition_node != cur) swapElements(partition_node, cur);
      partition_node = partition_node->next;
      partition_index++;
    }
    cur=cur->next;
  }

  if(partition_index < 0){
    recursionLevel--;
    return;
  }

  stat_end = partition_index - 1;
  this->Quicksort(stnInfoList);
  stat_end = cur_end;stat_start = partition_index;
  this->Quicksort(partition_node);

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  // int stat_start, stat_end;
  stat_start = start;
  stat_end = end;
  this->Quicksort(stnInfoList);
}

// listOfObjects<TrainInfoPerStation*> * Planner::partition(listOfObjects<TrainInfoPerStation*> *stnInfoList, int& partition_index, int start, int end){
//   // static int stat_start, stat_end;
//   partition_index = stat_start;
//   listOfObjects<TrainInfoPerStation*> *pivot=stnInfoList, *cur=stnInfoList, *partition_node=stnInfoList;
//   TrainInfoPerStation* pivot_obj = this->chooseRandomPivot(stnInfoList);

//   for(int i=stat_start; i<=stat_end; i++){
//     if(lessThan(cur->object, pivot_obj)){
//       if(partition_node != cur) swapElements(partition_node, cur);
//       partition_node = partition_node->next;
//       partition_index++;
//     }
//     cur=cur->next;
//   }

//   return partition_node;
// }

// TrainInfoPerStation* Planner::chooseRandomPivot(listOfObjects<TrainInfoPerStation*> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation*>** headArr){
//   // static int stat_start, stat_end, K;
//   // static listOfObjects<TrainInfoPerStation*> **stat_headArr;
//   int choice = (rand() % (stat_end-stat_start+1)) + stat_start;
//   listOfObjects<TrainInfoPerStation*> *cur = stat_headArr[choice/K];

//   for(int i=0; i<(choice%K); i++) cur=cur->next;

//   return cur->object;
// }

#endif
