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

//Custom Less Than

void printDay(TrainInfoPerStation *x){
  for(int y=0; y<7;y++){
    if(x->daysOfWeek[y]){
      cout<<y<<endl;
    }
  }
}

bool isLessThan(TrainInfoPerStation * a , TrainInfoPerStation *b){
  for(int u=0 ; u<7 ; u++){
    if(a->daysOfWeek[u] && b->daysOfWeek[u]){
      //If both are same compare time
      if(a->depTime < b->depTime) return true;
      else if(a->depTime > b->depTime) return false;
      else {
        if(a->arrTime < b->arrTime) return true;
        else return false;
      }
    }
    else if (a->daysOfWeek[u]) return true; // If a is first
    else if (b->daysOfWeek[u]) return false; // If b is first
    else continue;
  }
  return false; //Should never reach here 
}
// To swap two values
void swap(TrainInfoPerStation *a, TrainInfoPerStation *b)
{
  TrainInfoPerStation c(1,1,1,1);
  c = *a;
  *a=*b;
  *b = c;
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  static int end=0;
  static int start=0;
  static listOfObjects<TrainInfoPerStation *> **array;
  //To store the pointer to the last object
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

    
    int n=0; 
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList; //temporary list
    //To count number of objects and store them
    while(true){ 
      n++;

      if(temp->next == NULL){
        break;
      }

      temp =temp->next;
    }
    end = n-1;
    
    
    array = new listOfObjects<TrainInfoPerStation *>* [(n-1)/K +1];
    temp = stnInfoList;
    n = 0;
    while(temp!=nullptr){
      if(n%K == 0){
        array[n/K] = temp;
      }
      n++;
      temp =temp->next;
    }


    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  // Put your code for the core of Quicksort here


  if(start==end) return ;

  TrainInfoPerStation *node; // The node for quicksort
  
  srand(time(0));
  int len=end-start;
  int nodeIndex = rand()%len + start ; //To randomly get node index
  int q = nodeIndex/4;
  int r = nodeIndex%4;
  listOfObjects<TrainInfoPerStation *> *ChosenNode;
  
  ChosenNode = array[q]; //Directly accessing the array element

  while(r--){ 
    ChosenNode = ChosenNode->next;
  } // Time taken is O(K)

  node = ChosenNode->object; //Setting the node to be the value at randomly chosen index
  
  node = stnInfoList->object;
  int i = start;
  int j = end;

  

  listOfObjects<TrainInfoPerStation*> *first;
  first = stnInfoList;
  listOfObjects<TrainInfoPerStation*> *last;
  last = stnInfoList;
  for(int u=0 ;u < j-i ; u++){
    last = last->next;
  }

  while(j>i){
    while(i<= end && isLessThan(first->object,node)){
      i++;
      first = first->next;
      }
    while(j>=start && !(isLessThan(last->object,node ))){
      j--;
      last = last->prev;
    }
    
    if(j>i) swap(first->object,last->object);
  }

  if(j==start-1){
    int tempstart = start;
    int tempend = end;
    start++;
    Quicksort(stnInfoList->next);
    start = tempstart;
    end = tempend;
  }
  else{
    int tempstart = start;
    int tempend = end;
    end = j;
    Quicksort(stnInfoList);
    start = tempstart;
    end = tempend;
    for(int r=0 ; r<i-start; r++){
      stnInfoList = stnInfoList->next;
    }
    tempstart = start;
    tempend = end;
    start = i;
    Quicksort(stnInfoList);
    end = tempend;
    start =tempstart;
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
  static listOfObjects<TrainInfoPerStation *> **array; // The array to store info
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
    int n=end+1;
    
    array = new listOfObjects<TrainInfoPerStation *>* [(n-1)/K +1]; // n/K space
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
    int s = 0;
    while(temp!=nullptr){
      if(s%K == 0){
        array[s/K] = temp; //Storing pointer to every kth element
      }
      s++;
      temp =temp->next;
    }

    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  if(start==end) return ;

  TrainInfoPerStation *node; // The node for quicksort
  
  srand(time(0));
  int len=end-start;
  int nodeIndex = rand()%len + start ; //To randomly get node index
  // Now we find its remainder and quotient on dividing by 4
  int q = nodeIndex/4;
  int r = nodeIndex%4; 
  
  listOfObjects<TrainInfoPerStation *> *ChosenNode; //This will point to the chosen node
  
  ChosenNode = array[q]; //Directly accessing the array element

  while(r--){ 
    ChosenNode = ChosenNode->next;
  } // Time taken is O(K)

  node = ChosenNode->object; //Setting the node to be the value at randomly chosen index
  

  int i = start;
  int j = end;

  

  listOfObjects<TrainInfoPerStation*> *first;
  first = stnInfoList;
  listOfObjects<TrainInfoPerStation*> *last;
  node = stnInfoList->object;
  last = stnInfoList;
  for(int u=0 ;u < j-i ; u++){
    last = last->next;
  }

  while(j>i){
    while(i<= end && isLessThan(first->object,node)){
      i++;
      first = first->next;
      }
    while(j>=start && !(isLessThan(last->object,node ))){
      j--;
      last = last->prev;
    }
    
    if(j>i) swap(first->object,last->object);
  }

  if(j==start-1){
    QuicksortSimple(stnInfoList->next , start+1 , end);
  }
  else{
    QuicksortSimple(stnInfoList,start,j);
    for(int r=0 ; r<i-start; r++){
      stnInfoList = stnInfoList->next;
    }
    QuicksortSimple(stnInfoList, i, end);
  }

  recursionLevel--;
  return;
}

#endif
