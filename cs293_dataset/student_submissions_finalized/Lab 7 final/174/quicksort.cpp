#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP
#include <cstdlib>
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


//This function swaps the objects of 2 listOfObjects<TrainInfoPerStation *>* a and b

void swap(listOfObjects<TrainInfoPerStation *>*a, listOfObjects<TrainInfoPerStation *>*b){
  TrainInfoPerStation * t;
  t=a->object;
  a->object=b->object;
  b->object=t;
  return;
}

//This function finds the last element of the list

listOfObjects<TrainInfoPerStation *>* findlast(listOfObjects<TrainInfoPerStation *>* a){
  while(a!=NULL && a->next!=NULL){
    a=a->next;
  }
  return a;
}

//This function calculates the pivot element using rand() function, swaps the tail with that element, and returns the new tail

listOfObjects<TrainInfoPerStation *>* pivot(listOfObjects<TrainInfoPerStation *>** A, listOfObjects<TrainInfoPerStation *>* t ,int k, int start, int end){
  int a=((rand()%(end-start+1))+start);
  listOfObjects<TrainInfoPerStation *>* q;  //q is pivot element
  int p=a%k;   //remainder
  int x=a/k;   //quotient
  q=A[x];
  for(int i=0; i<p; i++){
    q=q->next;
  }
  swap(q,t);
  return t;
}

//Partition function takes in a list, for pivot element it calculates the approprite position and returns that position

listOfObjects<TrainInfoPerStation *>* partition(listOfObjects<TrainInfoPerStation *>* h, listOfObjects<TrainInfoPerStation *>* t, listOfObjects<TrainInfoPerStation *>** A,int n, int k){
  listOfObjects<TrainInfoPerStation *> *p;
  int s;
  int e;
  int al=0;
  listOfObjects<TrainInfoPerStation *> *r;
  r=A[0];
  while(r!=NULL){
    if(r==h){
      s=al;
    }
    if(r==t){
      e=al;
      break;
    }
    r=r->next;
    al=al+1;
  }
  p=pivot(A,t,k,s,e);
  listOfObjects<TrainInfoPerStation *> *i, *x; //x is for traversal
  i=x=h;
  while(x!=t){
    for(int m=0; m<7; m++){                   //running the loop for days of week, m is the day no.
      if(x->object->daysOfWeek[m]==true && p->object->daysOfWeek[m]==false){  //lessthan case
        swap(i,x);
        i=i->next;
        break;
      }
      else if(x->object->daysOfWeek[m]==true && p->object->daysOfWeek[m]==true){ 
        if(x->object->depTime <= p->object->depTime){     //lessthan case
          swap(i,x);
          i=i->next;
          break;
        }
        else{                                             //greaterthan case
          break;
        }
      }
      else if(x->object->daysOfWeek[m]==false && p->object->daysOfWeek[m]==true){ //greaterthan case
        break;
      }
      else{                                             //cannot decide on this day, so going to next day
        continue;
      }
    }
    x=x->next;
  }
  swap(i,t);                                          //swapping i and t
  return i;
}

void quick(listOfObjects<TrainInfoPerStation *>* h, listOfObjects<TrainInfoPerStation *>* t,listOfObjects<TrainInfoPerStation *>** A, int n, int k){
  if(t!=NULL && t!=h && h!=t->next){
    listOfObjects<TrainInfoPerStation *>*p;
    p=partition(h,t,A,n,k);
    quick(h,p->prev,A,n,k);
    quick(p->next,t,A,n,k);
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
  static int K=4;
  int n=0;           //n is no. of elements in list
  listOfObjects<TrainInfoPerStation *> *a;
  a=stnInfoList;
  if(a==NULL){
    return;
  }
  while(a!=NULL && a->next!=NULL){
    n=n+1;
    a=a->next;
  }
  n=n+1;
  int p;   //p is size of array
  if(n%K==0){  
    p=n/K;
  }
  else{
    p=((n/K)+1);
  }

  a=stnInfoList;

  // A few static variable declarations
  // static int K = 4; // Parameter to be experimented with
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
  
  listOfObjects<TrainInfoPerStation *>** A;  //array of listOfObjects<TrainInfoPerStation *>*
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    A=new listOfObjects<TrainInfoPerStation *>*[p];
    for(int i=0; i<n; i++){
      if(i%K==0){
        A[i/K]=a;
      }
      a=a->next;
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  quick(stnInfoList,findlast(stnInfoList),A,n,K);
  // Decrement recursion level before leaving the function
  recursionLevel--;

  delete [] A; //deleting array
  return;
}

#endif
