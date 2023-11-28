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
  const static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **MainArr=nullptr;
  static listOfObjects<TrainInfoPerStation *> *Front=nullptr;// Variable used for storing the start of the current linked list
  static listOfObjects<TrainInfoPerStation *> *End=nullptr;// Variable used for storing the end of the current linked list
  static listOfObjects<TrainInfoPerStation *> *FrontTravel=nullptr;// Variable used to traverse the linked list from the front
  static listOfObjects<TrainInfoPerStation *> *EndTravel=nullptr;//Variable used to traverse the linked list from the back 
  static listOfObjects<TrainInfoPerStation *> *temp=nullptr; //temporary variable for switching
  static listOfObjects<TrainInfoPerStation *> *temp1=nullptr; //temporary variable for switching
  static listOfObjects<TrainInfoPerStation *> *current=nullptr; //temporary variable1
  static int n;//Stores length of the linked list
  static int x;//Stores the pivot day
  static int a1, a2;//Stores numbers generated from rand()
  static TrainInfoPerStation * temp2;
  static bool flag1=false;//Flags for testing edge cases
  static bool flag2=false;
  static int startTravel, finishTravel;//Static variables that travel the list
  static int start, finish;
  static int check1, check2, check3, check4;
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
    int length=1;
    listOfObjects<TrainInfoPerStation *> *curr= stnInfoList;
    Front=curr;
    FrontTravel=curr;
    while(curr->next!=nullptr){
        curr=curr->next;
        length++;
    }
    if(length<=1){
        return;
    }
    End=curr;
    EndTravel=curr;
    curr=stnInfoList;
    n=length; 
    flag1=false;
    flag2=false;
    int t=n/K;
    if(t*K < n){
        MainArr = new listOfObjects<TrainInfoPerStation *>*[n/K +1]; //Array of size n/K+1
    }
    else{
        MainArr = new listOfObjects<TrainInfoPerStation *>*[n/K];
    }
    int counter2 = 0;
    start=0;
    finish=n-1;
    for(int i=0; i<n; i++){
        if(i%K == 0){
            MainArr[counter2]=(curr);// Initialising the array using every kth element of the array
            counter2++;
            
        }
        curr=curr->next;
    }

  }
  
  // Put your code for the core of Quicksort here
  static listOfObjects<TrainInfoPerStation *> *pivot; // pivot also a static variable
  static int pivotDay; //pivot day static
  pivotDay=0;
  if(start >= finish){
     return;
  }
  current=Front;
  static int counter1;
  counter1=0;
  for(int i=0; i<n; i++){
    if(i==start){
        FrontTravel=current;
    }
    if(i==finish){
        EndTravel=current;
        break;
    }
    current=current->next;
  }
  

  srand(time(0));
  if((finish-start)/K !=0)
    a1=(start/K)+(((int)(rand())%((finish-start)/K)));//A random number to choose from the array in O(1) time
  else{
    a1=start/K;
  }
  a2=(int)(rand())%(K);// A random number to choose from the linked list in O(K) time
  if(finish-start<=K){
      current=FrontTravel;
      for(int p=0; p<a2; p++){
        if(current==EndTravel){
            break;
        }
        current=current->next;
      }
  }
  else{
    current=MainArr[a1];
    cout<<MainArr[a1]->object->arrTime<<endl;
    if(a1*K < start){
        while(current != FrontTravel){
            current=current->next;
            a2=a2-1;
        }
        for(int i=0; i<a2; i++){
            current=current->next;
        }
    }
    else{
        for(int i=0; i<a2; i++){
            if(current==EndTravel){
                break;
            }
            current=current->next;
        }
    }
  }
  if(current==nullptr){
    current=EndTravel;
  }
/*
  x= (finish+start)/2;
  current=Front;
  for(int i=0; i<x; i++){
      current=current->next;
  }*/
  pivot=current;
  for(int k=0; k<7; k++){
    if(pivot->object->daysOfWeek[k]==true){
        pivotDay=k;
        break;
    }
  }
   if(start<finish){
        startTravel=start-1;
        finishTravel=finish+1;
        while(true){//Main loop
            flag1=false;
            flag2=false;
            current=Front;
            do{
                startTravel=startTravel+1;
                for(int k=0; k<7; k++){
                    if(FrontTravel->object->daysOfWeek[k] == true){
                        check1 = k;
                    }
                }
                check3=FrontTravel->object->arrTime;
                if(FrontTravel->next==nullptr){
                    flag1=true;
                    break;
                }
                else{
                    FrontTravel = FrontTravel->next;
                }
            }while((check1 < pivotDay)||((check1 == pivotDay)&&(pivot->object->arrTime > check3)));//loop until the time of the journey is less than the pivot

            do{
                finishTravel=finishTravel-1;
                for(int k=0; k<7; k++){
                    if(EndTravel->object->daysOfWeek[k] == true){
                        check2 = k;
                    }
                }
                check4=EndTravel->object->arrTime;
                if(EndTravel->prev==nullptr){
                    flag2=true;
                    break;
                }
                else{
                    EndTravel = EndTravel->prev;
                }
            }while((pivotDay < check2) || ((check2 == pivotDay)&&(pivot->object->arrTime < check4)));//loop until the time of the journey is greater than the pivot          
            if(startTravel<finishTravel){
                if(flag1==true){
                    if(flag2==true){
                        temp2=FrontTravel->object;
                        FrontTravel->object=EndTravel->object;
                        EndTravel->object=temp2;
                        flag1=false;
                        flag2=false;
                    }
                    else{
                        temp2=FrontTravel->object;
                        FrontTravel->object=EndTravel->next->object;
                        EndTravel->next->object=temp2;
                        flag1=false;
                        flag2=false;
                    }
                }
                else{
                    if(flag2==true){
                        temp2=FrontTravel->prev->object;
                        FrontTravel->prev->object=EndTravel->object;
                        EndTravel->object=temp2;
                        flag1=false;
                        flag2=false;
                    }
                    else{
                        temp2=FrontTravel->prev->object;
                        FrontTravel->prev->object=EndTravel->next->object;
                        EndTravel->next->object=temp2;
                        flag1=false;
                        flag2=false;
                    }
                }
            }
            else
                break;
        }
        if(finishTravel == finish){
            finishTravel = finishTravel-1;
        }
        int start1=start;
        int finish1=finishTravel;
        int start2 = finishTravel+1;
        int finish2=finish;
        start=start1;
        finish=finish1;
        startTravel=start1;
        finishTravel=finish1;             
        Quicksort(Front);
        start=start2;
        finish=finish2;
        startTravel=start2;
        finishTravel=finish2;
        Quicksort(Front);
        return;
    }
    return;
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
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
