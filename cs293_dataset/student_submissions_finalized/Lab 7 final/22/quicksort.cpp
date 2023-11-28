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
// TrainInfoPerStation objects that is to be -sorted. In the updated
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

bool isLessThan(listOfObjects<TrainInfoPerStation *> *A, listOfObjects<TrainInfoPerStation *> *B)
{
  
  for (int i = 0; i < 7; i++) //Check for each day.
  {
    if (A->object->daysOfWeek[i])
    {
      if (!B->object->daysOfWeek[i])//A travels earlier than B
        return true;
      else
      {
        if (A->object->depTime < B->object->depTime) //A travels earlier on Same day than B.
          return true;
        else
          return false;
      }
    }
    else
    {
      if (B->object->daysOfWeek[i]) //B travels earlier than A.
        return false;
    }
    //Check next day if both trains dont travel on the current day.
  }

  return false;
}

void swap(listOfObjects<TrainInfoPerStation *> *A, listOfObjects<TrainInfoPerStation *> *B)
{
  //Swaps the object stored in node A and B.
  
  int tmp = A->object->arrTime;
  A->object->arrTime = B->object->arrTime;
  B->object->arrTime = tmp;

  for (int i = 0; i < 7; i++)
  {
    bool tmp = A->object->daysOfWeek[i];
    A->object->daysOfWeek[i] = B->object->daysOfWeek[i];
    B->object->daysOfWeek[i] = tmp;
  }

  tmp = A->object->depTime;
  A->object->depTime = B->object->depTime;
  B->object->depTime = tmp;

  tmp = A->object->journeyCode;
  A->object->journeyCode = B->object->journeyCode;
  B->object->journeyCode = tmp;

  unsigned short x = A->object->stopSeq;
  A->object->stopSeq = B->object->stopSeq;
  B->object->stopSeq = x;
  return;
}

int partition_function(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end, listOfObjects<TrainInfoPerStation *> **stPointers, int K)
{
  /*
    A modified implementation of Quicksort as taught by Naveen sir, to sort linked lists.
  */


  int partitioner = start + (std::rand() % (end - start + 1)); //Random pivot
  int pIndex = partitioner / K, ptravLen = partitioner % K; //Used to get to pivot in O(K) time.
  int sIndex = start / K, stravLen = start % K; //Used to get startNode in O(K) time.
  int eIndex = end / K, etravLen = end % K; //Used to get endNode in O(K) time.

  listOfObjects<TrainInfoPerStation *> *startNode, *endNode, *partitionNode; //Required nodes.

  listOfObjects<TrainInfoPerStation *> *tmp = stPointers[sIndex];
  //Getting startNode
  for (int j = 0; j < stravLen; j++)
  {
    if (tmp->next == nullptr)
      break;

    tmp = tmp->next;
  }
  startNode = tmp;

  tmp = stPointers[eIndex];

  //Getting endNode
  for (int j = 0; j < etravLen; j++)
  {
    if (tmp->next == nullptr)
      break;

    tmp = tmp->next;
  }
  endNode = tmp;

  tmp = stPointers[pIndex];
  //getting pivot.
  for (int j = 0; j < ptravLen; j++)
  {
    if (tmp->next == nullptr)
      break;

    tmp = tmp->next;
  }
  partitionNode = tmp;

  int startIndex = sIndex * K + stravLen, endIndex = eIndex * K + etravLen; //Indices as in virtual array.

  while (true)
  {
    while (isLessThan(startNode, partitionNode)) //We traverse linked list until we get an object which should come after pivot.
    {
      if (startNode->next == nullptr) //In case we reach the end, to prevent errors.
        break;
      startNode = startNode->next;
      startIndex++; //Moving to next node in linked list is equivalent to moving to next index in our virtual array.
      
    }

    while (isLessThan(partitionNode, endNode))//We reverse traverse linked list until we get an object which should come before pivot.
    {
      if (endNode->prev == nullptr)//In case we reach the end, to prevent errors.
        break;
      endNode = endNode->prev;

      endIndex--;//Moving to prev node in linked list is equivalent to moving to prev index in our virtual array.
      
    }

    if (startIndex < endIndex) //If (greater than pivot) object is before (less than pivot)swap them.
    {
      swap(startNode, endNode);
    }

    else //No more swaps possible, return partition index.
      return endIndex;
  }

  return 0;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int start = 0; //These act as the start and end indices of virtual array.
  static int end;


  // Increment recursion level on entering the function
  recursionLevel++;

  static listOfObjects<TrainInfoPerStation*> *(*stPointers);//Array of pointers.


  if(start > end)//start MUST be less than or equal to end
  {
    recursionLevel--;
    return;
  }

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
    int n = 0;//size of linked list.
    listOfObjects<TrainInfoPerStation *> *tmp = stnInfoList;

    //Calculating size of linked list.
    while (tmp != nullptr)
    {
      tmp = (*tmp).next;

      n++;
    }

    end = n-1;//In first call, end is initialized to size of linked list.

    tmp = stnInfoList;

    /*Creating an array of pointers to nodes.
      This enables us to traverse through the linked list in an efficient manner(Time to reach any node is max O(K))
      We divide the linked list into groups of size K, and store the pointer to the head of groups in this array.
      Since we divide into size of K, if n is multiple of K, we get n/K groups.
      If n is not multiple of K, some remainder is left. These are the remaining nodes not in a group. Hence we create an extra group for them.
      Thus, total groups = n/K +1
    */
    if (n % K == 0)
      stPointers = new listOfObjects<TrainInfoPerStation *> *[n / K];
    else
      stPointers = (listOfObjects<TrainInfoPerStation *> **)malloc((n / K + 1) * sizeof(listOfObjects<TrainInfoPerStation *> *));

    //Filling the array of pointers.
    for (int i = 0, j = 0; tmp != nullptr; i++)
    {

      if (i % (K) == 0)
      {
        stPointers[j] = tmp;
        tmp = tmp->next;
        j++;
      }
      else
        tmp = tmp->next;
    }
    //Calling partition function to sort the linked list and get partition index.
    int partitioner = partition_function(stnInfoList, start, end, stPointers, K);

    //Storing the TRUE start and end values.
    int tmpStart = start, tmpEnd = end;

    //For recursion on first partition of linked list.(start, partitioner-1 in our virtual array).
    end = partitioner-1;

    //Now start = start and end = partitioner-1 are passed in Quicksort call.
    Quicksort(stnInfoList);

    //Restoring end to true value.
    end = tmpEnd;

    //For recursion on second partition of linked list.(partitioner+1, end in our virtual array).
    start = partitioner+1;
    //Now start = partitioner+1 and end = end are passed in Quicksort call.
      Quicksort(stnInfoList);

      //Restoring start to true value.
      start = tmpStart;
    
    
    recursionLevel--;
    return;
   
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  //Calling partition function to sort the linked list and get partition index.
  int partitioner = partition_function(stnInfoList, start, end, stPointers, K);

  //Storing the TRUE start and end values.
  int tmpStart = start, tmpEnd = end;

  //For recursion on first partition of linked list.(start, partitioner-1 in our virtual array).
    end = partitioner-1;

    //Now start = start and end = partitioner-1 are passed in Quicksort call.
    Quicksort(stnInfoList);

    //Restoring end to true value.
    end = tmpEnd;

    //For recursion on second partition of linked list.(partitioner+1, end in our virtual array).
    start = partitioner+1;

    //Now start = partitioner+1 and end = end are passed in Quicksort call.
      Quicksort(stnInfoList);

      //Restoring start to true value.
      start = tmpStart;
  

  // Put your code for the core of Quicksort here

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

  // Increment recursion level on entering the function
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation*> *(*stPointers); //Array of pointers.


  if(start > end) //start MUST be less than or equal to end.
  {
    recursionLevel--;
    return;
  }
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

  if (recursionLevel == 0) //First call.
  {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    int n = 0;//size of linked list.
    listOfObjects<TrainInfoPerStation *> *tmp = stnInfoList; 

    //Calculating size of linked list
    while (tmp != nullptr)
    {
      tmp = (*tmp).next;

      n++;
    }
    tmp = stnInfoList;

    /*Creating an array of pointers to nodes.
      This enables us to traverse through the linked list in an efficient manner(Time to reach any node is max O(K))
      We divide the linked list into groups of size K, and store the pointer to the head of groups in this array.
      Since we divide into size of K, if n is multiple of K, we get n/K groups.
      If n is not multiple of K, some remainder is left. These are the remaining nodes not in a group. Hence we create an extra group for them.
      Thus, total groups = n/K +1
    */
    
    if (n % K == 0)
      stPointers = new listOfObjects<TrainInfoPerStation *> *[n / K];
    else
      stPointers = (listOfObjects<TrainInfoPerStation *> **)malloc((n / K + 1) * sizeof(listOfObjects<TrainInfoPerStation *> *));

    //Filling the array of pointers.
    for (int i = 0, j = 0; tmp != nullptr; i++)
    {

      if (i % (K) == 0)
      {
        stPointers[j] = tmp;
        tmp = tmp->next;
        j++;
      }
      else
        tmp = tmp->next;
    }

    //Calling the partition function to sort the array and get partition index.
    int partitioner = partition_function(stnInfoList, start, end, stPointers, K);

      //Recursion.
      QuicksortSimple(stnInfoList, start, partitioner-1);
      QuicksortSimple(stnInfoList, partitioner + 1, end);
    

    recursionLevel--;
    return;
  }
  //Calling the partition function to sort the array and get partition index.
  int partitioner = partition_function(stnInfoList, start, end, stPointers, K);
    
    //Recursion
    QuicksortSimple(stnInfoList, start, partitioner-1);
    QuicksortSimple(stnInfoList, partitioner + 1, end);
  

  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
