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

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *&stnInfoList)
{
  int end=0;
  while(stnInfoList->next){
    end++;
    stnInfoList=stnInfoList->next;
  }
  while(stnInfoList->prev){
    stnInfoList=stnInfoList->prev;
  }
  QuicksortSimple(stnInfoList,0,end);
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *&stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int multiplier=1000;     //a constant multiplier so pivot is chosen
                                  //multiplier*K steps
  // Increment recursion level on entering the function
  recursionLevel++;
  static int arrsize;
  static listOfObjects<TrainInfoPerStation*>**arrK;
  static listOfObjects<TrainInfoPerStation*>*iter;
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    arrsize=(end-start+1)/K +1;
    arrK=new listOfObjects<TrainInfoPerStation*>*[arrsize];

  }  
  iter=stnInfoList;
  while(iter->prev){
    iter=iter->prev;
  }
  int count=0;
  while(count<arrsize){
    arrK[count]=iter;
    for(int i=0;i<K;i++){
      if(!iter){
        break;
      }
      iter=iter->next;
    }
    count++;
  }

  //choosing the pivot
  int pivotN = start+rand()%(end-start+1);
  listOfObjects<TrainInfoPerStation*>* pivot;
  int arrIndex=pivotN/K;
  pivot=arrK[arrIndex];
  int extraSteps = pivotN%K;
  for(int j=0;j<extraSteps;j++){
    pivot=pivot->next;
  }

  if(start==end){
    recursionLevel--;
    return;
  }
  if(start>end){
    recursionLevel--;
    return;
  }
  if(start==end-1 && lessThan(stnInfoList->object,stnInfoList->next->object)){
    recursionLevel--;
    return;
  }

  listOfObjects<TrainInfoPerStation*>* firstTrain=nullptr;
  if(pivot->prev){
    pivot->prev->next=pivot->next;
  }
  if(pivot->next){
    pivot->next->prev=pivot->prev;
  }

  listOfObjects<TrainInfoPerStation*>* last;
  if(stnInfoList==pivot){
    last =stnInfoList->next;
    int count=0;
    while(count<end-start-1){
      last=last->next;
      count++;
    }
    pivot->next=last->next;
  }
  else{
    last =stnInfoList;
    int count=0;
    while(count<end-start-1){
      last=last->next;
      count++;
    }
    pivot->next=last->next;
  }

  int pivotIndex;
  if(stnInfoList==pivot){
    int counter=0;
    while(counter<end-start-1){
      last=last->prev;
      counter++;
    }
    pivotIndex=partition(last,pivot,end-start,pivot,stnInfoList->prev,firstTrain);
  }
  else{
    pivotIndex=partition(stnInfoList,pivot,end-start,pivot,stnInfoList->prev,firstTrain);
  }
  stnInfoList=firstTrain;

  QuicksortSimple(pivot,pivotIndex,end);
  QuicksortSimple(firstTrain,start,start+pivotIndex-1);
  stnInfoList=firstTrain;
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

int Planner::partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation*>* pivot,int num,listOfObjects<TrainInfoPerStation *>*tempMore,listOfObjects<TrainInfoPerStation*>*tempLess,listOfObjects<TrainInfoPerStation*>*&firstTrain){  //tempMore should be pivot when calling,tempLess should be stnInfoList.prev
  int count=0;
  int pivotIndex=0;
  while(count<num){
    /*
    currInfo=stnInfoList->object;
    if (currInfo != nullptr) {
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
        string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	      if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	      cout << "Starts";
      }
      else {
	      cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	      cout << "Ends";
      }
      else {
	      cout << currInfo->depTime;
      }
      cout << endl;
    }
    */
    listOfObjects<TrainInfoPerStation*>* temp=stnInfoList->next;
    if(lessThan(stnInfoList->object,pivot->object)){
      //cout<<"less"<<endl;
      if(!firstTrain){
        firstTrain=stnInfoList;
      }
      pivotIndex++;
      if(tempLess){
        tempLess->next=stnInfoList;
      }
      stnInfoList->prev=tempLess;
      tempLess=stnInfoList;
    }
    else{
      //cout<<"more"<<endl;
      stnInfoList->next=tempMore->next;
      tempMore->next=stnInfoList;
      stnInfoList->prev=tempMore;
      tempMore=stnInfoList; 
    }
    stnInfoList=temp;
    count++;
  }
  if(tempLess){
    tempLess->next=pivot;
  }
  pivot->prev=tempLess;
  return pivotIndex;
}

bool Planner::lessThan(TrainInfoPerStation* train1, TrainInfoPerStation* train2){
  for(int i=0;i<7;i++){
    if(train1->daysOfWeek[i] && !train2->daysOfWeek[i]){
      return true;
    }
    else if(!train1->daysOfWeek[i] && train2->daysOfWeek[i]){
      return false;
    }
    else if(train1->daysOfWeek[i] && train2->daysOfWeek[i]){
      if(train1->arrTime==-1 && train2->arrTime==-1){
        if(train1->depTime<train2->depTime){
          return true;
        }
        else{
          return false;
        }
      }
      else if(train1->arrTime==-1){
        return false;
      }
      else if(train2->arrTime==-1){
        return true;
      }
      else if(train1->arrTime < train2->arrTime){
        return true;
      }
      else{
        return false;
      }
    }
    else{
      continue;
    }
  }
  return true;
}


#endif
