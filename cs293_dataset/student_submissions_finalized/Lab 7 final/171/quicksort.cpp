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
   // Parameter to be experimented with
  
  int len=0;
  
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
   listOfObjects<TrainInfoPerStation *> *t = stnInfoList;
    while(t!=NULL){
      len++;
      t=t->next;
    }
  
  QuicksortSimple(stnInfoList,0,len-1);
  
  // Put your code for the core of Quicksort here

  
  return;
}

int day(TrainInfoPerStation* t){
    int d=0;
    for(int i=0;i<7;i++){
      if(t->daysOfWeek[i]){
        d=i;
        break;
      }
    }
    return d;
}

listOfObjects<TrainInfoPerStation *> *Pivot(listOfObjects<TrainInfoPerStation *>* *arr,int len,int K){
  int p = rand()%len ;
  int q = p/K;
  int r = p%K;
  //cout << "p" << p << endl;
  
  listOfObjects<TrainInfoPerStation *> *pivot;
  pivot = arr[q];
  
  for(int i=0;i<r;i++){
    pivot = pivot->next;
  }
  return pivot;
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

  static listOfObjects<TrainInfoPerStation *>* *arr ;
  static int len,n;
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
  //cout << "start" << endl;
  
  if (recursionLevel == 0) {
      //cout << "recursionLevel";
      n=end+1;
      len = n;
      int a=0;
      if(n%K==0)
        a=n/K;
      else
        a=(n/K)+1;

      arr = (listOfObjects<TrainInfoPerStation *>* *) calloc(a,sizeof(listOfObjects<TrainInfoPerStation *>* *));
      listOfObjects<TrainInfoPerStation *> *s = stnInfoList;
      for(int i=0;i<a;i++){
        arr[i] = s;
        if(i==a-1)
          break;
        for(int j=0;j<K-1;j++){
          s=s->next;
        }
      }

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

 
  listOfObjects<TrainInfoPerStation *> *pivot = Pivot(arr,len,K);
  
  listOfObjects<TrainInfoPerStation *> *head = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *tail = stnInfoList;
  
  for(int i=0;i<start;i++){
    head=head->next;
  }
  for(int i=0;i<end;i++){
    tail=tail->next;
  }
  
  int s=start;
  int e=end;
  int part;
  while(1){
        
        while((day(pivot->object)<day(tail->object)) || ((day(pivot->object)==day(tail->object)) && (pivot->object->depTime<tail->object->depTime)) ){
            e--;
            tail=tail->prev;
            if(e==0)
              break;
        }
        while((day(head->object)<day(pivot->object)) || ((day(head->object)==day(pivot->object)) && (head->object->depTime<pivot->object->depTime)) ){
            s++;
            head=head->next;
            if(head->next==nullptr)
              break;
        }
        
        
        if(s<e){
           TrainInfoPerStation *x = head->object;
           head->object=tail->object;
           tail->object=x; 

           if((day(head->object)==day(tail->object)) && (head->object->depTime==tail->object->depTime)){
            if(head->next!=NULL){
              head=head->next;
              s++;
            }
            if(tail->prev!=NULL){
              tail=tail->prev;
              e--;
            }
           }
        }
        else if(e==end){
          part=e-1;
          break;
        } 
        else {
          part=e;
          break;
        }
  }
  //cout << "end" << len << endl;
  QuicksortSimple(stnInfoList,start,part);
  
  QuicksortSimple(stnInfoList,part+1,end);
  
  
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  //cout << recursionLevel << endl;
  return;
}

#endif
