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





void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  
  
  
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

void swap(listOfObjects<TrainInfoPerStation* > * a, listOfObjects<TrainInfoPerStation *> * b){
  listOfObjects <TrainInfoPerStation*> t = * b;
  b -> object = a -> object;
  a -> object = t.object;
}

bool lessThan(listOfObjects<TrainInfoPerStation *>*a, listOfObjects<TrainInfoPerStation *>*b){
  int i = 0;
  int j = 0;
  
  long int depTimeA = 0;
  long int depTimeB = 0;
  
  for(i = 0; i < 7; i++){
    if (a->object->daysOfWeek[i] == true){ //find the day when the train runs
      break;
    }
  }

  for(j = 0; j < 7; j++){
    if (a->object->daysOfWeek[j] == true){ //find the day when the train runs
      break;
    }
  }

  if (a->object->depTime != -1){
    //give larger preference to the days of week against time.
    depTimeA = 5555555 * i + a->object->depTime; 
  } else {
    depTimeA = 5555555 * 8;
  }


  if (b->object->depTime != -1){
    //give larger preference to the days of week against time.
    depTimeB = 5555555 * j + b->object->depTime; 
  } else {
    depTimeB = 5555555 * 8;
  }

  if(depTimeA < depTimeB){
    return true;
  } else {
    return false;
  }
}



void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation*> **trainList = nullptr;
  

  // Increment recursion level on entering the function
  recursionLevel++;
  

  int N = end - start + 1; //let N be the number of elements to be sorted

  if (start >= end){ //if start is ahead of end then return
    return;
  } 

  if (stnInfoList == nullptr){ //if the stnInfoList is a nullptr then return
    return;
  }

  

  
    
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    listOfObjects<TrainInfoPerStation *> * currPtr = stnInfoList;
    
    //find the value of the pointer at each interval of length K.
    int count = 0;
    trainList = new listOfObjects<TrainInfoPerStation *>*[ (N/ K) ];
    currPtr = stnInfoList;
    while(currPtr != nullptr){
      if (count % K == 0){
        trainList[count / K] = currPtr;
      }

      count++;
      currPtr = currPtr->next;
    }
  }
  
  // find the last pointer of the list to be sorted
  listOfObjects <TrainInfoPerStation *> * lastPtr = trainList[end/K];


  for(int i = 0; i < end % K; i++){
    lastPtr = lastPtr->next;
  }


  //finding the pivot
  int randPointer;
  int randPivot;
  if (N >= K){
    randPointer = (start / K) + (rand() % (N / K)); //choose a pointer from the list.

    randPivot = rand() % K; // advance atmost K steps at random to find the pivot

  } else {
    randPointer = (start / K); //handling the case when N < K

    randPivot = rand() % K;
  }
  
  if (K * randPointer + randPivot > end){
    randPointer = end / K; //if pivot choosen lies outside the list then choose the last pointer.
    randPivot = (end) % K;
  } else if (K * randPointer + randPivot < start){ //if pivot chosen lies before the list then choose the starting pointer.
    randPointer = start / K;
    randPivot = start % K;
  }

  listOfObjects<TrainInfoPerStation * > *pivot = trainList[randPointer]; //finding the pivot pointer

  while(pivot->next != nullptr && randPivot > 0){
    
    randPivot--;
    pivot = pivot->next;
    
  }

  swap(pivot, lastPtr); //swap values of the last pointer and the pivot;

  listOfObjects<TrainInfoPerStation *> pivot1 = *lastPtr;

  int front = start;
  int back = end;
  
  listOfObjects<TrainInfoPerStation *>* frontPtr = stnInfoList;
  
  //partitioning the list.
  while(front < back){ 
    //if front pointer less than pivot then move ahead
    if(!lessThan(&pivot1, frontPtr)){
        front++;
        frontPtr = frontPtr->next;
    //if lastPtr greater than the pivot then move behind
    } else if(lessThan(&pivot1, lastPtr)) {
        back--;
        lastPtr = lastPtr->prev;
    //otherwise swap values of the pointers.
    } else {
      //
      swap(frontPtr, lastPtr);
      front++;
      back--;
      frontPtr = frontPtr ->next;
      lastPtr = lastPtr -> prev;
    }
  }
  

  /*while (true){
    while(!lessThan(&pivot1, frontPtr) && frontPtr->next != nullptr){
      frontPtr = frontPtr->next;
      front++;
    }

    while(lessThan(lastPtr, &pivot1) && lastPtr->prev != nullptr){
      lastPtr = lastPtr->prev;
      back--;
    }

    if(front < back){
      swap(frontPtr, lastPtr);
      frontPtr = frontPtr->next;
      lastPtr = lastPtr->prev;
      front++;
      back--;
    } else {
      break;
    }
  
       
  }
*/




  // recursively keep on sorting the list.
  QuicksortSimple(stnInfoList, start, front-1);
  QuicksortSimple(lastPtr, back, end);   
  
  






  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
