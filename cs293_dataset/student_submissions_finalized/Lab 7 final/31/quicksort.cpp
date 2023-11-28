#include <cstdlib>
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

int check(listOfObjects<TrainInfoPerStation* > *node, listOfObjects<TrainInfoPerStation *> *pivot){
  int l,r;
  for(int i=0; i<7; i++){
    if(node->object->daysOfWeek[i]==true)
      l=i;
  }
  for(int i=0; i<7; i++)
    if(pivot->object->daysOfWeek[i]==true)
      r=i;

  if(l>r)
    return 1;
  else if(l==r){
    if(node->object->arrTime > pivot->object->arrTime){
      return 1;
    }
    else if(node->object->arrTime == pivot->object->arrTime){
      if(node->object->depTime > pivot->object->depTime)
        return 1;
      else if(node->object->depTime == pivot->object->depTime)
        return -1;
    }
  }
  return 0;
}

void swap(listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right){
  TrainInfoPerStation* nowleft = new TrainInfoPerStation(right->object->journeyCode, right->object->stopSeq, right->object->arrTime, right->object->depTime);
  for(int i=0; i<7; i++)
    if(right->object->daysOfWeek[i]==true)
      nowleft->setDayOfWeek(i);

  TrainInfoPerStation* nowright = new TrainInfoPerStation(left->object->journeyCode, left->object->stopSeq, left->object->arrTime, left->object->depTime);
  for(int i=0; i<7; i++)
    if(left->object->daysOfWeek[i]==true)
      nowright->setDayOfWeek(i);

  /*if(left->prev!=NULL){
    (left->prev)->next=nowleft;
    nowleft->prev = left->prev;
  }
  if(left->next!=NULL){
    (left->next)->prev=nowleft;
    nowleft->next = left->next;
  } 

  if(right->prev!=NULL){
    (right->prev)->next=nowright;
    nowright->prev = right->prev;
  }
  if(right->next!=NULL){
    (right->next)->prev=nowright;
    nowright->next = right->next;
  } */

  left->object = nowleft;
  right->object = nowright;

}
listOfObjects<TrainInfoPerStation*> * partition(listOfObjects<TrainInfoPerStation *> *list, listOfObjects<TrainInfoPerStation *> *pivot, int length, int &midind, int start){
  listOfObjects<TrainInfoPerStation *> *left = list;
  listOfObjects<TrainInfoPerStation *> *right = list;
  bool k=false;
  while(true){
      while(check(right, pivot)==1){
        right = right->prev;
        if(right==left || right->next==left)
          k=true;
      }
      while(check(left,pivot)==0){
        left = left->next;
        midind++;
        if(left==right || left->prev==right)
          k=true;
      }
      if(k==false){
        swap(left,right);
        left = left->next;
        right = right->prev;
        if(left==right || right->next==left)
          k = true;
        midind++;
      }
      else return left;

  }

}

listOfObjects<TrainInfoPerStation* >* choosepivot(listOfObjects<TrainInfoPerStation *> **a, int start, int end, int k){
  srand (time(NULL));
  int ranNum = (rand() % (end-start + 1) + start);
  int nearind = ranNum/k;
  /*bool left=false;
  if(ranNum%k >= 0.5){
    nearind = ranNum/k + 1;
    left = true;
  }
  else
    nearind = ranNum/k;*/

  cout << "pivot " << ranNum << endl;
  listOfObjects<TrainInfoPerStation *> *ptr = a[nearind];
  for(int i=0; i<(ranNum-nearind*k); i++){
    ptr = ptr->next;
  }
  return ptr;

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

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  if(start>=end)
    return;
  recursionLevel++;
  cout << start << " " << end << endl;
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

  int n=(end-start+1)/K;
  static listOfObjects<TrainInfoPerStation *> **a;
  if (recursionLevel == 0) {
    a = new listOfObjects<TrainInfoPerStation *> *[n+1];
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation *> *list = stnInfoList;
    a[0] = list;
    int i=1;
    bool br = false;
    while(i<(((end-start+1)/K)+1)){
      for(int j=0; j<K; j++){
        if(list->next==NULL){
          br = true;
          break;
        }
        list = list->next;
      }
      if(br)
        break;
      a[i] = list;
      i++;
    }
  }
  int midind;
  listOfObjects<TrainInfoPerStation *> *pivot = choosepivot(a,start,end,K);
  listOfObjects<TrainInfoPerStation *> *midp = partition(stnInfoList, pivot, end-start+1, midind, start);
  cout << "midind" << midind << endl;
  if(midind==end){  
    QuicksortSimple(stnInfoList, start, midind-1);
    QuicksortSimple(midp, midind, end);
  }
  else {
    QuicksortSimple(stnInfoList, start, midind);
    QuicksortSimple(midp->next, midind+1, end);
  }
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
