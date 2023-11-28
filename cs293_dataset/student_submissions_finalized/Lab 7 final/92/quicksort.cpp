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
bool isLessthan(TrainInfoPerStation* a,TrainInfoPerStation* b){
  for(int i=0;i<7;i++){
    if(a->daysOfWeek[i]||b->daysOfWeek[i]){//if any of trains arrive on a day
      if(a->daysOfWeek[i] && !b->daysOfWeek[i]){return 1;}//if they both donot arrive on same day
      else{return 0;}
      if(a->daysOfWeek[i]&& b->daysOfWeek[i]&&(a->arrTime<=b->arrTime)){return 1;}//if both arrive on same day but a arrives early than b
      else{return 0;}
    }
  }
}
int Length(listOfObjects<TrainInfoPerStation *> *stnInfoList){//number of stations
  int n=0;//length value
  listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
  while(currNode!=NULL){//until the ode points to null pointer
    currNode=currNode->next;
    n=n+1;
  }
  return n;
}
listOfObjects<TrainInfoPerStation*>* get(listOfObjects<TrainInfoPerStation *> *stnInfoList,int l){//finding 
 listOfObjects<TrainInfoPerStation *> *Node = stnInfoList;
 while(l>0){//finding the lth station in the list
    Node=Node->next;//advancing to next station
    l=l-1;
  }
  return Node;//the station to be found
}
listOfObjects<TrainInfoPerStation*>**  Preprocess(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  listOfObjects<TrainInfoPerStation*>** arr;
  int K=4,i=0;j=0;int N=Length(stnInfoList);
 listOfObjects <TrainInfoPerStation *> *currNode = stnInfoList;
  arr = new listOfObjects<TrainInfoPerStation*>* [(N-1/K)+1];
  while(currNode!=NULL){//until station points to null pointer
    if(j%K==0){arr[i]=(currNode);i++;}
    j++;currNode=currNode->next;}
  return arr;
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
listOfObjects<TrainInfoPerStation*>* choosePivot( int start, int end,listOfObjects<TrainInfoPerStation*>** arr){
    int N = start + rand()%(end-start+1);//pivot index
    listOfObjects<TrainInfoPerStation*>* curr;//station list
    int rem = N%4;
    curr = arr[N/4];
    while(rem != 0){//until extra space is zero
      curr = curr->next;rem=rem-1;}//node chages to next node
    return curr;//returning required station

}
int Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,int start, int end,listOfObjects<TrainInfoPerStation*>** arr)
{    listOfObjects<TrainInfoPerStation*> *pivot;// Call appropriate pivot function based on choice
    pivot = choosePivot(start,end,arr);//choosing the pivot index
    int i=start,j=end;//starting and ending of the array
    listOfObjects<TrainInfoPerStation*> *ta = get(stnInfoList,end);//tail of the station info list
    listOfObjects<TrainInfoPerStation *> *he = get(stnInfoList,start);//head of the station info list
listOfObjects<TrainInfoPerStation*> *tempo=new listOfObjects<TrainInfoPerStation*> (pivot->object);
    while(1){
    // compare and swap the elements
        while(!(isLessthan(tempo->object,he->object))){he=he->next;i++;}//swapping according to the algo
         while(!(isLessthan(ta->object,tempo->object))){ta=ta->prev;j--;}//swapping according to the algo
        if(i<j) {//until the elements left of pivot are less than pivot and right of pivot are greater than pivot.
            TrainInfoPerStation* t;
            t=he->object;he->object=ta->object;ta->object=t;}
        else return j;}
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
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

  
  static listOfObjects<TrainInfoPerStation*>** arr;
  if (recursionLevel == 0) { arr = Preprocess(stnInfoList);//preprocessing step.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    }

  
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function

  if (start<end){//precondition
if(Partition(stnInfoList,start,end,arr)<end){
    QuicksortSimple(stnInfoList,start,Partition(stnInfoList,start,end,arr));QuicksortSimple(stnInfoList,Partition(stnInfoList,start,end,arr)+1,end);}//quick sort algorithm if pivot is within bounds
else{QuicksortSimple(stnInfoList,start,Partition(stnInfoList,start,end,arr)-1);QuicksortSimple(stnInfoList,Partition(stnInfoList,start,end,arr),end);}//if pivot is not within bounds
}
  recursionLevel--;return;//recursively doing it until it is complete
}

#endif
