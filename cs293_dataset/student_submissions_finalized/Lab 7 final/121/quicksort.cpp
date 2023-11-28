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
#include<vector>
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
void myswap(listOfObjects<TrainInfoPerStation *> *o1,listOfObjects<TrainInfoPerStation *> *o2){
  if(o1==o2) return;
  TrainInfoPerStation* temp = o1->object;
  o1->object = o2->object;
  o2->object = temp;
  return;
}

bool isgt(TrainInfoPerStation *o1, TrainInfoPerStation *o2){
  //checks if o1 is greater than o2
  int day1, day2;
  for (int i=0; i<7; i++){
    if((o1->daysOfWeek[i]==true)){
      day1=i;
      break;
    }
  }
  for (int i=0; i<7; i++){
    if((o2->daysOfWeek[i]==true)){
      day2=i;
      break;
    }
  }
  if(day1>day2) return true;
  else if(day1<day2) return false;
  else{
    return o1->depTime > o2->depTime;
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

  //we store n/K milestones that is breakpoints in our linked list so that we can 
  //travel through linked list faster.
  static vector <listOfObjects<TrainInfoPerStation*>*> milestones;
  static int linkedListLen ;
  static int start , end;
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    //we also have to calculate start and end for this implementation, rest is almost 
    //same as QuicksortSimple.
    start=0;
    

    //we create and append milestones only in the initial call
    listOfObjects<TrainInfoPerStation*> * currptr = stnInfoList;
    milestones.clear();
    for(int i=0; true; i++){     //counter for so called 'index'
      if(currptr==nullptr) {    //if we reach end of linked list
        linkedListLen = i;
        break;    
      }
      if (i%K==0){      // to choose every kth element and push into milestones vector
        milestones.push_back(currptr);
      }
      currptr=currptr->next;
    }
    end = linkedListLen-1;
  }
  //updating start and end everytime : 

  // Put your code for the core of QuicksortSimple here
  if (start < end){
    // 1- Pivot selection in O(k) time 
    int ind = rand()%(end-start+1) + start; 
    listOfObjects<TrainInfoPerStation*> * pivot = milestones[ind/K];
    for (int i=0; i<(ind%K); i++){
      pivot = pivot->next;
    }
    //now pivot is ready
    
    //2- Partition of linked list
    //myswapping 'end' element of linked list with pivot 
     //finding end element of linked list
    // listOfObjects<TrainInfoPerStation*>* endElem = milestones[end/K];
    listOfObjects<TrainInfoPerStation*>* endElem = stnInfoList;
    for(int i=0; i<end; i++){
     endElem = endElem->next;
    }
    myswap(pivot, endElem);
    TrainInfoPerStation* pivotObject = endElem->object;
    listOfObjects<TrainInfoPerStation*>* iElem = milestones[(start)/K];  //to access ith element
                                                                            //of linked list
    for(int i=0; i<(start%K); i++){
      iElem = iElem->next;
    }
    listOfObjects<TrainInfoPerStation*>* jElem = milestones[(start)/K];  //to access jth element
                                                                            //of linked list
    for(int j=0; j<(start%K); j++){  
      jElem = jElem->next;
    }

    int i=start-1;
    for (int j=start; j<=(end-1); j++){
      if(! isgt(jElem->object, pivotObject)){
        i++;
        if (i != (start)) iElem=iElem->next;
        myswap(iElem,jElem);
      }
      jElem=jElem->next;
    }
    if (i!=(start-1)) iElem=iElem->next;
    myswap(iElem, endElem);
    
    //i+1 is index of pivot now
    //3- Recursive Call
    int end1 = end;
    int start1 = start;
    end=i;
    Quicksort(stnInfoList);
    start = i+2;
    end = end1;
    Quicksort(stnInfoList);
    start=start1;
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

  //we store n/K milestones that is breakpoints in our linked list so that we can 
  //travel through linked list faster.
  static vector <listOfObjects<TrainInfoPerStation*>*> milestones;
  static int linkedListLen ;
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    

    //we create and append milestones only in the initial call
    listOfObjects<TrainInfoPerStation*> * currptr = stnInfoList;
    milestones.clear();
    for(int i=0; true; i++){     //counter for so called 'index'
      if(currptr==nullptr) {    //if we reach end of linked list
        linkedListLen = i;
        break;    
      }
      if (i%K==0){      // to choose every kth element and push into milestones vector
        milestones.push_back(currptr);
      }
      currptr=currptr->next;
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  if (start < end){
    // 1- Pivot selection in O(k) time 
    int ind = rand()%(end-start+1) + start; 
    listOfObjects<TrainInfoPerStation*> * pivot = milestones[ind/K];
    for (int i=0; i<(ind%K); i++){
      pivot = pivot->next;
    }
    //now pivot is ready
    
    //2- Partition of linked list
    //myswapping 'end' element of linked list with pivot 
     //finding end element of linked list
    // listOfObjects<TrainInfoPerStation*>* endElem = milestones[end/K];
    listOfObjects<TrainInfoPerStation*>* endElem = stnInfoList;
    for(int i=0; i<end; i++){
     endElem = endElem->next;
    }
    myswap(pivot, endElem);
    TrainInfoPerStation* pivotObject = endElem->object;
    listOfObjects<TrainInfoPerStation*>* iElem = milestones[(start)/K];  //to access ith element
                                                                            //of linked list
    for(int i=0; i<(start%K); i++){
      iElem = iElem->next;
    }
    listOfObjects<TrainInfoPerStation*>* jElem = milestones[(start)/K];  //to access jth element
                                                                            //of linked list
    for(int j=0; j<(start%K); j++){  
      jElem = jElem->next;
    }

    int i=start-1;
    for (int j=start; j<=(end-1); j++){
      if(! isgt(jElem->object, pivotObject)){
        i++;
        if (i != (start)) iElem=iElem->next;
        myswap(iElem,jElem);
      }
      jElem=jElem->next;
    }
    if (i!=(start-1)) iElem=iElem->next;
    myswap(iElem, endElem);
    
    //i+1 is index of pivot now
    //3- Recursive Call
    QuicksortSimple(stnInfoList, start, i);
    QuicksortSimple(stnInfoList, i+2, end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
