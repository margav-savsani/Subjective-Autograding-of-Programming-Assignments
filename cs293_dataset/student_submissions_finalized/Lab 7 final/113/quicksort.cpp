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

#include <cassert>

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

//defining shorthand for some large names
typedef listOfObjects<TrainInfoPerStation *> Node;
typedef TrainInfoPerStation* Data;

// function to compare two train details (based on time)
bool lesss(listOfObjects<TrainInfoPerStation *> *A, listOfObjects<TrainInfoPerStation *> *B){
  for (int i=0; i<7; i++){
    //considering different cases
    if (A->object->daysOfWeek[i] && !B->object->daysOfWeek[i]) return true;
    else if (!A->object->daysOfWeek[i] && B->object->daysOfWeek[i]) return false;
    else if (A->object->daysOfWeek[i]){
      if (A->object->depTime <= B->object->depTime) return true;
      else return false;
    }
  }
  return false;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int size=0;  //size of current linked list
  static Node **dots=NULL;  //array to keep track of the n/K pointers
  static Node *end=NULL;  //end of the array
  static int starting=0;  //shift of the starting pointer i.e. basically the position of starting node in list
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
    Node *t=stnInfoList;
    size=1;

    //base case
    if (t == NULL){
        size = 0;
        return;
    }
    //first loop to find size and initializing static variables
    while (t->next != NULL){
        t = t->next;
        size++;
    }
    end = t;
    
    //initializing the array of pointers of nodes which are 0 mod K
    // which is in space n/K
    dots = new Node *[int(size/K)];
    t = stnInfoList;
    int j=0;
    for (int i=0; i<size; i++){
      if (i%K == 0){
        dots[j] = t;
        j++;
      }
      t = t->next;
    }

    
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  // shorthands for starting and ending elements of current list
  Node *h = end; // h means higher
  Node *l = stnInfoList;  // l means lower

  // if the start and end are equal or start is next of end or end is null then nothing to do
  if (h != NULL && l != h && l != h->next) 
  {         

      // choosing a random number and locating it using dots static variable
      int random = starting + (rand()%size);
      int q = random/K;      
      int r = random - q*K;
      Node *x = dots[q];

      //loop of order K at most for getting the pivot
      for (int i=0;i<r;i++){
        x = x->next;
      }

      // putting the pivot at the end of the linked list
      Data temp=x->object;
      x->object = h->object;
      h->object = temp;
      x=h;  // x is the pivot
      
      //normal quicksort algorithm but with pointer objects
      Node *i = l->prev; 
      int count=0;

      // looping all the elements and swapping them as needed
      for (Node *j = l; j != h; j = j->next) { 
          
          //condition for swapping is when the element is smaller than pivot
          if (lesss(j,x)) { 
              i = (i == NULL)? l : i->next; 
              count++;

              //swapping
              Data tem=i->object;
              i->object = j->object;
              j->object = tem;
          } 
      } 

      //last swap where the pivot which was stored at end of array goes back to its actual position
      i = (i == NULL)? l : i->next; 
      Data tem=i->object;
      i->object = h->object;
      h->object = tem;
      Node *p = i;
      // p is the pointer to the final position of pivot

      // recursive calls but first updating the static members to appropriate values and then changing them back to where they were
      end = p->prev;
      int act_size=size;
      int act_starting = starting;
      size = count;
      Quicksort(l); 
      end = h;
      size = act_size - count -1;
      starting = starting+count+1;
      Quicksort(p->next); 
      starting = act_starting;
      size = act_size;
  } 

// restoring static variables at the end of execution
if (recursionLevel==0){
  delete[] dots;
    end = NULL;
    dots = NULL;
    size = 0;
    starting = 0;
  }

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
  static Node **dots=NULL;  //array to keep track of the n/K pointers
  static Node *last=NULL;  //last of the array
  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will last up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  int size = end-start+1;

  if (recursionLevel == 0) {
    Node *t=stnInfoList;
    size=1;

    //base case
    if (t == NULL){
        size = 0;
        return;
    }
    //first loop to find size and initializing static variables
    while (t->next != NULL){
        t = t->next;
        size++;
    }
    last = t;
    
    //initializing the array of pointers of nodes which are 0 mod K
    // which is in space n/K
    dots = new Node *[int(size/K)];
    t = stnInfoList;
    int j=0;
    for (int i=0; i<size; i++){
      if (i%K == 0){
        dots[j] = t;
        j++;
      }
      t = t->next;
    }

    
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  // shorthands for starting and lasting elements of current list
  Node *h = last; // h means higher
  Node *l = stnInfoList;  // l means lower

  // if the start and last are equal or start is next of last or last is null then nothing to do
  if (h != NULL && l != h && l != h->next) 
  {         

      // choosing a random number and locating it using dots static variable
      int random = start + (rand()%size);
      int q = random/K;      
      int r = random - q*K;
      Node *x = dots[q];

      //loop of order K at most for getting the pivot
      for (int i=0;i<r;i++){
        x = x->next;
      }

      // putting the pivot at the last of the linked list
      Data temp=x->object;
      x->object = h->object;
      h->object = temp;
      x=h;  // x is the pivot
      
      //normal quicksort algorithm but with pointer objects
      Node *i = l->prev; 
      int count=start-1;

      // looping all the elements and swapping them as needed
      for (Node *j = l; j != h; j = j->next) { 
          
          //condition for swapping is when the element is smaller than pivot
          if (lesss(j,x)) { 
              i = (i == NULL)? l : i->next; 
              count++;

              //swapping
              Data tem=i->object;
              i->object = j->object;
              j->object = tem;
          } 
      } 

      //last swap where the pivot which was stored at last of array goes back to its actual position
      i = (i == NULL)? l : i->next; 
      Data tem=i->object;
      i->object = h->object;
      h->object = tem;
      Node *p = i;
      // p is the pointer to the final position of pivot

      // recursive calls but first updating the static members to appropriate values and then changing them back to where they were
      last = p->prev;
      QuicksortSimple(l, start, count); 
      last = h;
      QuicksortSimple(p->next, count+2, end); 
  } 

// restoring static variables at the last of execution
if (recursionLevel==0){
  delete[] dots;
    dots = NULL;
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
