#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP
#include<random>

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

bool greaterThan(TrainInfoPerStation* t1, TrainInfoPerStation* t2){
  int day_t1;
  int day_t2;

  for (int i = 0; i < 7; i++)
  {
    if (t1->daysOfWeek[i])
    {
      day_t1 = i;
      break;
    }
  }

  for (int i = 0; i < 7; i++)
  {
    if (t2->daysOfWeek[i])
    {
      day_t2 = i;
      break;
    }
    
  }
  
  if (day_t1 > day_t2)
  {
    return true;
  }

  else if (day_t1 < day_t2)
  {
    return false;
  }

  if (t1->depTime == -1 || t2->depTime == -1)
  {
    if (t1->depTime == -1 && t2->depTime == -1)
    {
      return false;
    }
    
    return !(t1->depTime > t2->depTime);
  }

  return t1->depTime > t2->depTime; 
}

void swapElements(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  TrainInfoPerStation * temp_a = a ->object;
  a -> object = b -> object;
  b -> object = temp_a;
}

int getLength(listOfObjects<TrainInfoPerStation *> *startPtr){
  listOfObjects<TrainInfoPerStation *> *ptr = startPtr -> next;
  int len = 1;

  while (ptr != nullptr)
  {
    ptr = ptr -> next;
    len++;
  }
  
  return len;
}

int getRand(int min, int max){
  return (random()%(max-min + 1) + min);
}

listOfObjects<TrainInfoPerStation *> *getElement(listOfObjects<TrainInfoPerStation *> **heads, int K, int i){
  listOfObjects<TrainInfoPerStation *> *ptr = heads[i/K];
  for (int j = 0; j < i%K; j++)
  {
    ptr = ptr -> next;
  }

  return ptr;
  
}

TrainInfoPerStation* pivotChooser(listOfObjects<TrainInfoPerStation *> **heads, int K, int i , int j){
  int pivot = getRand(i, j);

  return getElement(heads, K, pivot) -> object;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int start = 0;
  static int end = 0;
  static listOfObjects<TrainInfoPerStation *> **heads;
  // static listOfObjects<TrainInfoPerStation* >* data = new listOfObjects<TrainInfoPerStation >[]; 

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
    static int n = getLength(stnInfoList);
    end = n - 1;

    listOfObjects<TrainInfoPerStation*> *ptr = stnInfoList;
    heads = new listOfObjects<TrainInfoPerStation*>*[(n/K) + 1]; // pointers to the listOfObjects<T>*

    int i = 0;
    while (ptr != nullptr)
    {
      if(i%K == 0){
        heads[i/K] = ptr;
      }
      i++;
      ptr = ptr -> next;
    }

    recursionLevel++; 
    Quicksort(stnInfoList);
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
    if(end - start <= 0){
      return;
    }

    int left_count = start;
    int right_count = end;
    TrainInfoPerStation* pivot = pivotChooser(heads,K,start,end);
    listOfObjects<TrainInfoPerStation *> *left = getElement(heads, K, start);  
    listOfObjects<TrainInfoPerStation *> *right= getElement(heads, K, end);  

    while (left_count < right_count)
    {
      while (greaterThan(right->object,pivot))
      {
        right = right -> prev; 
        right_count--;
      }

      while (greaterThan(pivot,left->object))
      {
        left = left -> next; 
        left_count++;
      }
      
      swapElements(right, left);
    }

    start = start;
    end =  left_count - 1;
    Quicksort(stnInfoList);

    start = left_count + 1;
    end =  end;
    Quicksort(stnInfoList); 
    // TrainInfoPerStation* pivot = 
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int _start, int _end)
{
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which

  int start = _start;
  int end = _end;
  static listOfObjects<TrainInfoPerStation *> **heads;
  recursionLevel++;
  
  
  if (recursionLevel == 0) {
    static int n = getLength(stnInfoList);
    end = n - 1;

    listOfObjects<TrainInfoPerStation*> *ptr = stnInfoList;
    heads = new listOfObjects<TrainInfoPerStation*>*[(n/K) + 1]; // pointers to the listOfObjects<T>*

    int i = 0;
    while (ptr != nullptr)
    {
      if(i%K == 0){
        heads[i/K] = ptr;
      }
      i++;
      ptr = ptr -> next;
    }

    recursionLevel++; 
    Quicksort(stnInfoList);
  }
  
    if(end - start <= 0){
      return;
    }

    int left_count = start;
    int right_count = end;
    TrainInfoPerStation* pivot = pivotChooser(heads,K,start,end);
    listOfObjects<TrainInfoPerStation *> *left = getElement(heads, K, start);  
    listOfObjects<TrainInfoPerStation *> *right= getElement(heads, K, end);  

    while (left_count < right_count)
    {
      while (greaterThan(right->object,pivot))
      {
        right = right -> prev; 
        right_count--;
      }

      while (greaterThan(pivot,left->object))
      {
        left = left -> next; 
        left_count++;
      }
      
      swapElements(right, left);
    }

    start = start;
    end =  left_count - 1;
    QuicksortSimple(stnInfoList,start,end);

    start = left_count + 1;
    end =  end;
    QuicksortSimple(stnInfoList,start,end); 
  recursionLevel--;
  return;
  
}

#endif
