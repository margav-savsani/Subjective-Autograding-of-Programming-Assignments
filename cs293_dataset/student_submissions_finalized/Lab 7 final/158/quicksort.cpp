#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#include<cmath>

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

using namespace std;

void Swap1(listOfObjects<TrainInfoPerStation*>* In1,listOfObjects<TrainInfoPerStation*>* In2){
  
  
  TrainInfoPerStation* temp = In1->object;
  In1->object = In2->object;
  In2->object = temp;

}

bool operator<(TrainInfoPerStation t1, TrainInfoPerStation t2){
  int t1_day=0, t2_day=0;
  for(t1_day=0;t1_day<7;t1_day++){
    if(t1.daysOfWeek[t1_day]) break;
  }
  for(t2_day=0;t2_day<7;t2_day++){
    if(t2.daysOfWeek[t2_day]) break;
  }
  if(t1_day<t2_day) return true;
  else if(t1_day==t2_day){
    if(t1.arrTime<t2.arrTime) return true;
    else if(t1.arrTime==t2.arrTime) return t1.depTime<t2.depTime;
    else return false;
  }
  else return false;
}

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

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
                                  
  static int numOfElements;
  static  listOfObjects<TrainInfoPerStation*>* * PointerArr = nullptr; //  This array grows to contain K elements.
  // Increment recursion level on entering the function 
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  if (K < 0) {
    cerr << "Invalid parameter k" << endl;
    exit(-1);
  }
  else if (K == 0) {
    recursionLevel--;
    return;
  }
  
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  if(start>=end){ recursionLevel--; return;}
  if (recursionLevel == 0) {

    //Count number of elements in object.
    numOfElements = 0;
    listOfObjects<TrainInfoPerStation*>* curr = stnInfoList; 
    
    while(curr!=nullptr){
     
      numOfElements+=1;
      curr = curr->next;
    }
    
    if(numOfElements==0)return;
    PointerArr = new listOfObjects<TrainInfoPerStation*>*[numOfElements/K];
    // By now, we have number of elements in the List.*/
    
    
    // Choose n/K pointers from the list.
    curr = stnInfoList;
    curr = curr->next;
    int count = 1;
    while(curr!=nullptr){
      if(count % K==0) {
        PointerArr[(count/K)-1] = curr;
         
      }
        count++;
      curr=curr->next;
    }

   
    
  }

    /********************PIVOT CHOOSER**********************************/
    int  pivot_index = rand()%(end-start+1);
    cout<<start+pivot_index<<" PIVOT IND"<<endl;
    cout<< pivot_index<<" at recLev"<< recursionLevel<< endl;
    listOfObjects<TrainInfoPerStation*>* pivot;
    if(pivot_index<K)pivot = stnInfoList;
    else pivot = PointerArr[((start + pivot_index)/K) - 1];
    
    int count = 0;
    while(count!=pivot_index%K){ // AT MAX THIS WILL DO K-1 STEPS.
      pivot = pivot->next;
      count++;
    }
    
    
    

    /**************NEW PARTITITON******************/
    //Get end element of current list scope.
    listOfObjects<TrainInfoPerStation*>*endptr;
    if(end<K)endptr = stnInfoList;
    else endptr = PointerArr[end/K - 1];
    count=0;
    while(count!=end%K){
      count++;
      endptr=endptr->next;
    }
    cout<< endptr->object->arrTime<<endl;

    //Get starting element
    listOfObjects<TrainInfoPerStation*>*startptr, *j_ptr, *i_ptr;
    if(start<K)startptr = stnInfoList;
    else startptr = PointerArr[start/K - 1];
    count=0;
    while(count!=start%K){
      count++;
      startptr=startptr->next;
    }
    ;
    Swap1(endptr, pivot);
    pivot = endptr;

    int i = start-1;
    j_ptr = startptr;
    i_ptr = nullptr;
    for(int j=start;j<=end-1;j++){
      if(*j_ptr->object < *pivot->object){
        i++; 
        if(i_ptr==nullptr) i_ptr=startptr;
        else i_ptr = i_ptr->next;
        
        
        Swap1(i_ptr, j_ptr);
      }
      j_ptr = j_ptr->next;
    }
    i++;
    if(i_ptr==nullptr) i_ptr=startptr;
        else i_ptr = i_ptr->next;
    
    
    Swap1(i_ptr,pivot);

    int P_index = i;

   
    /***********************PARTITION****************************
    int left=0, right=0;
    listOfObjects<TrainInfoPerStation*>* leftptr=pivot->prev, *rightptr=pivot->next;
    while(left<pivot_index && right<end-pivot_index-start){
      while(*leftptr->object<*pivot->object && left<pivot_index){
        leftptr=leftptr->prev;
        left++;
      }
      while(*pivot->object<*rightptr->object &&  right<end-pivot_index-start){
        rightptr=rightptr->next;
        right++;
      }
      if(*rightptr->object < *leftptr->object) Swap1(leftptr,rightptr);
    }
    while(left<pivot_index){
    while(*leftptr->object<*pivot->object && left<pivot_index){
        leftptr=leftptr->prev;
        left++;
    }
    if(leftptr->prev!=nullptr)leftptr->prev->next= leftptr->next;
    leftptr->next->prev=leftptr->prev;

    if(pivot->next!=nullptr)pivot->next->prev=leftptr;
    pivot->next=leftptr;
    
    pivot_index--;
    }
    while(right<end-pivot_index-start){
     while( *pivot->object <*rightptr->object && right<end-pivot_index-start){
        rightptr=rightptr->next;
        right++;
      } 

      if(rightptr->next!=nullptr)rightptr->next->prev= rightptr->prev;
      rightptr->prev->next=rightptr->next;

    if(pivot->prev!=nullptr)pivot->prev->next=rightptr;
    pivot->prev=rightptr;
    
    pivot_index++;
    }




    ****************************PARTITION ENDS****************************/
    //int P_Index = start+pivot_index;
    /*******************RECURSE*********************************************/
    QuicksortSimple(stnInfoList, start, i-1 );
    QuicksortSimple(stnInfoList, i+1, end);
    

  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}


#endif
