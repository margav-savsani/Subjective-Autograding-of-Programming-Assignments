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
#include <time.h>

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
bool compare(TrainInfoPerStation *t1,TrainInfoPerStation *t2){
  int p,q;
  for(int i=0;i<7;i++){
    if(t1->daysOfWeek[i])
      p=i;   //finding day for t1
    
  }
   for(int j=0;j<7;j++){
    if(t2->daysOfWeek[j])
      q=j;    //finding day for t2
    
  }
  if(p<q){
    return true;   //if dep time of t1 is lesser then returns true
  }
  else if(p==q){
    if (t1->depTime < t2->depTime) return true;
    else if(t1->depTime==t2->depTime){
      if(t1->arrTime<t2->arrTime) return true;  //if dep time is also same we compare arr time
      else return false;
    }
    else return false;
  }

  else return false;
}

int partition(int start,int end,int K,listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation*>**s){

  srand((unsigned)time(NULL));


    int pivotIndex = (rand()%(end-start))+start;

    int t=pivotIndex/K;
    int p=pivotIndex%K;

    listOfObjects<TrainInfoPerStation*>*t3=s[t];
    for(int i=0;i<p;i++){    
        t3=t3->next;      //recursing towards t3
      }

    TrainInfoPerStation piv=*(t3->object);  //setting pivot to t3
    int i=start;
    int j=end;
    listOfObjects<TrainInfoPerStation*> *l1=stnInfoList;
    listOfObjects<TrainInfoPerStation*> *l2=stnInfoList;
    for(int m=0;m<end;m++){   
    
    l2=l2->next;  //l2 is at end 

    } 
    for(int n=0;n<start;n++){
      l1=l1->next;  //l1 is at start
    }
    
    while (true) {
    

        while(compare(l1->object,&piv)) {  
            l1=l1->next;  
            i=i+1;      
            
        }
        while(compare(&piv,l2->object)){
            l2=l2->prev;          
            j-=1;
        }
        if(i < j) {          
            TrainInfoPerStation t=*(l1->object);
            *(l1->object)=*(l2->object);
            *(l2->object)=t;    //swapping the objects

            
        }
        else{
            return j;
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
 
  
 
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  static int len=1;
  recursionLevel+=1;

  
  
  if(recursionLevel==0){
    listOfObjects<TrainInfoPerStation*> *l1=stnInfoList;
    len=1;
    while(l1->next!=nullptr){     //len++ till the next is null 
      l1=l1->next;
      len+=1;
    }  
  }
  
  

  static listOfObjects<TrainInfoPerStation*> **arr= new listOfObjects<TrainInfoPerStation*>*[((len)/K)+1];
     

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

    listOfObjects<TrainInfoPerStation*>*obj=stnInfoList;
      int i=0;
      int j=0;    
      while(obj!=nullptr){//setting values in array for consecutive 4 increments
        if(i%4==0){//till it is null
          arr[j]=obj; 
          j++;
        }
        i=i+1;
        i=i%4;
        obj=obj->next;
      }  
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  if(start < end){
        
        int piv = partition(start,end,K,stnInfoList,arr); //setting pivot in partition function 
        QuicksortSimple(stnInfoList,start,piv);        
        QuicksortSimple(stnInfoList,piv+1,end);
    }

  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return ;
}

#endif
