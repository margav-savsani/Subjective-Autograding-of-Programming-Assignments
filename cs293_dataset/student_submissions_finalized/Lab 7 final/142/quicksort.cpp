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

template <typename T>
void swap_obj(T &obj1, T &obj2)
{
  T t = obj1;
  obj1 = obj2;
  obj2 = t;
}

void swap_train_info(TrainInfoPerStation &obj1, TrainInfoPerStation &obj2)
{
  swap_obj<int>(obj1.journeyCode, obj2.journeyCode);
  swap_obj<unsigned short>(obj1.stopSeq, obj2.stopSeq);
  for(int i = 0; i < 7; i++)
  {
    swap_obj<bool>(obj1.daysOfWeek[i], obj2.daysOfWeek[i]);
  }
  swap_obj<int>(obj1.arrTime,obj2.arrTime);
  swap_obj<int>(obj1.depTime,obj2.depTime);
}
int comparedaysofweek(TrainInfoPerStation obj1, TrainInfoPerStation obj2)
{
  int d1, d2;
  //d1 = day when 1 occurs first time for obj1
  //d2 = day when 1 occurs first time for obj2
  for(int i = 0; i < 7; i++)
  {
    if(obj1.daysOfWeek[i])
    {
      d1 = i;
      break;
    }
    else continue;
  }
  for(int i = 0; i < 7; i++)
  {
    if(obj2.daysOfWeek[i])
    {
      d2 = i;
      break;
    }
    else continue;
  }
  if(d1<d2)return 1;
  if(d1==d2) return 0;
  if(d1>d2)return -1;
}
//function to first obtain random pointer to object in array pivots and then pointer to random object from the sublist that the pointer points to
listOfObjects<TrainInfoPerStation*>* ran_pivot(listOfObjects<TrainInfoPerStation*> *pivots, int n, int K)
{
  int i = rand()%(n/K);
  int j = rand()%K;
  int x = 0;
  listOfObjects<TrainInfoPerStation*>*pivotk = &pivots[i];
  while(x < j)
  {
    pivotk = pivotk->next;
    x++;
  }
  return pivotk;
}
// listOfObjects<TrainInfoPerStation*>* Planner::partition(listOfObjects<TrainInfoPerStation*> *stnInfoList, int start, int end)
// {
 
//   return pivots;
// }
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
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    int n = end - start + 1;
    int i = 0;
    static listOfObjects<TrainInfoPerStation*>** pivots = new listOfObjects<TrainInfoPerStation*>*();
    //array of pointer to pivots
    //dividing the entire list of objects into n/k parts each of size K
    //pointer to first object in each part is stored in array
    //thus each element of array "pivots" is start for sublist of size K
    while(i < n)
    {
      if(i%K==0)
      {
        pivots[i] = stnInfoList;
      }
      stnInfoList = stnInfoList->next;
      i++;
    }
    //reset stnInfoList to its initial value
    stnInfoList = pivots[0];
    listOfObjects<TrainInfoPerStation*> *pivot_obj = ran_pivot(*pivots,n,K);
    // listOfObjects<TrainInfoPerStation*> *pivot_obj_ptr = &pivot_obj;
    listOfObjects<TrainInfoPerStation*> *first_obj = stnInfoList;
    listOfObjects<TrainInfoPerStation*> *last_obj = stnInfoList;
    int a = 0;
    while(a<(end-start+1))
    {
      last_obj = last_obj->next;
      a++;
    }
        swap_train_info(pivot_obj,last_obj);

    // TrainInfoPerStation *x = *last_obj;
    // first_obj = pivot_obj->prev;
    // last_obj = last_obj->next;
    int start_ini = start;
    int end_ini = end;
    while(true)
    {
      if(comparedaysofweek(pivot_obj,first_obj)==1 && comparedaysofweek(last_obj,pivot_obj)==1)//returns true if stnInfoList occurs before pivot_obj
      {
        swap_train_info(*first_obj, *last_obj);
      }
      if(comparedaysofweek(pivot_obj,first_obj)==0 && comparedaysofweek(last_obj,pivot_obj)==0)
      {
        if(first_obj->depTime > pivot_obj->depTime && last_obj->depTime < pivot_obj->depTime)
        {
          swap_train_info(*first_obj, *last_obj);
        }
      }
        last_obj = last_obj->prev;
        end--;
        first_obj = first_obj->next;
        start++;
        if(start < end)
        {
            swap_train_info(first_obj,last_obj);
        }
        else break;
    }
    QuicksortSimple(stnInfoList,start_ini,start);
    QuicksortSimple(stnInfoList,start, end_ini);
}

  // Put your code for the core of QuicksortSimple here
  // listOfObjects<TrainInfoPerStation*> *p = pivots();

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
