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

#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP


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

void printAll(listOfObjects<TrainInfoPerStation *> *expandedList){
  listOfObjects<TrainInfoPerStation *> *currList = expandedList;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  TrainInfoPerStation *currInfo;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
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
    currList = currList->next;
  }
  cout << endl;
}


bool equal(TrainInfoPerStation * t1, TrainInfoPerStation * t2){
  bool ans = t1->journeyCode == t2->journeyCode && t1->stopSeq == t2->stopSeq && t1->arrTime == t2->arrTime && t1->depTime == t2->depTime;
  bool weekssame = true;
  for(int i = 0; i < 7; i++){
    weekssame = weekssame && (t1->daysOfWeek[i] == t2->daysOfWeek[i]);
  }
  return ans&&weekssame;
}
listOfObjects<TrainInfoPerStation *> * partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation *> *pivotObj, int &pivotIndex, int numelem){
  listOfObjects<TrainInfoPerStation *> *nextToChange = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *justChanged = nullptr;
 listOfObjects<TrainInfoPerStation *> *pivotInTheList= nullptr; 
  int numChanged = 0;
  TrainInfoPerStation * pivotInfo = pivotObj->object;
  int j = 0;
  while(j < numelem){ // TODO: Fix this
    j++;
    bool lessthanpivot = true; // True in the beginning to account for both being the same
    if(equal(pivotInfo, stnInfoList->object)){
      pivotInTheList = stnInfoList;
      lessthanpivot = true;
    }
    else{
      for(int i = 0; i < 7; i++){
        if(stnInfoList->object->daysOfWeek[i] && !pivotInfo->daysOfWeek[i]){
          lessthanpivot = true;
          break;
        }
        else if(!stnInfoList->object->daysOfWeek[i] && pivotInfo->daysOfWeek[i]){
          lessthanpivot = false;
          break;
        }
        else if(stnInfoList->object->daysOfWeek[i] && pivotInfo->daysOfWeek[i]){
          lessthanpivot = stnInfoList->object->depTime <= pivotInfo->depTime;
          break;
        }
      }
    }
    // cout << lessthanpivot << endl;
    if(lessthanpivot){
      TrainInfoPerStation *temp = stnInfoList->object;
      stnInfoList->object = nextToChange->object;
      nextToChange->object = temp;
      justChanged = nextToChange;
      nextToChange = nextToChange->next;
      numChanged += 1;
    }
    stnInfoList = stnInfoList->next;
  }
  if(numChanged == 0){
    // cout << "No way" << endl;
  }
  pivotIndex = numChanged-1; // The -1 because numChanged is a count, while pivotIndex is 0-indexed
  if(numChanged != numelem)
  // if(1)
    return justChanged;
  else {
    // Keep the pivot on the other side
    // Swap pivotInTheList with the last changed element and put on the other side
    TrainInfoPerStation *temp = justChanged->object;
    justChanged->object = pivotInTheList->object;
    pivotInTheList->object = justChanged->object;
    pivotIndex -= 1;
    return justChanged->prev;
  }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  if(stnInfoList == nullptr) return;
  
  // A few static variable declarations
  static int k = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int start = 0;
  static int end = -1;
  // Increment recursion level on entering the function
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation *> **checkpoints;
  int n=0;
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
  

  if (recursionLevel <= 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    
   listOfObjects<TrainInfoPerStation *> * currInfoList = stnInfoList;
   while(currInfoList != nullptr){
    currInfoList = currInfoList->next;
    n++;
   }
   start = 0;
   end = n-1;
   currInfoList = stnInfoList;
   checkpoints = new listOfObjects<TrainInfoPerStation *> *[n/k];
   
   for(int i = 0; i < n/k; i++){
    for(int j = 0; j < k; j++){
      currInfoList = currInfoList->next;
    }
    checkpoints[i] = currInfoList;
   }

  }

  // cout << "Entry " << recursionLevel << endl;
  // cout << "Start = " << start << " End = " << end << endl;
  // cout << "pointer to first element " << stnInfoList << endl; 
  // cout << "Before Sorting" << endl;
  // printAll(stnInfoList);
  
  if(end - start <= 0){
    recursionLevel--;
    return;
  }
  // Put your code for the core of Quicksort here
  int pivotindex = start + rand()%(end-start+1);
  // cout << "Pivot index = " << pivotindex << endl;

  listOfObjects<TrainInfoPerStation *>* pivotObj;
  if(pivotindex < k){
    // move pivotindex-start times forward
    pivotObj = stnInfoList;
    for(int j = 0; j < pivotindex-start; j++){
      pivotObj = pivotObj->next;
    }
  }
  else{
    pivotObj = checkpoints[(pivotindex-k)/k];
    for(int i = 0; i < pivotindex%k; i++){
      pivotObj = pivotObj->next;
    }
  }
  pivotObj = partition(stnInfoList, pivotObj, pivotindex, end-start+1);
  if(pivotObj == nullptr){
    
      // cout << "Bruh" << endl;
      Quicksort(stnInfoList);
      recursionLevel--;
      

      return;
  }

  pivotindex = pivotindex + start;
  // cout << "Output Pivot index " << pivotindex;
  start = start;
  int prevend = end;
  end = pivotindex;
  Quicksort(stnInfoList);
  start = pivotindex+1;
  end = prevend;
  Quicksort(pivotObj->next);


  // Decrement recursion level before leaving the function
  recursionLevel--;

  // cout << "After Sorting" << endl;
  // printAll(stnInfoList);
  // cout << "Exit " << recursionLevel << endl;
  if(recursionLevel == -1){
    start = 0;
    end = -1;
  }
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int k = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation *> **checkpoints;
  int n=0;
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
    
   listOfObjects<TrainInfoPerStation *> * currInfoList = stnInfoList;
   while(currInfoList != nullptr){
    currInfoList = currInfoList->next;
    n++;
   }
   start = 0;
   end = n-1;
   currInfoList = stnInfoList;
   checkpoints = new listOfObjects<TrainInfoPerStation *> *[n/k];
   
   for(int i = 0; i < n/k; i++){
    for(int j = 0; j < k; j++){
      currInfoList = currInfoList->next;
    }
    checkpoints[i] = currInfoList;
   }

  }
  
  // Put your code for the core of Quicksort here
  int pivotindex = start + rand()%(end-start+1);
  if(pivotindex < k){
    // move k-start times forward
  }

  listOfObjects<TrainInfoPerStation *>* pivotObj;
  if(pivotindex < k){
    // move k-start times forward
    pivotObj = stnInfoList;
    for(int j = 0; j < k-start; j++){
      pivotObj = pivotObj->next;
    }
  }
  else{
    pivotObj = checkpoints[(pivotindex-k)/k];
    for(int i = 0; i < pivotindex%k; i++){
      pivotObj = pivotObj->next;
    }
  }
  pivotObj = partition(stnInfoList, pivotObj, pivotindex, end-start+1);
  if(pivotObj == nullptr){
    if(end-start <= 1){
      return;
    }
    else{
      QuicksortSimple(stnInfoList, start, end);
      return;
    }
  }

  pivotindex = pivotindex + start;

  start = start;
  int prevend = end;
  end = pivotindex;
  QuicksortSimple(stnInfoList, start, end);
  start = pivotindex+1;
  end = prevend;
  QuicksortSimple(pivotObj, start, end);


  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif




// listOfObjects<TrainInfoPerStation *> * QuickSortRecursive(listOfObjects<TrainInfoPerStation *> *stnInfoList){
//   // Returns the last element in the sorted list
//   if(stnInfoList->next == nullptr){return stnInfoList;}
//   listOfObjects<TrainInfoPerStation *> * partition = partition(stnInfoList);
//   listOfObjects<TrainInfoPerStation *> *firstOfSecond = partition->next;
//   firstOfSecond->prev = nullptr;
//   partition->next = nullptr;

//   listOfObjects<TrainInfoPerStation *> * sorted1 =QuickSortRecursive(stnInfoList);
//   listOfObjects<TrainInfoPerStation *> * sorted2 =QuickSortRecursive(firstOfSecond); 
//   sorted1->next = firstOfSecond;
//   firstOfSecond->prev = sorted1;
//   // Sorted 1 address should be equal to partition
//   return sorted2;
// }


// void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
// {
//   // Put your code here.
//   QuickSortRecursive(stnInfoList);
// }
