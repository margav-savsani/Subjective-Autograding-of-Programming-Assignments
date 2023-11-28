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
static listOfObjects< TrainInfoPerStation*> **compressed_list;

void swap(int index_1,int index_2,listOfObjects<TrainInfoPerStation*> *stnInfoList,listOfObjects<TrainInfoPerStation*> **arr){
         int i=index_1/4;
         int j=index_1%4;
         int k=index_2/4;
         int l=index_2%4;

         listOfObjects<TrainInfoPerStation*> *a=( listOfObjects< TrainInfoPerStation*> *)malloc(sizeof(listOfObjects< TrainInfoPerStation*>));
        if(j==0){ a=arr[i];}
        else if(j==1) {a=arr[i]->next; }
        else if(j==2){ a=arr[i]->next->next;}
        else if(j==3) {a=arr[i]->next->next->next; }

         listOfObjects<TrainInfoPerStation*> *b=( listOfObjects< TrainInfoPerStation*> *)malloc(sizeof(listOfObjects< TrainInfoPerStation*>));
        if(l==0) {b=arr[k];}
        else if(l==1) {b=arr[k]->next;}
        else if(l==2){ b=arr[k]->next->next;}
        else if(l==3) {b=arr[k]->next->next->next;}
            TrainInfoPerStation* t=a->object;
            a->object=b->object;
            b->object=t;

}
int partition(listOfObjects<TrainInfoPerStation*> **arr,listOfObjects<TrainInfoPerStation *> *stnInfoList,int start,int finish){
        int pivot_choice;
        pivot_choice=rand()%(finish-start+1)+start;
        swap(pivot_choice,finish,stnInfoList,arr);
        static listOfObjects<TrainInfoPerStation*> *pivot=( listOfObjects< TrainInfoPerStation*> *)malloc(sizeof(listOfObjects< TrainInfoPerStation*>));
        if(finish%4==0) pivot= arr[finish/4];
        else if(finish%4==1) pivot=arr[finish/4]->next;
        else if(finish%4==2) pivot=arr[finish/4]->next->next;
        else if(finish%4==3) pivot=arr[finish/4]->next->next->next;

        int day_1;
        bool* bool_1=pivot->object->daysOfWeek;
        for( int i=0;i<7;i++){
            if(bool_1[i]){
                day_1=i;
                break;
            }
        }

        static listOfObjects<TrainInfoPerStation*> *a=( listOfObjects< TrainInfoPerStation*> *)malloc(sizeof(listOfObjects< TrainInfoPerStation*>) );
        if(start%4==0) a= arr[start/4];
        else if(start%4==1) a=arr[start/4]->next;
        else if(start%4==2) a=arr[start/4]->next->next;
        else if(start%4==3) a=arr[start/4]->next->next->next;

        int i=start-1;  
        for( int j=start; j<=finish; j++){
            int day_2;
            bool* bool_2=a->object->daysOfWeek;
           for( int k=0;k<7;k++){
               if(bool_2[k]){day_2=k; break;}
           }
           if(day_2<day_1){
               i++;
               swap(i,j,stnInfoList,arr);
           }
           else if(a->object->depTime<pivot->object->depTime && day_2==day_1){
               if(a->object->depTime!=-1){
                  i++;
                  swap(i,j,stnInfoList,arr);
               }
           }
            else if(a->object->depTime==pivot->object->depTime && day_2==day_1){
               if(a->object->arrTime<pivot->object->arrTime){
                   i++;
                   swap(i,j,stnInfoList,arr);
               }
              else if(a->object->arrTime==pivot->object->arrTime){
                   if(a->object->journeyCode<pivot->object->journeyCode){
                      i++;
                      swap(i,j,stnInfoList,arr);
                   }
              }
           }
           a=a->next;
        }
        swap(i+1,finish,stnInfoList,arr);
        return i+1;
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int start_1;
  static int end_1;
  int start_2;
  int end_2;
  // Increment recursion level on entering the function
  recursionLevel++;

   int i=0;
  static listOfObjects<TrainInfoPerStation *> *b;
  b=stnInfoList;
  while(stnInfoList!=nullptr){
    stnInfoList=stnInfoList->next;
    i++;
  }
  stnInfoList=b;
  int j=i/K+1;
  static listOfObjects< TrainInfoPerStation*> **compressed_list=( listOfObjects< TrainInfoPerStation*> **)malloc(sizeof(listOfObjects< TrainInfoPerStation*>*) * j);

  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    static listOfObjects<TrainInfoPerStation *> *a;
    a=stnInfoList;
    int i=0,j=0;
    while(stnInfoList!=nullptr){
       if(i%K==0){
          compressed_list[j]=stnInfoList;
          j++;  
       }
       i++;
       stnInfoList=stnInfoList->next;
    }
    stnInfoList=a;
    start_1=0;
    end_1=i-1;
  }
  // Put your code for the core of Quicksort here
  if(start_1<=end_1){
        start_2=start_1;
        end_2=end_1;
        int p=partition(compressed_list, stnInfoList,start_1,end_1);
        start_1=start_2;
        end_1=p-1;
        Quicksort(stnInfoList);
        start_1=p+1;
        end_1=end_2;
        Quicksort(stnInfoList);
        // if(count==0) s=p;
        // int end_2;
        // int start_2=r+1;
        // start_1=start_2;
        // end_1=p-1;
        // if(p==s && count!=0){end_2=i-1; f=1;}
        // else{
        //   if(f!=1)end_2=q-1;
        //   else end_2=n;
        // }
        // n=p-1;
        // count++;
        // q=p;
        // Quicksort(stnInfoList);  // Before p
        // start_1=p+1;
        // end_1=end_2;
        // r=p;
        // n=end_1;
        // Quicksort(stnInfoList); // After p
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
  int i=0;
  static listOfObjects<TrainInfoPerStation *> *b;
  b=stnInfoList;
  while(stnInfoList!=nullptr){
    stnInfoList=stnInfoList->next;
    i++;
  }
  stnInfoList=b;
  int j=i/K+1;
  static listOfObjects< TrainInfoPerStation*> **compressed_list=( listOfObjects< TrainInfoPerStation*> **)malloc(sizeof(listOfObjects< TrainInfoPerStation*>*) * j);

  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    static listOfObjects<TrainInfoPerStation *> *a=stnInfoList;
    int i=0,j=0;
    while(stnInfoList!=nullptr){
       if(i%K==0){
          compressed_list[j]=stnInfoList;
          j++;  
       }
       i++;
       stnInfoList=stnInfoList->next;
    }
    stnInfoList=a;
  }
   //Put your code for the core of QuicksortSimple here
    if(start<=end){
        int p=partition(compressed_list, stnInfoList,start,end);
        QuicksortSimple(stnInfoList ,start, p-1);  // Before p
        QuicksortSimple(stnInfoList, p+1,end); // After p
    }
    recursionLevel--;
  return;
}

#endif
