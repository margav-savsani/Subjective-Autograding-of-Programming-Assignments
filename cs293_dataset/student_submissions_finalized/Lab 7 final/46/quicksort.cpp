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

#include "time.h"

const int K = 4;

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  //static int K = 4; // Parameter to be experimented with
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

bool lessthan(listOfObjects<TrainInfoPerStation*>* a,listOfObjects<TrainInfoPerStation*>* b) {
  TrainInfoPerStation* t1 = (a->object);
  TrainInfoPerStation* t2 = (b->object);
  for(int i=0;i<7;i++) {
    if(t1->daysOfWeek[i] == 0 &&t2->daysOfWeek[i] != 0) { // if second train is available first
      return false;
    }
    else if (t1->daysOfWeek[i] != 0 &&t2->daysOfWeek[i] == 0) { // if first train is available first
      return true; 
    }
    else if(t1->daysOfWeek[i] == 1 &&t2->daysOfWeek[i] == 1) {  // both are available on the same day
                                                                // so, we are checking depTime
      if(t1->depTime < t2->depTime) {
        return true;
      }
      else if(t1->depTime > t2->depTime) {
        return false;
      }
      else if(t1->arrTime < t2->arrTime) { // if the depTime is null(it is a terminal)
        return true;
      }
    }
  }
  return true; // the program should not reach here, since there cant be 2 trains at the same time on same day
}

listOfObjects<TrainInfoPerStation*> *con(listOfObjects<TrainInfoPerStation*>** arr,int index) {

        int tmp = index/K;
        int tt = index%K; // always less than K
        listOfObjects<TrainInfoPerStation*> *curr;
        curr = arr[tmp];
        if(curr == nullptr) { // curr pointer cant be null anyways.
          return curr;
        }                
        while(tt!=0 and curr->next!=NULL) { // finding pivot in O(K)
          curr = curr->next;
          tt--;
        }
        return curr; // returning the pointer corresponding to the index given
}
void my_swap(listOfObjects<TrainInfoPerStation*>** arr,int i,int j) {

  if(i==j) return; // single element
  listOfObjects<TrainInfoPerStation*> *pivot = con(arr,i);
  listOfObjects<TrainInfoPerStation*> *end_ptr = con(arr,j);
  listOfObjects<TrainInfoPerStation*> piv_val = *pivot;
  listOfObjects<TrainInfoPerStation*> end_val = *end_ptr;
  // simple swaping mechanism
  TrainInfoPerStation p = *(pivot->object);
  TrainInfoPerStation e = *(end_ptr->object);
  *(pivot->object) = e;
  *(end_ptr->object) = p;
}
int rand_partition(listOfObjects<TrainInfoPerStation*>** arr,int start,int end,int piv) {

    my_swap(arr,piv,end); //moving pivot to the end for ease
    piv = end;  // updating pivot index

    listOfObjects<TrainInfoPerStation*> *pivot = con(arr,end);
    int i=(start-1);
  
    for (int j = start; j <= end - 1; j++) {
        listOfObjects<TrainInfoPerStation*> *curr = con(arr,j);
        if (lessthan(curr,pivot)) {
            i++; 
            my_swap(arr,i,j);
        }
    }
    my_swap(arr,i+1,end);
    return i+1; // correct position of pivot in sorted order
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  if(start>=end) return;

  // A few static variable declarations
 // static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation*>** arr;
  recursionLevel++;
  listOfObjects<TrainInfoPerStation *> *store;
  store = stnInfoList;
  
  if (recursionLevel == 0) { // first call to the function
    arr = new listOfObjects<TrainInfoPerStation*>* [(end-start+1)/K + 1];
    int cnt=0;
    for(int i=0;i<end-start+1;i++) {
      if(i%K==0) {
        arr[cnt] = store; // storing the pointers of those whose index is a multiple of K
        cnt++;
      }
      store = store->next; // traversing along the linked list
    }
  }
    int pivot = rand()%(end-start+1) + start;
    pivot = rand_partition(arr,start,end,pivot); 
    QuicksortSimple(stnInfoList,start,pivot-1);
    QuicksortSimple(stnInfoList,pivot+1,end);
    if(recursionLevel == 0) {
      recursionLevel = -1; // ending the main call
      return;
    }
  recursionLevel--; // for normal recursion
  return;
}

#endif
