#include <time.h>
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

int dayOfNode(listOfObjects<TrainInfoPerStation*>* node){

  int dayOfPivot = 0;
  for (int i = 0; i < 7; i++)
  {
    if (node->object->daysOfWeek[i])
    {
      dayOfPivot = i;
      return dayOfPivot;

    }   
  }
  return -1;
}

int timeOfNode(listOfObjects<TrainInfoPerStation*>* node){
  return node->object->depTime;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
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
    // Put your code here.

  //Finding Pivot

  //Initialising last and pivot node 
  listOfObjects<TrainInfoPerStation *> *last = new listOfObjects<TrainInfoPerStation *>(nullptr);
  listOfObjects<TrainInfoPerStation *> *pivot = new listOfObjects<TrainInfoPerStation*>(nullptr);
  //Finding length of list
  int len = 0;
  listOfObjects<TrainInfoPerStation *> *node = stnInfoList;
  while (node != nullptr)
  {
    len++;
    last = node;
    node = node->next;
  }

  int pivotpos = len*rand()/RAND_MAX;
  for (int i = 0; i < pivotpos; i++)
  {
    if (pivot == nullptr)
    {
      pivot = stnInfoList;
    }
    pivot = pivot->next;
  }
  
  //Pivot found.. Now we do quicksort
  //We shift greater ones to last and lesser will be in their posn
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

// We will first partiton list into K parts, and each will have its own head. We will store it in an array and find some random pivot position.
// We find nearest head position and get to pivot position in O(k) time. Space taken is O(n/k).

// Now we go through the linked list keeping in mind the pivot position. Before crossing, if node value is lesser than pivot value, we will keep it here, else we add it to last node.
// After crossing, we shift lesser ones to start and leave greater ones.

// Finally, we get all nodes lesser to left and right ones are greater, same as quicksort.
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{ 
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;

  if (((end - start) > 0) && (stnInfoList != nullptr))
  {
  //size of list input
  int size = end - start + 1; //size is of list inserted
  //length of first array
  static int length; //length of original list
  // array of K heads
  static listOfObjects<TrainInfoPerStation*>** arr; 
  
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
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    length = end - start + 1;
    arr = new listOfObjects<TrainInfoPerStation*>*[int(length/K) + 1];
  }

    listOfObjects<TrainInfoPerStation*>* node1 = stnInfoList;
    listOfObjects<TrainInfoPerStation*>* node2 = stnInfoList;
    //Assigning node heads to array 
    int i = 0;
    for (int i = 0; (i < size && node2->next != nullptr); i++)   
    {
      if(i%K == 0){
        arr[int(i/K)] = node2;
       }
      node2 = node2->next;
      i++;
    }
  
  // Put your code for the core of QuicksortSimple here

  //Choosing pivot
  listOfObjects<TrainInfoPerStation*>* pivot;
  srand(time(0));
  int pivotpos = rand()%size;
    //Finding pivot
    int a = pivotpos/K;
    int b = pivotpos%K;
    pivot = arr[a];
    for (int i = 0; i < b ; i++)
    {
      if(pivot->next != nullptr){
        pivot = pivot->next;
      }

    } 

  //Quicksorting list

  listOfObjects<TrainInfoPerStation *> *last = new listOfObjects<TrainInfoPerStation *>(nullptr);
  listOfObjects<TrainInfoPerStation *> *first = stnInfoList;
  //Finding last pivot
  {
    listOfObjects<TrainInfoPerStation *> *node = stnInfoList;
    for (int i = 0; i < size; i++)
    {
      if (node->next != nullptr)
      {
        last = node;
        node = node->next;
      }
    }  
  }
  listOfObjects<TrainInfoPerStation*>* node = stnInfoList;
  bool crossed = false; //If pivot is crossed, then it is true
  int dayOfPivot = dayOfNode(pivot);
  int timeOfPivot = timeOfNode(pivot);
  //Checks if pivot is crossed, if crossed, check value of node. If node < pivot, send it back of pivot. Opposite if pivot is not passed
  for (int i = 0; (i < size && node != nullptr); i++)
  {
    int day = dayOfNode(node);
    int time = timeOfNode(node);
    listOfObjects<TrainInfoPerStation*>* newnode = node->next;
    //Crossing pivot
    if (day == dayOfPivot && time == timeOfPivot)
    {
      crossed = true;
    }
    //If pivot is crossed, if node lesser than pivot, bring it to start
    else if(crossed){
      if (day < dayOfPivot)
      {
        //Removing node from its position
        if(node->next == nullptr){
          last = node->prev;
        }
        else{  
          node->next->prev = node->prev;
        }
        node->next = first;
        first->prev = node;
        node->prev = nullptr;
        first = node;
        pivotpos++;
      }
      else if (day == dayOfPivot && time < timeOfPivot)
      {
        //Removing node from its position
        if(node->next == nullptr){
          break;
        }
        else{  
          node->next->prev = node->prev;
        }
        node->next = first;
        first->prev = node;
        node->prev = nullptr;
        first = node;
        pivotpos++;
      }  
    }
    //before pivot, if pivot is greater, bring it to end
    else
    {
      if (day > dayOfPivot)
      {
        //Removing node from its position
        if(node->prev == nullptr){
          first = node->next;
        }
        else{
          node->prev->next = node->next;
        }
        node->prev = last;
        last->next = node;
        node->next = nullptr;
        last = node;
        pivotpos -= 1;
      }
      else if (day == dayOfPivot && time > timeOfPivot){
        //Removing node from its position
        if(node->prev == nullptr){
          first = node->next;  
        }
        else{
        node->prev->next = node->next;
        }
        node->prev = last;
        last->next = node;
        node->next = nullptr;
        last = node;
        pivotpos -= 1;
      }  
    }
    node = newnode;
  }
  listOfObjects<TrainInfoPerStation*>* point = first;
  if (pivotpos > 0)
  {
    QuicksortSimple(point,start,start + pivotpos-1);
  }
  QuicksortSimple(pivot->next,start+pivotpos+1,end);
  listOfObjects<TrainInfoPerStation*>* nodal = pivot;
  while (nodal->prev != nullptr)
  {
    nodal = nodal->prev;  
  }
  //Reassigning stnInfoList to first node
  stnInfoList = nodal;
  // Decrement recursion level before leaving the function
}
  recursionLevel--;
  return;
}

#endif
