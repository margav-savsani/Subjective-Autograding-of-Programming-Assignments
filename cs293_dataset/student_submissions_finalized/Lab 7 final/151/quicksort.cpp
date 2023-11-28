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



// used for accessing elements of the listOfObjects
listOfObjects<TrainInfoPerStation *>* accessElement(int index, listOfObjects<TrainInfoPerStation *>** array, int K){
  listOfObjects<TrainInfoPerStation *>* currElm = array[index / K];

  for(int i = 0; i < index % K; i++){
    currElm = currElm->next;
  }

  return currElm;
}

// comparison function used inside quicksort
bool lessThan(TrainInfoPerStation* train1, TrainInfoPerStation* train2){
  for(int i = 0; i < 7; i++){
    if(train1->daysOfWeek[i] && !train2->daysOfWeek[i])
      return true;
    else if(!train1->daysOfWeek[i] && train2->daysOfWeek[i])
      return false;
    else if(train1->daysOfWeek[i] && train2->daysOfWeek[i]){
      if(train1->depTime < train2->depTime) return true;
      else return false;
    }
  }
  return false;
}

// swapping function used inside quicksort
void swap(listOfObjects<TrainInfoPerStation *>* train1, listOfObjects<TrainInfoPerStation *>* train2){
  TrainInfoPerStation* tempTrain = train1->object;
  train1->object = train2->object;
  train2->object = tempTrain;
}

// partition function for quicksort
int Planner::PartitionFunc(int start, int end, listOfObjects<TrainInfoPerStation *>** kthElements, int K){


  int length = end - start + 1;
  
  int pivotIndex = start + (rand() % length);
  if(pivotIndex == 0) pivotIndex = 1;
  listOfObjects<TrainInfoPerStation *>* pivotElement = accessElement(pivotIndex, kthElements, K);
  listOfObjects<TrainInfoPerStation *>* lastElement = accessElement(end, kthElements, K);

  // swapping of random element with last element
  swap(pivotElement->object, lastElement->object);
  pivotElement = accessElement(end, kthElements, K);

  listOfObjects<TrainInfoPerStation *>* currElement = accessElement(start, kthElements, K);
  listOfObjects<TrainInfoPerStation *>* pivotPos = currElement->prev;


  // main quicksort procedure

  int i = start - 1;

  if(end - start == 1){
    if(lessThan(currElement->object, pivotElement->object)){
      return end;
    } else {
      swap(currElement, pivotElement);
      return end;
    }
  }


  for(int j = start; j <= end - 1; j++){

    if(lessThan(currElement->object, pivotElement->object)){
      i++;
      pivotPos = accessElement(i, kthElements, K);
      swap(pivotPos, currElement);
    }

    currElement = currElement->next;
  }
  swap(pivotPos->next, pivotElement);
  

  //returns index of the pivot
  return i + 1;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *>** kthElements = nullptr;
  static int noElmInSubArray = (end - start + 1) % K == 0 ? (end - start + 1) / K : (end - start + 1) / K + 1;

  // Increment recursion level on entering the function
  recursionLevel++;
  
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    int length = (end - start) + 1;


    // declaration of the k elements of subarray
    kthElements = new listOfObjects<TrainInfoPerStation *>*[K];
    listOfObjects<TrainInfoPerStation *>* currTrain = stnInfoList;
    for(int i = 0; i < K; i++){
      kthElements[i] = currTrain;
      for (int j = 0; j < noElmInSubArray; j++){
        if(currTrain->next == nullptr) break;
        currTrain = currTrain->next;
      }
    }
  }
  


  if(start < end){
    int index = PartitionFunc(start, end, kthElements, noElmInSubArray);
    
    QuicksortSimple(stnInfoList, start, index - 1);
    QuicksortSimple(stnInfoList, index+1, end);

  }
  // Decrement recursion level before leaving the function
  recursionLevel--;

  
  return;
}





#endif
