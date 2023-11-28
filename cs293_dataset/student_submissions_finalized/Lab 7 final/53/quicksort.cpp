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

int Planner::Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation *> *random_pivot)
{ 
  TrainInfoPerStation *random_train = random_pivot->object;//storing the object generated from random pivot
  //setting the rightmost pointer
  listOfObjects<TrainInfoPerStation *> *last_pointer = stnInfoList;

  for (int i = 0; i < end; i++)
  {
    last_pointer = last_pointer->next;
  }
  //setting the leftmost pointer
  listOfObjects<TrainInfoPerStation *> *first_pointer = stnInfoList;
  for (int i = 0; i < start; i++)
  {
    first_pointer = first_pointer->next;
  }
  //initialising the left and right parameters which would be traversing through the linked list
  int left = start - 1;
  listOfObjects<TrainInfoPerStation *> *left_pointer = new listOfObjects<TrainInfoPerStation *>(0);
  left_pointer->next = first_pointer;
  int right = end + 1;
  listOfObjects<TrainInfoPerStation *> *right_pointer = new listOfObjects<TrainInfoPerStation *>(0);
  right_pointer->prev = last_pointer;

  //Continue partitioning until done
  while (true)
  { //traversing one step in right through one iteration of do while
    bool move_on1 = false;
    do
    {
      right--; // traversing through array
      right_pointer = right_pointer->prev;
      int i = 0;
      //Comparing the right index value with the pivot value
      while (i < 7)
      {
        if ((random_train->daysOfWeek[i]) && !(right_pointer->object->daysOfWeek[i]))
        {
          // random_pivot has greater value in it
          move_on1 = true;
          break;
        }
        else if (!(random_train->daysOfWeek[i]) && (right_pointer->object->daysOfWeek[i]))
        {
          // right_pointer has greater value in it
          move_on1 = false;
          break;
        }
        else if ((random_train->daysOfWeek[i]) && (right_pointer->object->daysOfWeek[i]))
        {
          // if they are on the same day, compare on the basis of departure time
          if (random_train->depTime < right_pointer->object->depTime)
          {
            move_on1 = true;
            break;
          }
          move_on1 = false;
          break;
        }
        i++;
      }
    } while (
        (move_on1) && (!(right == start)) // second condition is only for sanity check and the first one is the actual comparison
    );
    //Implementing the same procedure for left index value
    bool move_on2 = false;
    do
    {
      left++; // traversing through array
      left_pointer = left_pointer->next;
      int i = 0;
      while (i < 7)
      {
        if (!(random_train->daysOfWeek[i]) && (left_pointer->object->daysOfWeek[i]))
        {
          move_on2 = true;
          break;
        }
        else if ((random_train->daysOfWeek[i]) && !(left_pointer->object->daysOfWeek[i]))
        {
          move_on2 = false;
          break;
        }
        else if ((random_train->daysOfWeek[i]) && (left_pointer->object->daysOfWeek[i]))
        {
          if (left_pointer->object->depTime < random_train->depTime)
          {
            move_on2 = true;
            break;
          }
          move_on2 = false;
          break;
        }
        i++;
      }

    } while (
        (move_on2) && (!(left == end)) // second condition is only for sanity check and the first one is the actual comparison
    );
    //now left and right index value are ready to be swaped if left < right
    if (left < right)
    { // swapping the left and right index objects

      TrainInfoPerStation *temp = left_pointer->object;
      left_pointer->object = right_pointer->object;
      right_pointer->object = temp;
    }
    else if (right == end)
      return right - 1;
    else
      return right;
  }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **random_gen;

  static int start;
  static int end;

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

  if (recursionLevel == 0)
  {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    start = 0;
    end = 0;
    listOfObjects<TrainInfoPerStation *> *i = stnInfoList;
    int count = 0;
    while (i != nullptr)
    {
      i = i->next;
      count++;
    }
    int k = 4;
    int ratio;
    if (count % k == 0)
      ratio = count / k;
    else
      ratio = count / k + 1;
    random_gen = new listOfObjects<TrainInfoPerStation *> *[ratio];
    int x = 0;
    listOfObjects<TrainInfoPerStation *> *currentNode = stnInfoList;
    for (int j = 0; j < count; j++)
    {
      if (j % k == 0)
      {
        random_gen[x] = currentNode;
        x++;
      }
      currentNode = currentNode->next;
    }
    listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
    while (currNode->next != nullptr)
    {
      currNode = currNode->next;
      end++;
    }
  }

  // Put your code for the core of Quicksorthere

  if (start >= end)
  {
    recursionLevel--;
    return;
  }
  
  int n1 = (start) / K;
  int n2 = (end) / K;
  int randNum1 = rand() % (n2 - n1 + 1) + n1;
  int randNum2;
  if (randNum1 == n1 && n1 != n2)
  {
    randNum2 = rand() % ((n1 + 1) * K - start + 1) + start - n1 * K;
  }
  else if (randNum1 == n2 && n1 != n2)
  {
    randNum2 = rand() % (end - K * n2 + 1);
  }
  else if (n1 == n2)
  {
    randNum2 = rand() % (end - start + K * (n1 - n2)) + start - n1 * K;
  }
  else
  {
    randNum2 = rand() % K;
  }
  listOfObjects<TrainInfoPerStation *> *random_pivot = random_gen[randNum1];
  while (randNum2--)
  {
    random_pivot = random_pivot->next;
  }

  int pivot = Partition(stnInfoList, start, end, random_pivot);
  int temp = end;
  end = pivot;
  Quicksort(stnInfoList);
  int temp2 = start;
  start = pivot + 1;
  end = temp;
  Quicksort(stnInfoList);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}


void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **random_gen;

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

  if (recursionLevel == 0)
  {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    // count will result in total length of the linked list
    listOfObjects<TrainInfoPerStation *> *i = stnInfoList;
    int count = 0; // length initialised to 0
    while (i != nullptr) // traversing the linked list
    {
      i = i->next;
      count++;
    }
    int k = K; // The parameter K
    int ratio; // This ratio determines the number of pointers to be stored in the preprocessed array

    // finding the value of ratio
    if (count % k == 0)
      ratio = count / k;
    else
      ratio = count / k + 1;
    
    //creating the array which will store the pointers placed in equal intervals of the parameter K

    random_gen = new listOfObjects<TrainInfoPerStation *> *[ratio];
    //x keeps the count of the index of the array
    int x = 0;
    listOfObjects<TrainInfoPerStation *> *currentNode = stnInfoList;
    for (int j = 0; j < count; j++) //traversing the linked list and storing only the pointers stored in equal intervals
    {
      if (j % k == 0)
      {
        random_gen[x] = currentNode;
        x++;
      }
      currentNode = currentNode->next;
    }
  }

  // Put your code for the core of QuicksortSimple here

  if (start >= end) // because the list would already be sorted
  {
    recursionLevel--;
    return;
  }
  
  //Generating a random pivot between the range start and end
  int n1 = (start) / K; // the floor function of start
  int n2 = (end) / K; // the floor function of end

  //randNum1 is the index of the array from which random pointer is generated
  int randNum1 = rand() % (n2 - n1 + 1) + n1;
  //randNum2 is the number of places which have to be traversed from the chosen pointer from array
  int randNum2;
  if (randNum1 == n1 && n1 != n2)
  {
    randNum2 = rand() % ((n1 + 1) * K - start + 1) + start - n1 * K;
  }
  else if (randNum1 == n2 && n1 != n2)
  {
    randNum2 = rand() % (end - K * n2 + 1);
  }
  else if (n1 == n2)
  {
    randNum2 = rand() % (end - start + K * (n1 - n2)) + start - n1 * K;
  }
  else
  {
    randNum2 = rand() % K;
  }
  listOfObjects<TrainInfoPerStation *> *random_pivot = random_gen[randNum1];
  while (randNum2--)
  {
    random_pivot = random_pivot->next;
  }

  //now calling the reccursive call
  int pivot = Partition(stnInfoList, start, end, random_pivot);
  QuicksortSimple(stnInfoList, start, pivot);
  QuicksortSimple(stnInfoList, pivot + 1, end);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
