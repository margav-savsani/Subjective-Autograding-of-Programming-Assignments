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

#include<cstdlib>


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



// function to get the last node in the stnInfoList 
listOfObjects<TrainInfoPerStation *> *lastNode(listOfObjects<TrainInfoPerStation *> *root){ 
  while (root && root->next) 
    root = root->next; 
  return root; 
}

// to get a number that would be the basis of sorting based on day and time
int tocompare(TrainInfoPerStation* a){
  int day = 0;
  int time = 0;
  for(int i=0;i<7;i++){
    if(a->daysOfWeek[i] == 1){
      day = i+1;
      break;
    }
  }
  if(a->arrTime != -1) time = a->arrTime;
  int f = day*10000 + time;
  return f;
}

// this is the choose pivot function which chooses a random pivot
listOfObjects<TrainInfoPerStation *> choose_pivot(listOfObjects<TrainInfoPerStation *> **array, int sz, int K){
  srand(time(0));
  int num = rand()%sz ;
  int a = num%K;
  int index = num/K;
  if(a==0) {
    return *array[index];
  }
  else{
    listOfObjects<TrainInfoPerStation *> f = *array[index];
    for(int i=0;i<a;i++){
      if(f.next!=NULL)
        f = f.next->object;
    }
    return f;
  }
}

// partition function which has pivot as its last element
listOfObjects<TrainInfoPerStation *> * partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *h){
  if(h!=NULL){
    int x = tocompare(h->object); 
    listOfObjects<TrainInfoPerStation *> *i = l->prev;
    for (listOfObjects<TrainInfoPerStation *> *j = l; j != h; j = j->next){ 
      if (tocompare(j->object) <= x){
        i = (i == NULL)? l : i->next;  
        listOfObjects<TrainInfoPerStation*> *s= l;
        if(j != NULL || i != NULL){
          s->object = i->object;
          i->object = j->object;
          j->object = s->object;
        }
      } 
    } 
    i = (i == NULL)? l : i->next; 
    listOfObjects<TrainInfoPerStation*> *s = l; 
      cout<<h->object->journeyCode<<"  "<<i->object->journeyCode<<endl;
      s->object = i->object;
      i->object = h->object;
      h->object = s->object; 
      cout<<h->object->journeyCode<<"  "<<i->object->journeyCode<<endl;
    return i; 
  }
  else return l;
} 

// this is the partition function which has random pivot. We choose the pivot randomly using choose_pivot function and then swap the chosen pivot with the 
// last element of the station list and then call the partition function which sorts about the last element as pivot  
listOfObjects<TrainInfoPerStation *> * rand_partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *h, listOfObjects<TrainInfoPerStation *> **array, int sz, int K){
  listOfObjects<TrainInfoPerStation *> rand_pivot = choose_pivot(array, sz, K);
  listOfObjects<TrainInfoPerStation*> *s= l;
  if(s!=NULL){
    s->object = rand_pivot.object;
    if(h!=NULL){
      rand_pivot.object = h->object;
      h->object = s->object;
    }
  }
  return partition(l, h);
}

void quicksortsimple(listOfObjects<TrainInfoPerStation *> *head, listOfObjects<TrainInfoPerStation *> *tail , listOfObjects<TrainInfoPerStation *> **array, int sz, int K){
  if(head!=NULL){
    listOfObjects<TrainInfoPerStation *> *p = rand_partition(head, tail, array, sz, K);
    quicksortsimple(head, p->prev, array, sz, K); 
    quicksortsimple(p->next, tail, array, sz, K);
  }
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
  static listOfObjects<TrainInfoPerStation *> **array;
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    int size = (end+1)/K;
    array = new listOfObjects<TrainInfoPerStation *> *;
    int cnt=0;
    while(stnInfoList){
      if(cnt%K == 0){
        array[cnt]->object = stnInfoList->object;
      }
      stnInfoList = stnInfoList->next;
      cnt++;
    }
  }
  listOfObjects<TrainInfoPerStation *> *last = lastNode(stnInfoList);
  quicksortsimple(stnInfoList , last , array, end+1, K); 
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
