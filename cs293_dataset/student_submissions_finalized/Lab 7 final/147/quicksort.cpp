#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#include "dictionary.h"
#include <vector>

#ifndef CODES_H
#include "codes.h"
#endif

typedef listOfObjects<TrainInfoPerStation *> TrainInfoNode;
typedef TrainInfoNode * TrainInfoNodePtr; /* THIS PLAYS THE ROLE OF INDEX FOR LINKED LISTS */

struct range{
  int startIndex, endIndex;
  TrainInfoNodePtr startPtr, endPtr;
  range(int startIndex, int endIndex, TrainInfoNodePtr startPtr, TrainInfoNodePtr endPtr): startIndex(startIndex), endIndex(endIndex), startPtr(startPtr), endPtr(endPtr){}
};

// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200

bool operator<(const TrainInfoNode &a, const TrainInfoNode &b){
  int firstday_a = 7, firstday_b = 7;
  for (int i = 0; i < 7; i++) if (a.object->daysOfWeek[i]){
    firstday_a = i; break;
  }
  for (int i = 0; i < 7; i++) if (b.object->daysOfWeek[i]){
    firstday_b = i; break;
  }
  if (firstday_a < firstday_b) return true;
  if (firstday_b < firstday_a) return false;

  return a.object->depTime < b.object->depTime;
}

TrainInfoNodePtr getRandomPivot(int sz, int startIndex, int EndIndex, int K, TrainInfoNodePtr array[], int &pivotLoc){
  int randIndex = startIndex + rand() % (EndIndex - startIndex + 1); // randIndex E [start, end]. Also end - start > 1 so the % is well-defined.
  int whereToGo = randIndex / (2*K + 1);
  bool goForwards = true;
  if (randIndex % (2*K + 1) > K){ // can't reach pivot fast enough from this element moving forwards -> go to the next element in the array and move backwards. Because of how we constructed the array, 1. a next element of the array will exist, and 2. going backwards from this next element to the pivot takes <= K time.
    whereToGo++; goForwards = false;
  }
  TrainInfoNodePtr currNode = array[whereToGo]; // possibly tail.
  if (goForwards)
    for (int _ = 0; _ < randIndex % (2*K + 1); _++)
      currNode = currNode->next;
  else if (randIndex + (2*K + 1) < sz)
    for(int _ = 0; _ < ((2*K + 1) - (randIndex%(2*K+1)) ); _++)
      currNode = currNode->prev; // since doubly linked list!
  else
    for (int _ = 0; _ < (sz-1 - randIndex); _++)
      currNode = currNode->prev;
  
  pivotLoc = randIndex;
  return currNode;

}

// swap the two nodes' pointer(TrainInfoPerStation*) values.
inline void myswap(TrainInfoNode &a, TrainInfoNode &b){
    TrainInfoPerStation *tmp = a.object;
    a.object = b.object;
    b.object = tmp;
}

TrainInfoNodePtr partition(TrainInfoNodePtr pivot, TrainInfoNodePtr start, int startIndex, TrainInfoNodePtr end, int &pivotLoc){

  myswap(*pivot, *end); // swap the pointers's values in the two nodes. This effectively swaps the TrainInfoPerStation objects the nodes hold.

  TrainInfoNodePtr x = end;
  TrainInfoNodePtr i = nullptr; // using clrs syntax i,j
  pivotLoc = startIndex; // just ahead of i.

  // run through each element(except end) of the subarray in order
  for (auto j = start; j != end; j = j->next){ // treat j like an iterator over the linked list - which it indeed is!

    if (*j < *x){
        myswap(i? *(i->next): *start, *j); // *(i->next) is the wall ie >= pivot. swap it with *j < pivot = *x.
        i = i? i->next: start; // move 'the iterator' i forward.
        pivotLoc++;
    }

  }
  myswap(i? *(i->next): *start, *end); // finally get *end = *x before all the elements >= *x
  return i? i->next: start;
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

// works fine.
void Planner::Quicksort(TrainInfoNode *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with

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
  
  int sz;
  TrainInfoNodePtr tail;
  if (!stnInfoList) return; // empty linked list

  // Find length of the list stnInfoList
  TrainInfoNodePtr currNode = stnInfoList; // not null

  // works, but we'd like to find the tail as well.
  // int sz = 1; // nonempty, so sz >= 1
  // while (currNode = currNode->next) sz++; // sz incremented everytime currNode can be updated to a non-null node.
  
  sz = 1; // nonempty, so sz >= 1
  while(currNode){
    if (currNode->next) sz++; else tail = currNode; // increase sz everytime curr has a next.
    currNode = currNode->next;
  }

  // Allocate additional space for upto n/K TrainInfoPerStation objects
  // if needed.
  // Do other things that you may want to do only at the beginning
  // as a pre-processing step.

  // we maintain an array of some particular pointers of the linkedlist from which we can get (by moving front or back(the list is doubly linked!) atmost K times from a poiner in the array) to any pointer in the list. In particular, we store head, then head + K + K + 1 = head + (2K+1), head + (2K+1) + (2K+1), ..., and tail(else if size-1 % 2K+1 != 0 and > K and we don't store tail the last few elems will required more than K steps forward from the last stored node). If time, optimize to storing tail only if size-1 % 2K+1 is > K. Doesn't really matter though since it's just 4 bytes more space for the whole algorithm.
  bool exact = ((sz-1) % (2*K+1) == 0);
  int storageIfExact = (sz-1) / (2*K+1) + 1;
  TrainInfoNodePtr storage[exact? storageIfExact: storageIfExact + 1]; // array of pointers to nodes in the ll to sort. The pointers serve like 'array of indices in the array to sort'.
  
  currNode = stnInfoList;
  for (int i = 0; i < storageIfExact; i++){
    storage[i] = currNode; // store this pointer
    if (i == storageIfExact - 1) break; // since the below loop could go off to nullptr otherwise if we're at the last few nodes

    for (int _ = 0; _ < 2*K + 1; _++) currNode = currNode->next; // move forward to currNode + (2*K+1)
  }
  if (!exact)
    storage[storageIfExact] = tail;

  // we are now done with the preprocessing step and can move on to sorting.
  
  // Put your code for the core of Quicksort here
  // the static recursionLevel calls for a recursive solution, but here we present an iterative solution which, if you imagine running, looks quite similar to how the recursive one would run. Note it does a DFS on the recursion tree, which is exactly what the recursive solution does!

  // We use extra log(n) storage instead of a recursive call stack. The storage is same either way, indices and pointers passed in if the algorithm were recursive need to be stored anyway.
  vector<range> callsLeftStack;
  range currRange(0, sz-1, stnInfoList, tail); // so end is inclusive here.

  callsLeftStack.push_back(currRange);
  while(!(callsLeftStack.empty())){
    currRange = callsLeftStack.back();
    callsLeftStack.pop_back();

    // basecase: 0 and 1 element arrays:
    if (currRange.endIndex - currRange.startIndex < 1) continue;

    int pivotLoc;
    TrainInfoNodePtr pivot = getRandomPivot(sz, currRange.startIndex, currRange.endIndex, K, storage, pivotLoc);
    pivot = partition(pivot, currRange.startPtr, currRange.startIndex, currRange.endPtr, pivotLoc);

    if (pivot->prev) // if not, then pivot is the first element and so since 0<= startIndex <= pivotLoc = 0, start = pivot and so 1-element array, we anyway return. We must take care of this here itself, since for arrays index = -1 works but here nullptr->next doesn't quite work :)
      callsLeftStack.push_back(range(currRange.startIndex, pivotLoc-1, currRange.startPtr, pivot->prev));
    if (pivot->next) 
      callsLeftStack.push_back(range(pivotLoc + 1, currRange.endIndex, pivot->next, currRange.endPtr));
  }

  return;
}

void Planner::QuicksortSimple(TrainInfoNodePtr stnInfoList, int startIndex, int endIndex){
  // tried a recursive solution this time, some bug still there in the code
  // for completeness, I have just called the above function here:
  Quicksort(stnInfoList);
  return;
}

#endif
