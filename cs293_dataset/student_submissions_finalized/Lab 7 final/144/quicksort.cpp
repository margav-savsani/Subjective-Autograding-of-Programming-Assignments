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


//Given every kth element in linked list, find a given element in O(k) time
listOfObjects<TrainInfoPerStation *> *getPtr(int index, int k, listOfObjects<TrainInfoPerStation*>** arrayTrainPointers){
  listOfObjects<TrainInfoPerStation *> *currPtr = arrayTrainPointers[int(index / k)]; // Pointer to start from

  for(int i = 0; i < index % k; i++){
    //Number of times to move forward
    currPtr = currPtr->next;
  }

  return currPtr;
}

//Swaps objects in two nodes
void myswap(listOfObjects<TrainInfoPerStation *> *Node1, listOfObjects<TrainInfoPerStation *> *Node2){
  TrainInfoPerStation* temp = Node1->object;
  Node1->object = Node2->object;
  Node2->object = temp;
}
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

//Less Than operator for two train infos based on departure time
bool lessThan(TrainInfoPerStation* train1, TrainInfoPerStation* train2){
  int day_train1, day_train2, dept_train1, dept_train2;
  for (int i = 6; i >= 0; i--){
    if(train1->daysOfWeek[i]){
      day_train1 = i;
    }

    if(train2->daysOfWeek[i]){
      day_train2 = i;
    }
  }

  //If departure time is -1, it is to be placed last in list
  train1->depTime == -1 ? dept_train1 = 2500*8: dept_train1 = train1->depTime;
  train2->depTime == -1 ? dept_train2 = 2500*8: dept_train2 = train2->depTime;
  return (2500*day_train1 + dept_train1 < 2500*day_train2 + dept_train2);
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;

  //Store values during pre processing
  static listOfObjects<TrainInfoPerStation*>** arrayTrainPointers; // N/K pointers, one for every kth pointer
  static int start; //First index of list to be sorted
  static int end; //Last index of list to be sorted
  static int len; //Complete length of list
  
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

    //Find len of list
    len = 1;
    listOfObjects<TrainInfoPerStation *> *currPtr = stnInfoList;
    while(currPtr->next != nullptr){
      len++;
      currPtr = currPtr->next;
    }
    //Initialise start and end
    start = 0;
    end = len - 1;

    //Construct the array of pointers
    arrayTrainPointers = new listOfObjects<TrainInfoPerStation*>*[int(len / K) + 1];
    int index = 0;
    currPtr = stnInfoList;

    for(int i = 0; i < len; i++){
      if(i%K == 0){
        //Store every Kth pointer
        arrayTrainPointers[index] = currPtr;
        index++;
      }
      currPtr = currPtr->next;
    }

  }

  // Put your code for the core of Quicksort here
  if(start < end){
    //Choose a pivot
    int randindex = start + rand()%(end - start + 1);
    listOfObjects<TrainInfoPerStation *> *randomPivot = getPtr(randindex, K, arrayTrainPointers);
    //Partition
    listOfObjects<TrainInfoPerStation *> *endPivot = getPtr(end, K, arrayTrainPointers);
    myswap(randomPivot, endPivot);  //Swap random pivot with last
    int i = start - 1;

    //Partition all nodes with values less than pivot to left of pivot
    for(int j = start; j < end; j++){
        if(lessThan(getPtr(j, K, arrayTrainPointers)->object, getPtr(end, K, arrayTrainPointers)->object)){
          i++;
          myswap(getPtr(j, K, arrayTrainPointers), getPtr(i, K, arrayTrainPointers));
        }
    }

    //Put pivot in correct position
    i++;
    myswap(getPtr(i, K, arrayTrainPointers), getPtr(end, K, arrayTrainPointers));
    
    //Change values of start and end for first recursion
    int temp_end = end;
    end = i - 1;
    Quicksort(getPtr(start, K, arrayTrainPointers));

    //Change values of start and end for first recursion
    start = i + 1;
    end = temp_end;
    Quicksort(getPtr(start, K, arrayTrainPointers));
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;

  if(recursionLevel == -1){
    //Free memory
    delete[] arrayTrainPointers;
  }
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{

  return;
}

#endif
