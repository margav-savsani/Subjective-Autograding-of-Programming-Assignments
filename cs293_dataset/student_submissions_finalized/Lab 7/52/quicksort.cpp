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

// ASSUMPTION: Sorting is done on basis of arrival time
// If trains start from a station then arrival time will be -1 and it will be displayed before all other trains

// Takes main stnInfoList list, an array arr[] of pointers to some nodes in main list, index i, and K
// Returns pointer to the node at ith index
// This runs in O(K) time
listOfObjects<TrainInfoPerStation *> * getNode(
listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> ** arr, int i, int K
){
  int p = (i+1)/K;
  int q = (i+1)%K;
  listOfObjects<TrainInfoPerStation *> * curr;
  if(q == 0){ 
    curr = arr[p-1];  // O(1) time
    for (int j = 0; j < K-1; j++){  // O(K) time
      curr = curr->next;
    }
  }
  else{
    curr = arr[p];    // O(1) time
    for (int j = 0; j < q-1; j++){  // O(K) time
      curr = curr->next;
    }
  }
  
  return curr;
}

// Compares two given nodes
// Returns -1 if a is greater, 0 if equal, 1 if b is greater
int compare(listOfObjects<TrainInfoPerStation*>* a, listOfObjects<TrainInfoPerStation*>* b){
  int a_day = 0;
  int b_day = 0;
  // Get days of both
  while(true){
    if(!a->object->daysOfWeek[a_day]) a_day++;
    else break;
  }
  while(true){
    if(!b->object->daysOfWeek[b_day]) b_day++;
    else break;
  }
  
  if(a_day < b_day) return -1;
  else if(a_day > b_day) return 1;
  else{ // days equal then check arrival time
    if(a->object->arrTime < b->object->arrTime) return -1;
    else if(a->object->arrTime > b->object->arrTime) return 1;
    else return 0;
  }
}

// Swaps object contained inside the two given nodes
void swap(listOfObjects<TrainInfoPerStation*>* a, listOfObjects<TrainInfoPerStation*>* b){
  TrainInfoPerStation* temp = a->object;
  a->object = b->object;
  b->object = temp;
}

// Partition function for Quicksort
int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> ** arr, int start, int end, int K) 
{ 
  srand(time(NULL));
  int random = start + rand() % (end - start); // random index
  listOfObjects<TrainInfoPerStation*>* pivot = getNode(stnInfoList, arr, random, K);// get pivot in O(K) time

  // Make pivot the end node
  listOfObjects<TrainInfoPerStation*>* end_node = getNode(stnInfoList, arr, end, K);
  swap(pivot, end_node);
  pivot = end_node;

  // Vars for partitioning
  listOfObjects<TrainInfoPerStation*>* i = getNode(stnInfoList, arr, start, K);
  int i_index = start;
  listOfObjects<TrainInfoPerStation*>* j = i;
  // Partition loop
  for (int j_index = start; j_index <= end-1; j_index++){
    if (compare(j, pivot) != 1){ 
      swap(i, j); 
      i = i->next;
      i_index++;
    }
    j = j->next;
  }
  
  // Put pivot in its correct position
  swap(i, pivot);

  return i_index; 
} 


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int n;     // number of nodes in linked list
  static int start; // stores starting index of current iteration
  static int end;   // stores ending index of current iteration

  // Array of pointers of main list
  // all pointers are at K distance from each other and will store nodes at poistion 0, K, 2K ...
  // At max O(n/K) nodes will be stored in this array
  static listOfObjects<TrainInfoPerStation *> ** arr; 

  if(recursionLevel != -1 && start >= end) return;  // Base case

  // Increment recursion level on entering the function
  recursionLevel++;
  
  
  // Setup which runs only first time
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList
    n=0;
    for (listOfObjects<TrainInfoPerStation *> * i=stnInfoList; i != nullptr; i=i->next){
      n++;
    }
    start = 0;
    end = n-1;
    
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    if(n%K == 0){
      arr = new listOfObjects<TrainInfoPerStation *> *[n/K];
    }
    else{
      arr = new listOfObjects<TrainInfoPerStation *> *[n/K + 1];
    }

    // Store pointers at K distance
    int j=0;
    listOfObjects<TrainInfoPerStation *> * curr = stnInfoList;
    for(int i=0; i<n; i++){
      if(i % K == 0){
        arr[j] = curr;
        j++;
      }
      curr = curr->next;
    }
    
  }
  
  // Partition
  int pivot = partition(stnInfoList, arr, start, end, K); 
  int s = start;
  int e = end;
  
  // Quicksort sub lists
  end = pivot - 1;
  Quicksort(stnInfoList);
  end = e;

  start = pivot+1;
  Quicksort(stnInfoList);
  start = s;

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  if(start >= end) return;  // Base Case
  
  // A few static variable declarations
  static int K = 6; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int n;     // number of nodes in linked list

  // Array of pointers of main list
  // all pointers are at K distance from each other and will store nodes at poistion 0, K, 2K ...
  // At max O(n/K) nodes will be stored in this array
  static listOfObjects<TrainInfoPerStation *> ** arr;

  // Increment recursion level on entering the function
  recursionLevel++;
  
  // Setup which runs only first time
  if (recursionLevel == 0) {
    n = end - start + 1;

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    if(n%K == 0){
      arr = new listOfObjects<TrainInfoPerStation *> *[n/K];
    }
    else{
      arr = new listOfObjects<TrainInfoPerStation *> *[n/K + 1];
    }

    // Store pointers at K distance
    int j=0;
    listOfObjects<TrainInfoPerStation *> * curr = stnInfoList;
    for(int i=0; i<n; i++){
      if(i % K == 0){
        arr[j] = curr;
        j++;
      }
      curr = curr->next;
    }
    
  }
  
  // Partition
  int pivot = partition(stnInfoList, arr, start, end, K);

  // Quicksort sublists 
  QuicksortSimple(stnInfoList, start, pivot - 1); 
  QuicksortSimple(stnInfoList, pivot + 1, end);

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
