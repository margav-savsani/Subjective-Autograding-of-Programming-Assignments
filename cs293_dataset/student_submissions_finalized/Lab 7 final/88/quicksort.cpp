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

#define K 4

// comparision function used in quicksort within partition function
bool isLessThan(listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right){
  for(int i=0;i<7;i++){ // comparing by day of departure
    if(left->object->daysOfWeek[i] && !(right->object->daysOfWeek[i])) return true;
    else if(!(left->object->daysOfWeek[i]) && right->object->daysOfWeek[i]) return false;
  }
  if(left->object->depTime<right->object->depTime) return true; // comparing by time of departure
  else return false;
}

// swaps the object stored within two pointers
void swap(listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right){
  TrainInfoPerStation *temp = right->object;
  right->object = left->object;
  left->object = temp;
}

// choose a random pivot within the range specified using N/K additional space and O(K) time
listOfObjects<TrainInfoPerStation *> *choosePivot(listOfObjects<TrainInfoPerStation *> **PivotList, int start, int end){
  int pivotindex=start+rand()%(end-start+1);
  listOfObjects<TrainInfoPerStation *> *pivot=PivotList[pivotindex/K];

  for(int i=0; i<pivotindex%K; i++){ // O(K) time
    pivot=pivot->next;
  }
  return pivot;
}

// function which partitions the linked list given the pivot to be used
listOfObjects<TrainInfoPerStation *> *Partition(listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right, listOfObjects<TrainInfoPerStation *> *pivot, int &mid){
  listOfObjects<TrainInfoPerStation *> pivot1(pivot->object);
  while(true){
    while(left!=right && isLessThan(left,&pivot1)){
      left=left->next;
      mid++;
    }
    while(left!=right && !isLessThan(right,&pivot1)){
      right=right->prev;
    }
    if(left!=right){
      swap(left,right);
    }
    else break;
  }
  return left;
}

// function which recursively performs quicksort
void recursiveQuicksort(listOfObjects<TrainInfoPerStation *> **PivotList, listOfObjects<TrainInfoPerStation *> *left, listOfObjects<TrainInfoPerStation *> *right, int start, int end)
{
  if(start>=end) return;
  listOfObjects<TrainInfoPerStation *> *temp_right=right;
  listOfObjects<TrainInfoPerStation *> *temp_left=left;
  int mid=start;
  listOfObjects<TrainInfoPerStation *> *pivot=choosePivot(PivotList, start, end);
  right=Partition(left, right, pivot, mid);
  recursiveQuicksort(PivotList, temp_left, right->prev, start, mid-1);
  recursiveQuicksort(PivotList, right, temp_right, mid, end);
}

// creates a pivot list taking N/K space, and calls recursivequicksort to sort the list
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  int n=0;
  listOfObjects<TrainInfoPerStation *> *temp=stnInfoList;
  if(temp!=nullptr){
    n=1;
    while(temp->next!=nullptr){
      n++;
      temp=temp->next;
    }
  }

  // generates a pivot list using N/K space
  listOfObjects<TrainInfoPerStation *> **PivotList=new listOfObjects<TrainInfoPerStation *>*[n/K]; // N/K additional space
  listOfObjects<TrainInfoPerStation *> *tempPivot=stnInfoList;
  for(int i=0; i*K<n; i++){
    PivotList[i]=tempPivot;
    for(int j=0; j<K && tempPivot!=nullptr; j++){
      tempPivot=tempPivot->next;
    }
  }

  recursiveQuicksort(PivotList, stnInfoList, temp, 0, n-1);
  delete[] PivotList;
}

// creates a pivot list taking N/K space, and calls recursivequicksort to sort the list
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end){
  int n=end+1;
  listOfObjects<TrainInfoPerStation *> *temp=stnInfoList;
  if(temp!=nullptr){
    while(temp->next!=nullptr){
      temp=temp->next;
    }
  }

  // generates a pivot list using N/K space
  listOfObjects<TrainInfoPerStation *> **PivotList=new listOfObjects<TrainInfoPerStation *>*[n/K]; // N/K additional space
  listOfObjects<TrainInfoPerStation *> *tempPivot=stnInfoList;
  for(int i=0; i*K<n; i++){
    PivotList[i]=tempPivot;
    for(int j=0; j<K && tempPivot!=nullptr; j++){
      tempPivot=tempPivot->next;
    }
  }
  recursiveQuicksort(PivotList, stnInfoList, temp, start, end);
  delete[] PivotList;
}
#endif