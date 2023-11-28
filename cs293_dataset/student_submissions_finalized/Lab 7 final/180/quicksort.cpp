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



void swap(TrainInfoPerStation * a ,TrainInfoPerStation * b){                   //swap two pointer's data
  if(a ==NULL || b == NULL){
    return;
  }
  int jc = a->journeyCode;
  unsigned short stopsq = a->stopSeq;
  int at = a->arrTime;
  int dt = a->depTime;
  bool arr[7];
  for(int i = 0; i <7;i++){
    arr[i] = a->daysOfWeek[i];
  }
  a->journeyCode = b->journeyCode;
  a->arrTime = b->arrTime;
  a->depTime = b->depTime;
  a->stopSeq = b->stopSeq;
  for(int i = 0; i <7;i++){
    a->daysOfWeek[i] = b->daysOfWeek[i];
  }
  b->journeyCode = jc;
  b->arrTime = at;
  b->depTime = dt;
  b->stopSeq = stopsq;
  for(int i = 0; i <7;i++){
    b->daysOfWeek[i] = arr[i];
  }
  
}
bool is_less_than(TrainInfoPerStation * a ,TrainInfoPerStation * b){
  if(a ==NULL || b ==nullptr){
    return false;
  }
  for(int i=0; i < 7;i++){
    if(a->daysOfWeek[i] == true && b->daysOfWeek[i] == false){
      return true;
    }
    else if(a->daysOfWeek[i] == false && b->daysOfWeek[i] == true){
      return false;
    }
    else if(a->daysOfWeek[i] == true && b->daysOfWeek[i] == true){
      if(a->depTime < b->depTime){
        return true;
      }
      else{
        return false;
      }
    }
  }
  return false;
}
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 6; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int start1 =0,end1 = 0; //initialized to 0 end1 will be updated in recursion level 0
  static int arr_size =0;           
  static listOfObjects<TrainInfoPerStation*>** my_arr = nullptr;
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
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    start1 = 0;
    end1 = 0;
    my_arr = nullptr;
    listOfObjects<TrainInfoPerStation*>* currnode1 = stnInfoList;
    while(currnode1->next != nullptr){
      currnode1 = currnode1->next;
      end1++;                                          //end1 will be index of last pointer
    }
    int size_of_list = end1 -start1 +1 ;
    if(size_of_list < 2){                               //no sorting requited in this case
      recursionLevel--;
      return;

    }
    arr_size = 1 + (size_of_list - 1)/K;
    my_arr = new listOfObjects<TrainInfoPerStation*>*[arr_size];
    listOfObjects<TrainInfoPerStation*>* currnode = stnInfoList;
    for(int i = 0; i < size_of_list;i++){
      
      if(i%K == 0){                                               //these will be the points 0,k,2k.....
        my_arr[i/K] = currnode;
      }
      currnode = currnode->next;
      
    }
  }
  int start = start1;
  int end = end1;

  if(1+ end - start < 2){
    recursionLevel--;
    return;
  }
  // Put your code for the core of QuicksortSimple here
  srand(1);
  int pivot_index = start + rand()%(end - start + 1);                      //generate a random number between start and end
  //int pivot_index = end;
  listOfObjects<TrainInfoPerStation *>* pivot = my_arr[pivot_index / K];   //first go to nearest array element
  for(int i = 0; i < pivot_index%K ; i++){
    pivot = pivot->next;                                                   //then iterate and find pivot
  }

  //now swap the pivot with the last element so find the last element for that;
  listOfObjects<TrainInfoPerStation*>* lastnode = stnInfoList;
  for(int i = start; i < end ;i++){
    lastnode = lastnode->next;
  }
  swap(lastnode->object,pivot->object);               //swap the pivot and lastnode....now we will compare list with lastnode
  int front = start;
  listOfObjects<TrainInfoPerStation*>* curr_node = stnInfoList;
  listOfObjects<TrainInfoPerStation*>* front_node = stnInfoList;
  for(int i=start; i < end;i++){
        if(is_less_than(curr_node->object,lastnode->object)){
            swap(curr_node->object,front_node->object);
            front++;
            front_node = front_node->next;
        }
        curr_node=curr_node->next;        
    }
    swap(front_node->object,lastnode->object);
    start1 = start;                                //change start to starting index of this partition
    end1 = front -1;                                //change end to last index of this partition                            
    Quicksort(stnInfoList);                  
    start1 = front + 1;                               //change start to starting index of this partition
    end1 = end;                               //change end to last index of this partition
    Quicksort(front_node->next);


  //recursion level reduced
  recursionLevel--;
  if(recursionLevel == -1){                   //restore all data after doing sorting once;
    start1 = 0;
    end1 = 0;
    my_arr = nullptr;
    arr_size = 0;
    return;
  }
  return;
}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  int size_of_list = 1 + end - start;
  if(1 + end - start < 2){
    return;
  }
  static int arr_size = 1 + (size_of_list - 1)/K;           // 0,k,2k.....pk || pk+ r =list_size -1   || p + 1  =array_size
  static listOfObjects<TrainInfoPerStation*>** my_arr = new listOfObjects<TrainInfoPerStation*>*[arr_size];
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
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation*>* currnode = stnInfoList;
    for(int i = 0; i < size_of_list;i++){
      
      if(i%K == 0){                                               //these will be the points 0,k,2k.....
        my_arr[i/K] = currnode;
      }
      currnode = currnode->next;
      
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  srand(1);
  int pivot_index = start + rand()%(end - start + 1);                      //generate a random number between start and end
  //int pivot_index = end;
  listOfObjects<TrainInfoPerStation *>* pivot = my_arr[pivot_index / K];   //first go to nearest array element
  for(int i = 0; i < pivot_index%K ; i++){
    pivot = pivot->next;                                                   //then iterate and find pivot
  }

  //now swap the pivot with the last element so find the last element for that;
  listOfObjects<TrainInfoPerStation*>* lastnode = stnInfoList;
  for(int i = start; i < end ;i++){
    lastnode = lastnode->next;
  }
  swap(lastnode->object,pivot->object);               //swap the pivot and lastnode....now we will compare list with lastnode
  int front = start;
  listOfObjects<TrainInfoPerStation*>* curr_node = stnInfoList;
  listOfObjects<TrainInfoPerStation*>* front_node = stnInfoList;
  for(int i=start; i < end;i++){
        if(is_less_than(curr_node->object,lastnode->object)){
            swap(curr_node->object,front_node->object);
            front++;
            front_node = front_node->next;
        }
        curr_node=curr_node->next;        
    }
    swap(front_node->object,lastnode->object);
    QuicksortSimple(stnInfoList ,start,front - 1);
    QuicksortSimple(front_node->next ,front+ 1,end);


  //recursion level reduced
  recursionLevel--;
  return;
}

#endif
