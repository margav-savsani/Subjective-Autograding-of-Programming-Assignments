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
#include <time.h>
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

// void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
// {
//   // A few static variable declarations
//   static int K = 4; // Parameter to be experimented with
//   static int recursionLevel = -1; // This can be used to find out at which
//                                   // level of the recursion you are in

//   // Increment recursion level on entering the function
//   recursionLevel++;
  
//   // If you need to set up additional storage (upto n/K TrainInfoPerStation
//   // elements), it's ok to do it *once* using static variables/array.
//   // Using the static recursionLevel, you can ensure that the storage
//   // allocation is done only the first time Quicksort is called, and not
//   // in every recursive call.
//   //
//   // Note that if you allocate space for upto n/K TrainInfoPerStation in
//   // each recursive call, you will end up using much more than n/K space
//   // overall.  So you MUST NOT allocate space in each recursive call.
//   //
//   // A variable/array defined using static is not created afresh in
//   // each recursive call.  Instead, a single copy of it is maintained
//   // across all recursions.
  
//   if (recursionLevel == 0) {
//     // Find length of the list stnInfoList, if needed.
//     // Allocate additional space for upto n/K TrainInfoPerStation objects
//     // if needed.
//     // Do other things that you may want to do only at the beginning
//     // as a pre-processing step.
//   }
  
//   // Put your code for the core of Quicksort here

//   // Decrement recursion level before leaving the function
//   recursionLevel--;
//   return;
// }
//this function selects pivot randomly and returns pointer to that node.
listOfObjects<TrainInfoPerStation *> * returnpivot(listOfObjects<TrainInfoPerStation *> *head,int start,int end,int n,int k){
  int x;
  if(n%k==0){x=n/k;}
  else{x=(n/k)+1;}
  listOfObjects<TrainInfoPerStation *> *curr=head;
  //creared static because it should not allocate freshly on each call of funmction it should
  //just rewrite it.
  static listOfObjects<TrainInfoPerStation *>**arr = new listOfObjects<TrainInfoPerStation *>* [x];
  for(int i=0;i<x;i++){
    arr[i]=curr;
    if(i!=x-1){
    for(int i=0;i<k;i++){
      curr=curr->next;
    }
    }
  }
  srand(time(NULL));
  int r1;
  if(x==1){r1=0;}
  else{r1=rand()%x;}
  int r2=rand()%k;
  for(int i=0;i<r2;i++){
    if(r1+r2>=n){break;}
    if(arr[r1]->next==nullptr){break;}
    arr[r1]=arr[r1]->next;
  }
  return arr[r1];

}
//this function returns true if l1 appeared early than l2 else return false.
bool lessthan(listOfObjects<TrainInfoPerStation *>*l1,listOfObjects<TrainInfoPerStation *>*l2){
 int x1;
 int x2;
 for(int i=0;i<7;i++){
  if(l1->object->daysOfWeek[i]==true){x1=i;}
  if(l2->object->daysOfWeek[i]==true){x2=i;}
 }
 //1st checks for days of week
 if(x1<x2){return true;}
 else if(x1>x2){return false;}
 else{
  //if days of week are same it checks for departure time.
  if(l1->object->depTime < l2->object->depTime){return true;}
  else{return false;}
 }
}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  if(start>=end){return;}
  int i=start;
  int j=end;
  int pivotindex;
  //n is length of linkedlist.
  int n=end-start+1;
  listOfObjects<TrainInfoPerStation *> *curr=stnInfoList;
  listOfObjects<TrainInfoPerStation *> *tail=curr;
  for(int i=0;i<end;i++){
    tail=tail->next;
  }
  //ntail and tail is end node of linked list
  listOfObjects<TrainInfoPerStation *> *ntail=tail;
  listOfObjects<TrainInfoPerStation *> *head=curr;
  for(int i=0;i<start;i++){
    head=head->next;
  }
  //nhead and head are start node of linked list.
  listOfObjects<TrainInfoPerStation *> *nhead=head;
  listOfObjects<TrainInfoPerStation *>*pivot = returnpivot(head,start,end,n,K);

  while (true)
  {
    while(lessthan(nhead,pivot)&&(i<end)){
      i++;
      nhead=nhead->next;
      cout<<1;
    }
    while(!lessthan(ntail,pivot)&&(j>start)){
      j--;
      ntail=ntail->prev;
      cout<<2;
    }
    if(i<j){
      // Need to swap array[i] and array[j]
	// Note that array[i] may be the pivot.  However, array[j] can't be the pivot. Why?
	// In case array[i] is the pivot, we also remember where the pivot is being
	// moved.
      if(nhead == pivot){
        pivot=ntail;
      }
      TrainInfoPerStation* x=new TrainInfoPerStation(1,1,1,1);
      listOfObjects<TrainInfoPerStation *> *temp=new listOfObjects<TrainInfoPerStation *>(x);
      temp->object=ntail->object;
      ntail->object=nhead->object;
      nhead->object=temp->object;
    }
    else{
      // Now swap array[i] with the pivot
      TrainInfoPerStation* y=new TrainInfoPerStation(1,2,1,1);
      listOfObjects<TrainInfoPerStation *> *temp;
      temp=pivot;
      pivot=nhead;
      nhead=temp;
      pivotindex=i;
      break;
    } 
  }
  QuicksortSimple(stnInfoList,start,pivotindex-1);
  QuicksortSimple(stnInfoList,pivotindex+1,end);

  
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
  
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
