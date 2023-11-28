#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP
#define llNode listOfObjects<TrainInfoPerStation *>
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

//helper function to compare objects at 2 llNodes
bool lessThan(llNode *lhs, llNode *rhs){
  //compare the days first
  for(int i = 0; i < 7; i++){
    if(!lhs->object->daysOfWeek[i] && rhs->object->daysOfWeek[i]){return false;}
    else if(lhs->object->daysOfWeek[i] && !rhs->object->daysOfWeek[i]){return true;}
  }
  //else return comparison by times
  return lhs->object->depTime < rhs->object->depTime;
}

//this function goes to a location in the linked list 'list' in O(K) using the markers array.
llNode *goTo(int idx, llNode *list, llNode **markers, int K){
  llNode *pivot;
  if(idx / K == 0) pivot = list;
  //nearest K-multiple in linked list stored in the array
  else pivot = markers[idx / K - 1];
  int x = K * (idx / K);
  while(x < idx){
    pivot = pivot->next;
    x++;
  }
  return pivot;
}

//to partition the array using the quicker goTo method
int partition(int start, int end, llNode *stnInfoList, llNode **markers, int K){
  int demarcation = -1;
  //for further calls
  int n = end - start + 1;
  if(n > 1){
    //generate random index between start and end (inclusive both)
    int pivot_idx = start + rand() % n;
    llNode *pivot = goTo(pivot_idx, stnInfoList, markers, K);
    llNode *left = goTo(start, stnInfoList, markers, K);
    int l_idx = start;
    llNode *right = goTo(end, stnInfoList, markers, K);
    int r_idx = end;

    while(l_idx < r_idx){
      //travel from both ends till discrepancy found
      while(lessThan(left, pivot)){
        left = left->next;
        l_idx++;
      }
      while(!lessThan(right, pivot) && r_idx > start){
        right = right->prev;
        r_idx--;
      }
      //swap the 2 
      if(l_idx < r_idx){
        TrainInfoPerStation temp = *(left->object);
        *(left->object) = *(right->object);
        *(right->object) = temp;
      }
    }
    //to reduce problem size
    if(l_idx == start){
      //swap minimum element / pivot with the left index
      TrainInfoPerStation temp = *(pivot->object);
      *(pivot->object) = *(left->object);
      *(left->object) = temp;
      left = left->next;
      l_idx++;
    }
    demarcation = l_idx;
  }
  //return 
  return demarcation;
}
//uses static ints instead of arguments
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int start, end;
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static llNode **markers;
  // Increment recursion level on entering the function
  recursionLevel++;
  if (recursionLevel == 0) {
    //cout << "yay" << endl;
    start = 0;
    //n is the number of objects in the linked list
    int n = 0;
    listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;
    while(curr != NULL){
    //n is the "index" of the curr TrainInfo object in the linked list.
      n++;
      curr = curr->next;
    }
    end = n - 1;
    markers = new listOfObjects<TrainInfoPerStation *> *[n / K];
    curr = stnInfoList;
    int i = 0;
    while(curr != NULL){
      if(i % K == 0 && i != 0) markers[i / K - 1] = curr;
      i++;
      curr = curr->next;
    }
  }
  //markers has the pointers to the linked list objects at indices: 
  // K, ... , floor(n / K) * K
  // Put your code for the core of Quicksort here
  // cout << markers << endl;
  int demarcation = partition(start, end, stnInfoList, markers, K);
  if(demarcation == -1){
    recursionLevel--;
    return;
  }

  int temp = end;
  end = demarcation - 1;
  Quicksort(stnInfoList);
  end = temp;
  temp = start;
  start = demarcation;
  Quicksort(stnInfoList);
  start = temp;
  // Decrement recursion level before leaving the function
  if(recursionLevel == 0) delete[] markers;
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static llNode **markers;
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
    int n = end - start + 1;
    markers = new listOfObjects<TrainInfoPerStation *> *[n / K];
    llNode *curr = stnInfoList;
    int i = 0;
    while(curr != NULL){
      if(i % K == 0 && i != 0) markers[i / K - 1] = curr;
      i++;
      curr = curr->next;
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  int demarcation = partition(start, end, stnInfoList, markers, K);
  if(demarcation == -1){
    recursionLevel--;
    return;
  }

  QuicksortSimple(stnInfoList, start, demarcation - 1);
  QuicksortSimple(stnInfoList, demarcation, end);
  // Decrement recursion level before leaving the function
  if(recursionLevel == 0) delete[] markers;
  recursionLevel--;
  return;
}

#endif
