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


// Less than comparision for i1->object and i2->object
// Returns true if i1 should be displayed before i2
// Returns false otherwise
bool lt(listOfObjects<TrainInfoPerStation*> *i1, listOfObjects<TrainInfoPerStation*> *i2) 
{
  for(int i=0; i<7; i++)
  {
    if((i1->object)->daysOfWeek[i] && (i2->object)->daysOfWeek[i]) // Same day
    {
      return (i1->object)->depTime < (i2->object)->depTime;
    }
    else if((i1->object)->daysOfWeek[i])  // i1 departs at an earlier day of week
      return true;
    else if((i2->object)->daysOfWeek[i])  // i2 departs at an earlier day of week
      return false;
  }
  return false;
}


// Equal to comparision for i1->object and i2->object
// Returns true if i1 and i2 have same day as well as same departure time
// Returns false otherwise
bool eq(listOfObjects<TrainInfoPerStation*> *i1, listOfObjects<TrainInfoPerStation*> *i2)
{
  for(int i=0; i<7; i++)
  {
    if((i1->object)->daysOfWeek[i] && (i2->object)->daysOfWeek[i])  // Same day
    {
      return (i1->object)->depTime == (i2->object)->depTime;
    }
  }
  return false; // Different days
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
  static int K = 4; // Parameter to be experimented with
  static int N = 0; // Total elements in stnInfoList
  static int start=0; // Start location
  static int end=0; // End location
  int n=end-start+1; // Number of elements to be sorted in this call
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation*>* *headStnInfo; // n/K TrainInfoPerStation
  static bool NLessThanK=false; // True if N<K


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
    listOfObjects<TrainInfoPerStation*> *curr=stnInfoList;  
    while(curr!=nullptr)
    {
      N++;
      curr=curr->next;
    }
    n=N;  // All elements are to be sorted during first call
    start=0;
    end=N-1;
    if(N<K) // Just do normal Quicksort without any constraints
    {
      NLessThanK=true;
    }
    else 
    {
      listOfObjects<TrainInfoPerStation *> *currStnInfo=stnInfoList;
      headStnInfo= new listOfObjects<TrainInfoPerStation*>*[N/K]; // Array of pointers to head station which are at indices 0, K, 2K,... so that randomly choosing pivot takes O(K) time
      int total=0;  // Number of elements filled in headStnInfo
      for(int i=0; i<N; i++)
      {
        if(i%K==0 && total<N/K)
        {
          headStnInfo[i/(N/K)]=currStnInfo;
          total++;
        }
        currStnInfo=currStnInfo->next;
      }
    }
    
  }

  if(start>=end)  // Nothing to sort
  {
    if(recursionLevel==0) // Reset static variables for next call of Quicksort
    {
      N=0;
      start=0;
      end=0;
    }
    recursionLevel--;
    return;
  }

  // Put your code for the core of Quicksort here
  
  listOfObjects<TrainInfoPerStation*> *pivotStnInfo;  // Pivot for partition
  int pivotIndex = rand()%n+start;  // Pivot index
  if(NLessThanK)  // Normal Quicksort
  {
    pivotStnInfo= stnInfoList;
    for(int i=0; i<pivotIndex; i++) // Find Pivot
    {
      pivotStnInfo=pivotStnInfo->next;
    }
  }
  else
  {
    int headIndex =pivotIndex/K;  // Nearest head index preceeding Pivot
    if(headIndex==N/K)  // As it is not necessary that K divides N, so we would only have floor(N/K) heads
      headIndex--;
    pivotStnInfo= headStnInfo[headIndex];
    for(int i=0; i<pivotIndex-headIndex*K; i++) // Find Pivot
    {
      pivotStnInfo=pivotStnInfo->next;
    }
  }
  listOfObjects<TrainInfoPerStation*> *i=pivotStnInfo;  // Represents i in Prof. Garg's Lecture
  int indexi= pivotIndex; // Index of i
  for(int k=0; k<(pivotIndex-start); k++) // Find i
  {
    i=i->prev;
    indexi--;
  }
  listOfObjects<TrainInfoPerStation*> *j=pivotStnInfo; // Represents j in Prof. Garg's Lecture
  int indexj= pivotIndex; // Index of j
  for(int k=0; k<(end-pivotIndex); k++) // Find j
  {
    j=j->next;
    indexj++;
  }
  
  // copy of pivotStnInfo->object as pivotStnInfo might get swapped during partition process
  pivotStnInfo=new listOfObjects<TrainInfoPerStation*>(pivotStnInfo->object);

  while(true)
  {
    while(lt(i, pivotStnInfo))  // Search for i >= pivotStnInfo
    {
      i=i->next;
      indexi++;
    }
    while(lt(pivotStnInfo, j))  // Search for j <= pivotStnInfo
    {
      j=j->prev;
      indexj--;
    }
    if(indexi<indexj) // Swap possible
    {
      // swap i and j iff both doesn't have same departure time on same day
      if(eq(i, j))
      {
        indexi++;
        i=i->next;
        if(indexi==indexj)  // We have successfully partitioned list
          break;
        continue; // Continue
      }

      // Swap objects of i and j
      listOfObjects<TrainInfoPerStation*> *temp=new listOfObjects<TrainInfoPerStation*>(i->object);
      i->object=j->object;
      j->object=temp->object;
    }
    else
      break;  // We have successfully partitioned list
  }
  

  // Change static variables to mimic QuicksortSimple
  if(indexi==start) // See QuicksortSimple
  {
    start=start+1;
    Quicksort(stnInfoList);
    start=start-1;
  }
  else if(indexj==end)  // See QuicksortSimple
  {
    end=end-1;
    Quicksort(stnInfoList);
    end=end+1;
  }
  else  // See QuicksortSimple
  {
    int temp=end;
    end=indexj;
    Quicksort(stnInfoList);
    end=temp;

    temp=start;
    start=indexj+1;
    Quicksort(stnInfoList);
    start=temp;
  }

  if(recursionLevel==0) // Reset static variables for next call of Quicksort
  {
    N=0;
    start=0;
    end=0;
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *&stnInfoList, int start, int end)
{
  if(start>=end)  // Nothing to sort
    return;


  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int N = 0; // Total elements in stnInfoList
  int n=end-start+1; // Number of elements to be sorted in this call
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation*>* *headStnInfo; // n/K TrainInfoPerStation
  static bool NLessThanK=false;
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
    N=n;  // All elements are to be sorted during first call
    if(N<K)  // Just do normal QuicksortSimple without any constraints
    {
      NLessThanK=true;
    }
    else
    {
      listOfObjects<TrainInfoPerStation *> *currStnInfo=stnInfoList;
      headStnInfo= new listOfObjects<TrainInfoPerStation*>*[N/K];  // Array of pointers to head station which are at indices 0, K, 2K,... so that randomly choosing pivot takes O(K) time
      int total=0;  // Number of elements filled in headStnInfo
      for(int i=0; i<N; i++)
      {
        if(i%K==0 && total<N/K)
        {
          headStnInfo[i/(N/K)]=currStnInfo;
          total++;
        }
        currStnInfo=currStnInfo->next;
      }
    }
  }

  // Put your code for the core of QuicksortSimple here
  listOfObjects<TrainInfoPerStation*> *pivotStnInfo;  // Pivot for partition
  int pivotIndex = rand()%n+start;  // Pivot index
  if(NLessThanK)  // Normal QuicksortSimple
  {
    pivotStnInfo= stnInfoList;
    for(int i=0; i<pivotIndex; i++)  // Find Pivot
    {
      pivotStnInfo=pivotStnInfo->next;
    }
  }
  else
  {
    int headIndex =pivotIndex/K;  // Nearest head index preceeding Pivot
    if(headIndex==N/K)  // As it is not necessary that K divides N, so we would only have floor(N/K) heads
      headIndex--;
    pivotStnInfo= headStnInfo[headIndex];
    for(int i=0; i<pivotIndex-headIndex*K; i++)  // Find Pivot
    {
      pivotStnInfo=pivotStnInfo->next;
    }
  }
  listOfObjects<TrainInfoPerStation*> *i=pivotStnInfo;  // Represents i in Prof. Garg's Lecture
  int indexi= pivotIndex;  // Index of i
  for(int k=0; k<(pivotIndex-start); k++)  // Find i
  {
    i=i->prev;
    indexi--;
  }
  listOfObjects<TrainInfoPerStation*> *j=pivotStnInfo;  // Represents j in Prof. Garg's Lecture
  int indexj= pivotIndex;  // Index of j
  for(int k=0; k<(end-pivotIndex); k++)  // Find j
  {
    j=j->next;
    indexj++;
  }
  
  // copy of pivotStnInfo->object as pivotStnInfo might get swapped during partition process
  pivotStnInfo=new listOfObjects<TrainInfoPerStation*>(pivotStnInfo->object);

  while(true)
  {
    while(lt(i, pivotStnInfo))  // Search for i >= pivotStnInfo
    {
      i=i->next;
      indexi++;
    }
    while(lt(pivotStnInfo, j))  // Search for j <= pivotStnInfo
    {
      j=j->prev;
      indexj--;
    }
    if(indexi<indexj)  // Swap possible
    {
      // swap i and j iff both doesn't have same departure time on same day
      if(eq(i, j))
      {
        indexi++;
        i=i->next;
        if(indexi==indexj)  // We have successfully partitioned list
          break;
        continue;  // Continue
      }

      // Swap objects of i and j
      listOfObjects<TrainInfoPerStation*> *temp=new listOfObjects<TrainInfoPerStation*>(i->object);
      i->object=j->object;
      j->object=temp->object;
    }
    else
      break;  // We have successfully partitioned list
  }
  
  if(indexi==start) // Element at start is already smallest among all to sort which is also our pivot
  {
    QuicksortSimple(stnInfoList, start+1, end);
  }
  else if(indexj==end)  // Element at end is already largest among all to sort which is also our pivot
  {
    QuicksortSimple(stnInfoList, start, end-1);
  }
  else  // Normal partition
  {
    QuicksortSimple(stnInfoList, start, indexj);
    QuicksortSimple(stnInfoList, indexj+1, end);
  }



  // Decrement recursion level before leaving the function
  recursionLevel--;

  return;
}

#endif
