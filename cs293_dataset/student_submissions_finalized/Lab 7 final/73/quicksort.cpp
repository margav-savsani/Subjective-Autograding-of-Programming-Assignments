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
void swap(listOfObjects<TrainInfoPerStation *> *St1,listOfObjects<TrainInfoPerStation *> *St2)
{
  //function that swaps the Train info in the 2 pointers
  TrainInfoPerStation *sample;
  sample=St1->object;
  St1->object=St2->object;
  St2->object=sample;
}
bool greaterthan(listOfObjects<TrainInfoPerStation *> *St1,listOfObjects<TrainInfoPerStation *> *St2)
{
  //functions checks which comes late by given info
  for(int i=0;i<7;i++)
  {
    if( !St1->object->daysOfWeek[i] && St2->object->daysOfWeek[i])
      return true;
    else if (St1->object->daysOfWeek[i] && St2->object->daysOfWeek[i])
    {
      if (St1->object->arrTime > St2->object->arrTime)
        return true;
      else if (St1->object->arrTime == St2->object->arrTime)
      {
        if (St1->object->depTime > St2->object->depTime)
          return true;
        else if (St1->object->depTime == St2->object->depTime)
        {
          if (St1->object->journeyCode > St2->object->journeyCode)
            return true;
          else
            return false;
        }
        else 
          return false;
      }
      else
        return false;
    }
    else if (St1->object->daysOfWeek[i] && !St2->object->daysOfWeek[i])
      return false;
  }
  return false;
}
listOfObjects<TrainInfoPerStation *> *Planner::Partion(listOfObjects<TrainInfoPerStation *> *Start, listOfObjects<TrainInfoPerStation *> *end,listOfObjects<TrainInfoPerStation *> *pivot,int s,int e)
{
  //we will first shift the node to the last place of the list
  //the we do the partition 
  listOfObjects<TrainInfoPerStation *> *node;
  //swaps only Train info not the pointers
  swap(pivot,end);
  node=pivot;
  pivot=end;
  end=pivot;
  node=Start->prev;
  for (listOfObjects<TrainInfoPerStation *> *sample=Start;sample != end;sample=sample->next)
  {
    if (!greaterthan(sample,pivot))
    {
      if (node==nullptr)
        node=Start;
      else
        node=node->next;
      swap(node,sample);
    }
  }
  if (node==nullptr)
    node=Start;
  else
    node=node->next;
  swap(node,pivot);
  return node;
  //PARTITION of the list
  //one will start from the start and the other is from end
  //if the nodes from start is greater than the pivot then replace it with the nodes that are less than pivot from end
  //after the crossover return the end
  /*if (s==e)
    return end;
  while(true)
  {
    while ( greaterthan(end,pivot))
    {
      end=end->prev;
      e--;
    }
    while( greaterthan(pivot,Start))
    {
      Start=Start->next;
      s++;
    }
    if (s<e)
    {
      swap(Start,end);
    }
    else
      return end;
  }
  return end;*/
}
listOfObjects<TrainInfoPerStation *> *Planner::pivot(listOfObjects<TrainInfoPerStation *> **stnInfo,int k,int start,int end)
{
  //genarating pivot in O(K) time using arrays
  //by start and end we will get the random number in the range we required
  //by dividing with K we will get the index of the arr and reminder we will get the exact node from it
  //so its max order is O(K)
  int p=rand()%(end-start+1)+start;
  int q=p/k;
  int r=p%k;
  listOfObjects<TrainInfoPerStation *> *sample;
  sample=stnInfo[q];
  for (int i=0;i<r;i++)
    sample=sample->next;
  return sample;
}
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **objects;
  if (stnInfoList->next == nullptr)
    return;
  if (stnInfoList == nullptr)
    return;
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
    int n=0;
    listOfObjects<TrainInfoPerStation *> *sample=stnInfoList;
    while(sample != nullptr)
    {
      n++;
      sample=sample->next;
    }
    sample=stnInfoList;
    objects=new listOfObjects<TrainInfoPerStation *>* [(int)(n/K)+1];
    for (int i=0;i<n;i++)
    {
      if (i%K==0)
      {
        objects[i/K]=sample;
      }
      sample=sample->next;
    }
  }
  int n=0;
  listOfObjects<TrainInfoPerStation *> *sample=stnInfoList;
  while(sample->next != nullptr)
  {
    n++;
    sample=sample->next;
  }
  // Put your code for the core of Quicksort here
  n++;//checking for last elements index
  QuicksortSimple(stnInfoList,0,n-1);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 5; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **objects;
  if (start > end)//cases where it should return 
    return;
  if (stnInfoList == nullptr)
    return;
  if (start == end)
    return;
  if (stnInfoList->next == nullptr)
    return;
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
    int n=0;
    listOfObjects<TrainInfoPerStation *> *sample=stnInfoList;
    while(sample != nullptr)
    {
      n++;//for number of elements in the list
      sample=sample->next;
    }
    sample=stnInfoList;
    objects=new listOfObjects<TrainInfoPerStation *>* [(int)(n/K)+1];//creating the array
    for (int i=0;i<n;i++)
    {
      if (i%K==0)
      {
        //keeping the pointers that are at space K in the array
        objects[i/K]=sample;
      }
      sample=sample->next;
    }
  }
  listOfObjects<TrainInfoPerStation *> *stnend=stnInfoList,*Piv,*sample;
  for(int i=0;i<end-start;i++)
    stnend=stnend->next;
  Piv=pivot(objects,K,start,end);//pivot genaration
  Piv=Partion(stnInfoList,stnend,Piv,start,end);//partition 
  sample=stnInfoList;
  int num=start;
  while ( sample != Piv)
  {
    num++;//getting the pivot index
    sample=sample->next;
  }
  if (num < end)
  {//quicksort
    QuicksortSimple(stnInfoList,start,num);
    QuicksortSimple(Piv->next,num+1,end);
  }
  else
  {
    QuicksortSimple(stnInfoList,start,num-1);
    QuicksortSimple(Piv,num,end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
//by saran 210050036