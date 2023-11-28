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

#include<vector>
using namespace std;


bool Planner:: isEqual(TrainInfoPerStation* first, TrainInfoPerStation* second){
  bool flag = true;
  for (int i = 0; i<7;i++){
    if (first->daysOfWeek[i] != second->daysOfWeek[i]){
      flag = false;
      break;
    }
  }
   if (first->arrTime != second->arrTime){
      flag = false;
    }
    if (first->depTime != second->depTime){
      flag = false;
    }
  return flag;

}
bool Planner:: isGreater(TrainInfoPerStation* first, TrainInfoPerStation* second){
  
  for (int i = 0; i<7;i++){
    if (first->daysOfWeek[i] == true && second->daysOfWeek[i] == false){
      return false;
    }
    else if (second->daysOfWeek[i] == true && first->daysOfWeek[i] == false){
      return true;
    }
    else if (first->daysOfWeek[i] == true && second->daysOfWeek[i] == true){
      if (first->depTime != -1 && second->depTime!= -1){
        if (first->depTime != second->depTime){ // compare departure times
          return (first->depTime > second->depTime);
        }
        else {
          return (first->arrTime > second->arrTime); // compare using arrival times  if departure time is either equal or both -1
        }
      }
      else if (first->depTime == -1 && second->depTime == -1){ // compare arrival times if departure times are both -1
        return (first->arrTime > second->arrTime);
      }
      else if (first->depTime == -1){ // give the departure time -1 more priority
        return true;
      }
      else if (second->depTime == -1){
        return false;
      }
    }
  }
  return false;

}
// to swap two elements
void Planner:: swap(listOfObjects<TrainInfoPerStation *> *first, listOfObjects<TrainInfoPerStation *> *second){
    TrainInfoPerStation* temp = first->object;
    first->object = second->object;
    second->object = temp;
}

// Selects a pivot and partitions the linked list from head to tail node according to the pivot
int Planner:: partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start_, int end_, int K, vector<listOfObjects<TrainInfoPerStation *>* > pointerArray){
    if (stnInfoList == NULL){
      return -1;
    }
    if (start_ == end_){
      return start_;
    }
    int randNum = rand()%(end_ - start_ +1) + start_; 

  static listOfObjects<TrainInfoPerStation *> * randomPointer;
  static listOfObjects<TrainInfoPerStation *> * startNode;
  static listOfObjects<TrainInfoPerStation *> * endNode;

  // Selects a random pointer in the given linked list from start to end node
   randomPointer = pointerArray[0];

  // To set startNode to starting index node in the linked list
  startNode = pointerArray[start_/K];
  for (int i = 0; i<start_%K; i++){
    startNode = startNode->next;
  }
  // To set the pivot to the randNum index after the index of the randomPointer node
  randomPointer = pointerArray[randNum/K];
  for (int i = 0; i<randNum%K; i++){
    randomPointer = randomPointer->next;
  }

  // listOfObjects<TrainInfoPerStation *> * pivot = randomPointer;
  listOfObjects<TrainInfoPerStation *> pivotObject = randomPointer->object;
  // Pivot is set

  // To sort the linked list from start to end index based on the randomly chosen pivot
  

  // To set endNode to end index node in the linked list
  endNode = pointerArray[end_/K];
  for (int i = 0; i<end_%K; i++){
    endNode = endNode->next;
  }
  int j = end_;
  int i = start_;
  swap(randomPointer, endNode);
  
  while(true){
    while (isGreater(endNode->object, (&pivotObject)->object) && (i<j)) // WHAT SHOULD WE COMPARE
    { 
      endNode = endNode->prev;
      j--;
      
    }
    while (isGreater((&pivotObject)->object, startNode->object) && (i<j)){
      startNode = startNode->next;
      i++;

    }
    if (i<j){
      if (!isEqual(startNode->object, endNode->object)){
        swap(startNode, endNode);
      }
      else {
        j--;
      }
    }
    else{
      return j; // returns the index of the last element of the list which is smaller than the pivot
    }
  }
}

void Planner:: QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{ 
  if (stnInfoList == NULL){
    return;
  }
  if (start>=end){
    return;
  }
  // A few static variable declarations
  static int K = 2; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Stores the number of elements in the array
  static int numArrayElements = 0;
  static vector <listOfObjects<TrainInfoPerStation *>* > pointerArray;
  static int n = 0;

  // Increment recursion level on entering the function
  recursionLevel++;
  
  // Pre-processing step
  if (recursionLevel == 0) {
    // Counts the number of elements in the entire linked list - once only
    listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
    while(currNode!=NULL){
      n++;
      currNode = currNode->next;
    }
    numArrayElements = n/K;
    // array of pointers to n/k uniformly distributed nodes in the doubly linked list
    // Uniformly allocating pointers in the Original Linked List
    currNode = stnInfoList;
    for (int i = 0; i < n; i++) {
      if (i%K==0){
         pointerArray.push_back(currNode);
      }
      currNode = currNode->next;
    }
  }

  if (start<end){
    int pivot =  partition(stnInfoList, start, end, K, pointerArray);
    QuicksortSimple(stnInfoList, start, pivot-1);
    QuicksortSimple(stnInfoList, pivot+1, end);
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  if (recursionLevel==-1){
    n = 0; // DO NOT REMOVE
    pointerArray.clear();
  }
  return;
}
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  static int K = 2; 
  static int recursionLevel = -1;
  static int n_iterative = 0; // stores the size of the linked list
  static int low = 0;
  static int high = 0;
  static int numArrayElements = 0;
  static vector <listOfObjects<TrainInfoPerStation *>* > pointerArray;
  recursionLevel++;

    // Stack to store the start and end index of the linked list in which partition has to be done
    static vector<int> indices;
  
    if (recursionLevel == 0) {
    listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
    while(currNode!=NULL){
      n_iterative++;
      currNode = currNode->next;
    }
    numArrayElements = n_iterative/K;
    // array of pointers to n/k uniformly distributed nodes in the doubly linked list
    // Uniformly allocating pointers in the Original Linked List
    currNode = stnInfoList;
    for (int i = 0; i < n_iterative; i++) {
      if (i%K==0){
         pointerArray.push_back(currNode);
      }
      currNode = currNode->next;
    }
  }
    // push initial values of indices into the stack
    indices.push_back(0);
    indices.push_back(n_iterative-1);
 
    // Keep popping from stack while is not empty
    while (indices.size() >= 2) {
        // Pop high and low values of indices
        high = indices[indices.size() - 1];
        indices.pop_back();
        low = indices[indices.size() - 1];
        indices.pop_back();
        // partition according to the lattest low and high indices in the stack
        int pivot = partition(stnInfoList, low, high, K, pointerArray);
        // push the border indices of the left part
        if (pivot - 1 > low) {
            indices.push_back(low);
            indices.push_back(pivot-1);
        }
        // push the border indices of the right part
        if (pivot + 1 < high) {
            indices.push_back(pivot+1);
            indices.push_back(high);
        }
    }
  recursionLevel--;
  if (recursionLevel==-1){
    indices.clear();
    n_iterative = 0;
    pointerArray.clear();
  }
  return;
}
#endif
