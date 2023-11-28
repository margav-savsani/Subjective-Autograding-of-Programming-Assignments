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

int Planner::Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation *> *pivot)
{
  listOfObjects<TrainInfoPerStation *> *front = stnInfoList;    //pointer to traverse the list from front
  int s = start;
  int e = end;
  while(start != 0)   //getting the node at starting index
  {
    front = front->next;
    start--;
  }
  start = s;
  listOfObjects<TrainInfoPerStation *> *back = stnInfoList;   //pointer to traverse the list from the  back
  while(end != 0)   //getting the node at ending index
  {
    back = back->next;
    end--;
  }
  end = e;
  TrainInfoPerStation *temp = back->object;   //swapping the value of pivot with the last element
  back->object = pivot->object;
  pivot->object = temp;
  TrainInfoPerStation *p = back->object;
  int k = 0;
  while(!p->daysOfWeek[k])
  {
    k++;
    if(k>=7)
    {
      break;
    }
  }
  while(true)
  {
    while(true)   //traversing from the front till we find a node with value greater than or equal to the pivot
    {
      int i = 0;
      while(!front->object->daysOfWeek[i])
      {
        i++;
        if(i>=7)
        {
          break;
        }
      }
      if(i>k)
      {
        break;
      }
      else if (i == k && front->object->arrTime >= p->arrTime)
      {
        break;
      }
      else
      {
        if(s<end)
        {
          front = front->next;
          s++;
        }
        else
        {
          break;
        }
      }
    }
    while(true)   //traversing from the back till we find a node with value less than or equal to the pivot
    {
      int i = 0;
      while(!back->object->daysOfWeek[i])
      {
        i++;
        if(i>=7)
        {
          break;
        }
      }
      if(i<k)
      {
        break;
      }
      else if (i == k && back->object->arrTime <= p->arrTime)
      {
        break;
      }
      else
      {
        if(e>start)
        {
          back = back->prev;
          e--;
        }
        else
        {
          break;
        }
      }
    }
    if(!(s<e))
    {
      return s;   //returning if s>=e
    }
    else
    {
      TrainInfoPerStation *temp = back->object;   //else swapping the values of the nodes found
      back->object = front->object;
      front->object = temp;
      front = front->next;
      s++;
      back = back->prev;
      e--;
    }
  }
  return -1;
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
  // across all recursions.
  static int n = 0;
  static int start = 0;
  static int end = 0;
  static listOfObjects<TrainInfoPerStation *> *obj = stnInfoList;
  static listOfObjects<TrainInfoPerStation *> **stations;
  static listOfObjects<TrainInfoPerStation *> *node = stnInfoList; 
  static listOfObjects<TrainInfoPerStation *> *last = stnInfoList;
  static int r1 = 0;

  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    if(obj != NULL)
    {
    while(obj->next != nullptr)
    {
      obj = obj->next;
      last = last->next;
      end++;
    }
    obj = stnInfoList;
    n = (end - start + 1)/K;
    stations = new listOfObjects<TrainInfoPerStation *>*[n+1];
  }
  }
  if(obj != NULL)
  {
  end = 0;
  while(obj->next != nullptr)
  {
    obj = obj->next;
    end++;
  }
  if(end>start){
    node = stnInfoList; 
    for(int i = 0; i<start; i++)
    {
      node = node->next;
    }
    for(int i = 0; i<(end - start + 1); i++)
    {
      if(i%K == 0)
      {
        stations[i/K] = node;
      }
      node = node->next;
    }
    srand(time(0));
    r1 = rand();
    r1 = r1%(end - start + 1);
    node = stations[r1/K];
    for(int i = 0; i<r1%K; i++)
    {
      node = node->next;
    }
    int p = Partition(stnInfoList,start,end,node);
    obj = stnInfoList;
    for(int i = 0; i<=p; i++)
    {
      obj = obj->next;
    }
    Quicksort(obj);
    obj = stnInfoList;
    for(int i = 0; i<=p; i++)
    {
      obj = obj->next;
    }
    if(obj->prev != nullptr)
    {
      obj->prev->next = nullptr;
    }
    Quicksort(stnInfoList);
  }
  }
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  if(recursionLevel == -1)
  {
    while(last->prev != nullptr)
    {
      if(last->prev->next == nullptr)
      {
        last->prev->next = last;
      }
    }
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
  // across all recursions. 
  static int n;   //stores the value of N/K
  static int p = 0;   //stored the partition index
  static listOfObjects<TrainInfoPerStation *> **stations;   //array pointer for finding pivot in O(K)
  static listOfObjects<TrainInfoPerStation *> *node = stnInfoList;    //a node element of the list to traverse the list.
  static int r1 = 0;    //stores the value of random number generated.
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    n = (end - start + 1)/K;
    stations = new listOfObjects<TrainInfoPerStation *>*[n+1];    //defining an array of size O(N/K)
  }
  
  // Put your code for the core of QuicksortSimple here
  if(end>start){
    node = stnInfoList; 
    for(int i = 0; i<start; i++)    //finding the node at starting index.
    {
      node = node->next;
    }
    for(int i = 0; i<(end - start + 1); i++)    //storing the node at equal N/K intervals in the array
    {
      if(i%K == 0)
      {
        stations[i/K] = node;
      }
      node = node->next;
    }
    srand(time(0));   //defining a seed
    r1 = rand();    //getting a random number
    r1 = r1%(end - start + 1);    //scaling the random number fown to the size of the list
    node = stations[r1/K];    
    for(int i = 0; i<r1%K; i++)   //finding the random pivot
    {
      node = node->next;
    }
    p = Partition(stnInfoList,start,end,node);    //partitioning the list
    QuicksortSimple(stnInfoList,start,p-1);
    QuicksortSimple(stnInfoList,p,end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
