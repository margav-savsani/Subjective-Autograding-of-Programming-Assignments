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
#include <cstdlib>
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


//Swap function that will swap the data of the two nodes passed as arguments
void swap(listOfObjects<TrainInfoPerStation *> * a, listOfObjects<TrainInfoPerStation *> *b){
  if(a==b || a==nullptr || b==nullptr){
    return;
  }
  TrainInfoPerStation *temp = new TrainInfoPerStation(a->object->journeyCode, a->object->stopSeq, a->object->arrTime, a->object->depTime);
    for(int i=0; i<7; i++){
      temp->daysOfWeek[i]=a->object->daysOfWeek[i];
      a->object->daysOfWeek[i]=b->object->daysOfWeek[i];
      b->object->daysOfWeek[i]=temp->daysOfWeek[i];
    }

    a->object->arrTime = b->object->arrTime;
    b->object->arrTime = temp->arrTime;

    a->object->depTime = b->object->depTime;
    b->object->depTime = temp->depTime;

    a->object->journeyCode = b->object->journeyCode;
    b->object->journeyCode = temp->journeyCode;

    a->object->stopSeq = b->object->stopSeq;
    b->object->stopSeq = temp->stopSeq;
}

//Partition function
//places the pivot at its correct position such that all elements smaller than pivot comes before pivot
//and all elemnets larger than pivot comes after pivot
//smaller and bigger are according to the days and arrival time
int Planner::partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation *> *pivot1){
  listOfObjects<TrainInfoPerStation *> *l = stnInfoList; //element corresponding to the start
  for(int i = 0; i<start; i++)
  {
    l = l->next;
  }
  listOfObjects<TrainInfoPerStation *> *h = stnInfoList; //element corresponding to the end
  for(int i = 0; i<end; i++)
  {
    h = h->next;
  }
  listOfObjects<TrainInfoPerStation *> *i = l->prev; //element to keep track of pivot
  swap(pivot1, h); //swap pivot and last element and sort according to the pivot
  listOfObjects<TrainInfoPerStation *> *pivot = h;
  for(listOfObjects<TrainInfoPerStation *> *j =l; j!=h; j=j->next){
    int day_j=0;
    for(; day_j<7; day_j++){
      if(j->object->daysOfWeek[day_j]){
        break;
      }
    }

    int day_pivot=0;
    for(; day_pivot<7; day_pivot++){
      if(pivot->object->daysOfWeek[day_pivot]){
        break;
      }
    }

    if(day_j<day_pivot){ //comparing according to day
      i = (i == NULL)? l : i->next;
      swap(i,j);
    }else if(day_j==day_pivot){ //if day is same comparing acccording to arrival time
        if(j->object->arrTime <= h->object->arrTime){
          i = (i == NULL)? l : i->next;
          swap(i,j);
        }
    }
  }
  i = (i == NULL)? l : i->next;
  swap(i,h);
  int k = 0; //index of pivot in list
  listOfObjects<TrainInfoPerStation *> *p = stnInfoList;
  while(p != i)
  {
    k++;
    p = p->next;
  }
  return k;
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
// A few static variable declarations
  static int K = 2; // Parameter to be experimented with
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
  static int start = 0;
  static int end = 0;
  static int p = 0;
  static listOfObjects<TrainInfoPerStation *> *node = stnInfoList;
  static listOfObjects<TrainInfoPerStation *>* pivot = stnInfoList;

  static listOfObjects<TrainInfoPerStation *>** arr;
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    while(node->next!=nullptr){
      node=node->next;
      end++;
    }
    int n = (end+1)/K;
    arr = new listOfObjects<TrainInfoPerStation *>* [n+1];
  }
    end = 0;
    node = stnInfoList;
    while(node->next != nullptr)
    {
      node = node->next;
      end++;
    }
    if(start<end){
      int z = end - start +1;
      for(int i = 0; i<start; i++)
      {
        pivot = pivot->next;
      }
      int w;
      if(z%K==0){
        w=z/K;
      }else{
        w=z/K+1;
      }
      for(int y=0; y<w; y++){
        if(y==0){
          arr[0]=pivot;
        }else{
          for(int q=0; q<K; q++){
            pivot=pivot->next;
          }
          arr[y]=pivot;
        }
      }

      srand(time(0));
      int rand_val=rand();
      rand_val=rand_val%z;
      pivot=arr[rand_val/K];
      for(int y=0; y<rand_val%K; y++){
        pivot=pivot->next;
      }
      p = partition(stnInfoList,start,end,pivot);
      node = stnInfoList;
      for(int i=0; i<=p; i++)
      {
        node = node->next;
      }
      if(node->prev != nullptr)
      {
        node->prev->next = nullptr;
      }
      Quicksort(stnInfoList);
      node->prev->next = node;
      start = p;
      Quicksort(node->next);
    }
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;

}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // cout<<"start = "<<start<<" end = "<<end<<endl<<endl;
  // A few static variable declarations
  static int K = 2; // Parameter to be experimented with
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
  static listOfObjects<TrainInfoPerStation *>** arr;
  if (recursionLevel == 0) {

    int n = (end+1)/K; //number of elements in the list

    //forming a new array that will store the elements of the list stnInfoList for which i%K==0
    //where i is the index of the element in the array so that we can choose the pivot from
    //this array in O(K) time and the space that this array will take is O(N/K)
    arr = new listOfObjects<TrainInfoPerStation *>* [n+1];

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  // Put your code for the core of QuicksortSimple here
  if(start<end){
    listOfObjects<TrainInfoPerStation *>* pivot = stnInfoList;
    int z = end - start +1;   //number of elements between start and end
    for(int i = 0; i<start; i++)
    {
      pivot = pivot->next;
    }
    //allocating the elements to the array
    int w;
    if(z%K==0){
      w=z/K;
    }else{
      w=z/K+1;
    }
    for(int y=0; y<w; y++){
      if(y==0){
        arr[0]=pivot;
      }else{
        for(int q=0; q<K; q++){
          pivot=pivot->next;
        }
        arr[y]=pivot;
      }
    }
    //finding the random pivot from the array
    //first finding a random number between 0 and z-1 both inclusive
    //then go to the rand_val/K index of the arr and then choose the pivot from this index
    srand(time(0));
    int rand_val=rand();
    rand_val=rand_val%z;
    pivot=arr[rand_val/K];
    for(int y=0; y<rand_val%K; y++){
      pivot=pivot->next;
    }
    //calling partition function
    int p = partition(stnInfoList, start, end, pivot);
    //recursive Quicksort
    QuicksortSimple(stnInfoList, start, p-1);
    QuicksortSimple(stnInfoList, p+1, end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
