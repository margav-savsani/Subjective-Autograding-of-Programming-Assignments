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
#include <cstdlib>
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
bool less_than(listOfObjects<TrainInfoPerStation *> *a1,listOfObjects<TrainInfoPerStation *> *a2){
  int day1=0,day2=0;
  for(int i=0;i<7;i++){
    if(a1->object->daysOfWeek[i]){
      day1=i;
      break;
    }

  }
  for(int i=0;i<7;i++){
    if(a2->object->daysOfWeek[i]){
      day2=i;
      break;
    }
    
  }
  
  if(day1<day2) return true;
  if(day1==day2 && a1->object->depTime < a2->object->depTime) return true;
  else return false;
}

int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation *> *pivot,int start,int finish){
  listOfObjects<TrainInfoPerStation *> * head=stnInfoList,*tail,*temp;
  
  while(head!=nullptr){
    tail=head;
    head=head->next;
  }
  head=stnInfoList;
  temp=tail;
    int i = start -1;
    int j = finish + 1;
    
    while (true) {
      do {
	j = j - 1;
  if(j!=finish){
    temp=temp->prev;
  }
      } while (less_than( pivot  , temp ) && (j > start));

      do {
	i = i + 1;
  if(i!=start){
    head=head->next;
  }
      } while (less_than(head , pivot) && (i < finish));


      if (i < j) {

        TrainInfoPerStation * temp2 = temp->object;
        temp->object = head->object;
        head->object = temp2;
        if(!(less_than(head,pivot))&& !(less_than(pivot,head))){
         
          pivot=head;
        }
        if(!(less_than(temp,pivot))&& !(less_than(pivot,temp))){
         
          pivot=tail;
        }
      }
  
     
  else{
    TrainInfoPerStation * temp2 =head->object;
    head->object=pivot->object;
    pivot->object=temp2;
    return i;
  }
  
}
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
  if(start==end || start > end) return;
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
  if( end ==start+1){
    if( less_than(stnInfoList,stnInfoList->next)) return;
    else{
      TrainInfoPerStation * temp=stnInfoList->object;
      stnInfoList->object=stnInfoList->next->object;
      stnInfoList->next->object=temp;
    }
  }
  static listOfObjects<TrainInfoPerStation *> **arr;
  static int n;
  if (recursionLevel == 0) {
    n=(end-start+1);
    arr=new listOfObjects<TrainInfoPerStation *> *[n/K];
    listOfObjects<TrainInfoPerStation *> * curstn=stnInfoList;
    int j=0;
    for(int i=0;i<n ;i++){
      if(i%K==0){
        arr[j]=curstn;
        j++;
      }
      curstn=curstn->next;
    }

  }
  listOfObjects<TrainInfoPerStation *> * pivot;
  //pivot chooser starts
  int start1=start,finish=end;
  start1= start1+(finish-start1)*(rand()/RAND_MAX);
  finish=start1%K;
  start1=start1/K;
  listOfObjects<TrainInfoPerStation *> * temp=arr[start1];
  while(finish>0 && temp!=nullptr ){
    temp=temp->next;
    finish--;
  }
  pivot=temp;
  int day1;
    for(int i=0;i<7;i++){
    if(pivot->object->daysOfWeek[i]){
      day1=i;
      break;
    }

  }
  //pivot chooser ends
  
  TrainInfoPerStation *x=new TrainInfoPerStation(2,1,pivot->object->arrTime,pivot->object->depTime);
  x->setDayOfWeek(day1);
  listOfObjects<TrainInfoPerStation *> *y=new listOfObjects<TrainInfoPerStation *> (x);
  int j=partition(stnInfoList,y,start,end);

  listOfObjects<TrainInfoPerStation *> * curstn=stnInfoList;
  j=0;
  for(int i=0;i<n ;i++){
      if(i%K==0){
        arr[j]=curstn;
        j++;
      }
      curstn=curstn->next;
    }
  if (start < j) {
    QuicksortSimple(stnInfoList,start,j-1);
    if (end > j){
      QuicksortSimple(stnInfoList,j+1,end);
    }
  }
  else if(j!=end && start==j){

    QuicksortSimple(stnInfoList,j+1,end);
  }

  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  
  return;
}

#endif
