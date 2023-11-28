#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP
# include <cmath>
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
   static listOfObjects<TrainInfoPerStation *> ** array;

  static listOfObjects<TrainInfoPerStation *> * tail=nullptr ;
  static listOfObjects<TrainInfoPerStation *> *head= nullptr;
  static listOfObjects<TrainInfoPerStation *> *parted;
  
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
        int length=0 ;   //get the length of the whole list 
        listOfObjects<TrainInfoPerStation *> *head_temp=stnInfoList; //a temporary variable to store head to original list
        while(head_temp!=nullptr){ //iterate over the whole linked list once 
            length ++;
            tail=head_temp;
            head_temp=head_temp->next;
        }
   
        float max =length/K;   //get the maximum number of elements that
        int approx=ceil(max);  // can be stores in the additional space
        array = new listOfObjects<TrainInfoPerStation *> *[approx];  //allocate space n/K
       
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    // Find length of the list stnInfoList, if needed.
      }
    
    
    listOfObjects<TrainInfoPerStation *> *temp_head =head;
   
    
    if (head !=tail){// call recursive function untill the list has one element 
        parted = partition(stnInfoList,tail,K,array); 
        head=stnInfoList;  // change value of head for next recursion
       
        Quicksort(parted); // for second half of list
   
        head =temp_head; // restore value
    
       if (head !=stnInfoList && head !=stnInfoList->prev){ //check base cases
          parted = partition(head,stnInfoList,K,array); 
          tail=stnInfoList;   // change value of head for next recursion

          Quicksort(parted); // for first half of list
        }
    }

  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

listOfObjects<TrainInfoPerStation *> * Planner:: partition(listOfObjects<TrainInfoPerStation *> * start ,listOfObjects<TrainInfoPerStation *> * finish,int K,listOfObjects<TrainInfoPerStation *> * * array){
 
    static listOfObjects<TrainInfoPerStation *> * forward ; // similar to i in array quicksort 
    forward =start;
    static listOfObjects<TrainInfoPerStation *> * backward ; // similar to j in array quicksort
    backward =finish;
    static listOfObjects<TrainInfoPerStation *> *pivot;

    int length=0 ;
    
    static listOfObjects<TrainInfoPerStation *> *head_temp; 
    head_temp=start;

    while(head_temp!=backward->next && head_temp!=nullptr){  
      length ++;               // to find the lenght of the current list
      head_temp=head_temp->next;
    }

    if(length==0) return nullptr; // corner case when the list is not valid

    static listOfObjects<TrainInfoPerStation *> *temp;
    temp=start;
 
    int index=0;
    while(temp!=nullptr){ //store every 1 mod K element in the array 
      array[index]=temp;
      for(int i=0;i<K;i++){
        if ( temp ==nullptr){ //till the end of the original list
          break;
        }
        temp=temp->next ;
      }
      if ( temp ==nullptr){
          break;}
      index++; // only  atmost n/K elements will be stored hence 
      
    }

    int index_pivot=rand()%length ; // generate a random pivot index
    int stop= index_pivot/K; 
    int additional=index_pivot%K; // finding the pivot in O(k) time
    pivot=array[stop];
    for(int i=0;i<additional;i++)
    { 
      pivot=pivot->next;
    }
    int pivot_daydata;  // get the day of the week alloted to the pivot station 
    if(pivot==nullptr) pivot_daydata = -2;
      else{
         for(int i=0;i<7;i++){
          if(pivot->object->daysOfWeek[i]==1) // check the array of dayOfWeek array
          pivot_daydata=i;
          }
      }

    int pivot_time=pivot->object->arrTime;
    bool isstart=true;  // no decrement  of the value  of j for first iteration
    bool isend=true;  // no decrement  of the value  of i for first iteration
    bool cross=false; // to check if the i=j similar to in array quicksort

    while(true){
        while(true){ 
              if (!isstart)backward=backward->prev; 
              isstart=false;

              int daydata; // get the value of the  day of the linked list node
              if(backward==nullptr) daydata = -2;
              else{
                  for(int i=0;i<7;i++){
                  if(backward->object->daysOfWeek[i]==1)
                  daydata=i;
                  }
              }
     
              if (forward==backward) {cross=true;break;} // if i==j escape the loop
              if(daydata< pivot_daydata || (daydata==pivot_daydata && backward->object->arrTime<=pivot_time)|| backward==start->prev ||backward ==nullptr) 
                  {   // check the conditions for swap 
                  break; // criteria order being day and then arrival time 
                  } 
      
        }

      if(forward!=backward){  // check if already i=j;
        while(true){
            if (!isend)forward=forward->next;
            isend=false;
            int daydata ;  // get the value of the  day of the linked list node
            if(forward==nullptr) daydata= -2;
            else{
                for(int i=0;i<7;i++){
                    if(forward->object->daysOfWeek[i]==1)
                        daydata=i;
                }
            }
 
            if (forward==backward) {cross=true;break;}   // if i==j escape the loop
            if(daydata> pivot_daydata || (daydata==pivot_daydata && forward->object->arrTime>=pivot_time)||forward==finish->next || forward ==nullptr) // equality? nullptr?
              {break;} // criteria order being day and then arrival time
                    // check the conditions for swap 
        } 
      }
   
    
 
      if( cross==false ){ // swap condition
      if(forward!=nullptr && backward!=nullptr ) //check if swap is valid
          swap((forward->object), (backward->object)); }
      else{return backward;} // return node at j
    
    }


}


void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> ** array;
  static listOfObjects<TrainInfoPerStation *> * tail=nullptr ;
  static listOfObjects<TrainInfoPerStation *> *head= nullptr;
  

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
    int length=0 ; //get the length of the whole list 
        listOfObjects<TrainInfoPerStation *> *head_temp=stnInfoList;//a temporary variable to store head to original list
        while(head_temp!=nullptr){
            length ++;  //iterate over the whole linked list once
            tail=head_temp;
            head_temp=head_temp->next;
        }
   
        float max =length/K;   //get the maximum number of elements that
        int approx=ceil(max);  // can be stores in the additional space
        array = new listOfObjects<TrainInfoPerStation *> *[approx]; //allocate space n/K
         int index=0;
    while(stnInfoList!=nullptr){  //store every 1 mod K element in the array 
      array[index]=stnInfoList;
      for(int i=0;i<K;i++){
        
        if (stnInfoList ==nullptr){ //till the end of the original list
          break;
        }
        stnInfoList =stnInfoList->next ;
      
      }
      if ( stnInfoList==nullptr){
          break;}
      index++;  // only  atmost n/K elements will be stored hence
     
    }

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
   if (start<end && start>-1 && end>-1)
     { int q =partitionsimple (stnInfoList,K,array,start,end); // partition the list into two parts 
      QuicksortSimple (stnInfoList, start,q); // recurse on first half
      QuicksortSimple(stnInfoList,q+1,end);} // recurse on second half
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}


int Planner::partitionsimple (listOfObjects<TrainInfoPerStation *> *stnInfo,int K,listOfObjects<TrainInfoPerStation *> * *array,int p,int r){


    int j= r+1;
    int i =p-1;

    static listOfObjects<TrainInfoPerStation *> * forward ; 
    static listOfObjects<TrainInfoPerStation *> * start ;
   
  
    int stop= p/K;  //find out the first element of this part of list 
    int additional=p%K;
    forward=array[stop]; // using the elements stored in the array
    for(int i=0;i<additional;i++)
    { 
     forward=forward->next;
    
    }
    start =forward; // create a permanent variable 'start' for this call foe comparison afterwards

   static listOfObjects<TrainInfoPerStation *> * backward ; 
   static listOfObjects<TrainInfoPerStation *> * finish ;
    stop= r/K;  //find out the last element of this part of list 
    additional=r%K;
    backward=array[stop]; // using the elements stored in the array
    for(int i=0;i<additional;i++)
    { 
      backward= backward->next;
    
    } 
    finish = backward; // create a permanent variable 'finish' for this call foe comparison afterwards

   static listOfObjects<TrainInfoPerStation *> *pivot;
   int length=0 ; // find the length of this list 

    static listOfObjects<TrainInfoPerStation *> *head_temp; // use a temporary variable to find length
    head_temp=forward;
    while(head_temp!=backward->next && head_temp!=nullptr){  
      length ++;
    
      head_temp=head_temp->next;
    }

    if(length==0) return -3;
 
    int index_pivot=rand()%length +p; // generate a random pivot index
    stop= index_pivot/K;
    additional=index_pivot%K;
    pivot=array[stop]; // finding the pivot in O(k) time
    for(int i=0;i<additional;i++)
    { 
      pivot=pivot->next;
    
    }
    int pivot_daydata; // get the day of the week alloted to the pivot station
     if(pivot==nullptr) pivot_daydata = -2;
      else{
         for(int i=0;i<7;i++){
          if(pivot->object->daysOfWeek[i]==1) // check the array of dayOfWeek array
          pivot_daydata=i;
          }
      }
    
    int pivot_time=pivot->object->arrTime;

    bool isstart=true; // no decrement  of the value  of j for first iteration
    bool isend=true;  // no decrement  of the value  of i for first iteration
    bool cross=false;// to check if the i=j similar to in array quicksort

    while(true){ 
        while(true){ 
          if (!isstart)backward=backward->prev; 
          isstart=false;
          j--;
          int daydata; // get the value of the  day of the linked list node
              if(backward==nullptr) daydata = -2;
              else{
                  for(int i=0;i<7;i++){
                  if(backward->object->daysOfWeek[i]==1)
                  daydata=i;
                  }
              }
          if (forward==backward) {cross=true;break;} // check if already i=j;
          if(daydata< pivot_daydata || (daydata==pivot_daydata && backward->object->arrTime<=pivot_time)|| backward==start->prev ||backward ==nullptr) //needed?
          { // criteria order being day and then arrival time 
          break;} 
      
        }
       if(forward!=backward){
       while(true){
          if (!isend)forward=forward->next;
          isend=false;
          i++;
          int daydata ;  // get the value of the  day of the linked list node
            if(forward==nullptr) daydata= -2;
            else{
                for(int i=0;i<7;i++){
                    if(forward->object->daysOfWeek[i]==1)
                        daydata=i;
                }
            }
          if (forward==backward) {cross=true;break;} // if i==j escape the loop
          if(daydata> pivot_daydata || (daydata==pivot_daydata && forward->object->arrTime>=pivot_time)||forward==finish->next || forward ==nullptr) // equality? nullptr?
          {break;} // criteria order being day and then arrival time
      
        }
      }
   
    
    // check the conditions for swap 
    if( cross==false ){ // swap condition
       if(forward!=nullptr && backward!=nullptr ) //check if swap is valid
          swap((forward->object), (backward->object)); }
    else{return j;} // return  j
    
    }
   
};

#endif
