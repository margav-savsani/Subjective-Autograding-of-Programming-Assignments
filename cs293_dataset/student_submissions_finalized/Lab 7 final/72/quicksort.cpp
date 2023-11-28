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

bool lessThan(TrainInfoPerStation *A, TrainInfoPerStation *B){
  // Function to compare two TrainInfo stations
  for(int i = 0; i < 7; i++){
    if(A->daysOfWeek[i] > B->daysOfWeek[i])return true;
    if(A->daysOfWeek[i] < B->daysOfWeek[i])return false;
    if(A->daysOfWeek[i] == 0)continue;
    if(A->depTime < B->depTime)return true;
    if(A->depTime > B->depTime)return false;
    if(A->arrTime <= B->arrTime)return true;
    else return false;
  }
  return true;
}

int Planner::Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation *> *myRandPoin, int ran){
  // My extra variables which won't be created when every time the function is called.
  static listOfObjects<TrainInfoPerStation *> *begin;
  static listOfObjects<TrainInfoPerStation *> *finish;
  static listOfObjects<TrainInfoPerStation *> *dummy;
  dummy = stnInfoList;
  for(int i = 0; i <= end; i++){
    if(i == start)begin =dummy;
    if(i == end)finish = dummy;
    dummy = dummy->next;
  }
  dummy = begin;
  int count = 0;
  while(dummy != finish->next){
    if(lessThan(dummy->object, myRandPoin->object))count++;
    dummy = dummy->next;
  }
  // Moving the pivot to the appropriate position.
  dummy = begin;
  for(int i =1; i<count; i++){
    dummy = dummy->next;
  }
  // TrainInfoPerStation *ddd = myRandPoin->object;
  // if(dummy!=myRandPoin){
  // myRandPoin->object = dummy->object;
  // dummy->object = ddd;}
  swap(dummy->object,myRandPoin->object);
  int pividx = start + count -1;
  //Implementing the partition 
  while(begin->object != dummy->object && finish->object != dummy->object){
    while(lessThan(begin->object,dummy->object) && begin->object != dummy->object){
      begin = begin->next;
    }
    while(lessThan(dummy->object,finish->object) && finish->object != dummy->object){
      finish = finish->prev;
    }
    if(begin->object != dummy->object && finish->object != dummy->object){
      // TrainInfoPerStation *sss = finish->object;
      // finish->object = begin->object;
      // begin->object = sss;
      swap(finish->object,begin->object);
    }
  }
  return pividx;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Static variables to store an array of pointers
  static listOfObjects<TrainInfoPerStation *>* *myArr;
  // Static variables which decide on which part of list the quicksort ha sto applied.
  static int a, b;
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
    a=0;
    b=0;
    listOfObjects<TrainInfoPerStation *> *Mypointer = stnInfoList;
    while( Mypointer->next != nullptr){
      Mypointer = Mypointer->next;
      b++;
    }
    int l = b -a+1;
    int ceil = 0;
    if(l%K == 0)ceil = l/K;
    else ceil = l/K +1;
    myArr = new listOfObjects<TrainInfoPerStation *>*[ceil];
    Mypointer = stnInfoList;
    for(int i = 0; i < ceil; i++){
      myArr[i] = Mypointer;
      if(i == ceil-1)continue;
      for(int j = 0; j < K;j++){
        Mypointer=Mypointer->next;
      }
    }
  }
  
  // Put your code for the core of Quicksort here
  // Implementing the base case of quicksort.
  if(b <= a){
    recursionLevel--;
    return;
  }

  //Part of code that generates a random pivot in O(K) time.
  int len = b - a +1;
  int ran = a + rand()%len;
  static listOfObjects<TrainInfoPerStation *> *myRandPoin;
  myRandPoin = myArr[ran/K];
  for(int i = 0; i < ran%K; i++){
    myRandPoin = myRandPoin->next;
  }
  int par = Partition(stnInfoList,a,b,myRandPoin,ran);
  // Making the recursive calls with appropriate start and end.
  int c = b;
  b = par -1;
  Quicksort(stnInfoList);
  b = c;
  c = a;
  a = par +1;
  Quicksort(stnInfoList);
  a = c;

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Static variables to store an array of pointers
  static listOfObjects<TrainInfoPerStation *>* *myArr;
  // Increment recursion level on entering the function

  // Implementing base case of recursion.
  if(end <= start)return;
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
    int l = end -start+1;
    int ceil = 0;
    if(l%K == 0)ceil = l/K;
    else ceil = l/K +1;
    myArr = new listOfObjects<TrainInfoPerStation *>*[ceil];
    listOfObjects<TrainInfoPerStation *> *Mypointer = stnInfoList;
    for(int i = 0; i < ceil; i++){
      myArr[i] = Mypointer;
      if(i == ceil-1)continue;
      for(int j = 0; j < K;j++){
        Mypointer=Mypointer->next;
      }
    }

  }
  
  // Put your code for the core of QuicksortSimple here

  //Part of code that generates a random pivot in O(K) time.
  int len = end - start +1;
  int ran = start + rand()%len;
  static listOfObjects<TrainInfoPerStation *> *myRandPoin;
  myRandPoin = myArr[ran/K];
  for(int i = 0; i < ran%K; i++){
    myRandPoin = myRandPoin->next;
  }
  int par = Partition(stnInfoList,start,end,myRandPoin,ran);
  // Making the recursive calls with appropriate start and end.
  QuicksortSimple(stnInfoList,start,par-1);
  QuicksortSimple(stnInfoList,par+1,end);

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
