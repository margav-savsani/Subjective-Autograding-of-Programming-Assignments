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

void swapobj(listOfObjects<TrainInfoPerStation *> *A , listOfObjects<TrainInfoPerStation *> *B){
  // function for swapping objects

  TrainInfoPerStation* C;
  C = A->object;
  A->object = B->object;
  B->object = C;
}

bool compfxn(listOfObjects<TrainInfoPerStation *> *A , listOfObjects<TrainInfoPerStation *> *B){
  // int d1 ,d2 ,a , b;
  // for ( int i=0 ;i<7;i++){
  //   if(A->object->daysOfWeek[i]){
  //     d1 = i ;
  //   }
  //   if(B->object->daysOfWeek[i]){
  //     d2 = i;
  //   }
    
  // }
  // a = (d1*1000) + A->object->depTime;
  // b = (d2*1000) + B->object->depTime;
  // return a<=b;

   for(int i=0;i<7;i++){
    if((A->object->daysOfWeek[i]) && !(B->object->daysOfWeek[i])){
      return true;
    }
    if(!(A->object->daysOfWeek[i]) && (B->object->daysOfWeek[i])){
      return false;
    }
    if((A->object->daysOfWeek[i]) && (B->object->daysOfWeek[i])){
       if(A->object->depTime==A->object->depTime){
        if(A->object->arrTime<B->object->arrTime) return true;
        else return false;
      }
      else if(A->object->depTime < B->object->depTime) return true;
      else return false;
    }
  }
  return true;
}

// void pivot_choose(listOfObjects<TrainInfoPerStation *> *A , int s , int e , int K , static listOfObjects<TrainInfoPerStation*> *Array ){

//     int length = e - s  + 1;
//     srand(time(NULL));
//     int index = (rand()%(length)) + s;
//     int t = index/K;
//     int p = index%K;

//         for(int k =0 ; k< t;k++){
//           Array = Array->next;
//         } 
//         A=Array;
//         for(int i=0;i<p;i++){    
//           A=A->next;
//           if(A==nullptr)break;
//         }
        
//         return  ;

// }


int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList , int s , int e , listOfObjects<TrainInfoPerStation*> *pivot){

  int i = s  ;
  int j = e ;
  while(true){
  listOfObjects<TrainInfoPerStation *> *Listj = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *Listi = stnInfoList;
  for(int k =0 ; k< j;k++){
    Listj = Listj->next;
  } 
  for(int k =0 ; k< i;k++){
    Listi = Listi->next;
  } 

  while(compfxn(pivot,Listj)){      
    j = j-1;            
    Listj = Listj->prev;
    if(Listj==nullptr)break;
  }
  while(compfxn(Listi,pivot)){
    i = i+1;
    Listi = Listi->next;
    if(Listi==nullptr)break;      
  }
  if(i<j){
    // TrainInfoPerStation *node = Listi->object;
    // Listi->object = Listj->object;
    // Listj->object = node;
    swapobj(Listi,Listj);
  }
  else return j;
  }


}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in


  listOfObjects<TrainInfoPerStation*> *l1=stnInfoList;
  static int length=1;
  while(l1->next!=nullptr){
    l1=l1->next;
    length++;
  }  
  


  // storing into Array

  static listOfObjects<TrainInfoPerStation*> **Array= new listOfObjects<TrainInfoPerStation*> *[((length)/K)+1];
     


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
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
     listOfObjects<TrainInfoPerStation*>*l2=stnInfoList;
      int i=0;int j=0;
      while(l2!=NULL){
        if(i%K==0){ // taking elements of indexs 0,4,8,....................
          Array[j]=l2; //appending to list
          j++;
        }
        i=(i+1)%K;
        l2=l2->next;
      }  

  }

  if(start < end){
        
        int index = start;
        int t=index/K;
        int p=index%K;
        listOfObjects<TrainInfoPerStation*>*pivot=stnInfoList;
        pivot=Array[t];
        for(int i=0;i<p;i++){    
          pivot=pivot->next;
          if(pivot==nullptr)break;
        }

    int q = partition( stnInfoList, start,end,pivot);
        QuicksortSimple(stnInfoList , start,q-1);
        QuicksortSimple(stnInfoList,(q+1),end);
    }
  
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
