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
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200

// Comparing the TrainInfoPerStation.
bool compareinfo(TrainInfoPerStation *first, TrainInfoPerStation *second)
{
  bool firstarrives = false;
  for (int i = 0; i < 7; i++)
  {
    if ((int(first->daysOfWeek[i]) + int(second->daysOfWeek[i])) == 1)
    { //When one of the train arrived first
      return (int(first->daysOfWeek[i]) > int(second->daysOfWeek[i]));
    }
    else if ((int(first->daysOfWeek[i]) + int(second->daysOfWeek[i])) == 2)
    { // Both the trains arrive on the same day in the station. 
      break;
    }
  }
  // Both the trains arrive on the same day.Hence we sort by the departure time.
  return (first->depTime < second->depTime);
}

// Swapping the contents of the nodes. i.e their TrainInfo pointers.
void swapcontent(listOfObjects<TrainInfoPerStation *> *first, listOfObjects<TrainInfoPerStation *> *second)
{
  //Swapping the pointers.
  swap(first->object, second->object);
}

//Normal Quicksort without using the parameters start and end.
//Basically this implements Quicksort by keeping start and end index as static variables.
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations

  //The array which will store the pointers of list elements.
  static listOfObjects<TrainInfoPerStation *>* *array = NULL;

  //Static variables start and end which will be changed before any recursion call.
  static int start = 0;
  static int end = 0;

  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Increment recursion level on entering the function
  recursionLevel++;

  if (recursionLevel == 0)
  { 
    // An iterator to calculate the length of the list.
    listOfObjects<TrainInfoPerStation *> *iterator = stnInfoList;
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    //Calculating the length of the array.
    int n = 0;
    while (iterator != NULL)
    {
      n++;
      iterator = iterator->next;
    }
    iterator = stnInfoList;
    int size = (n / K) + 1;
    array = new listOfObjects<TrainInfoPerStation *> *[size];
    //Storing array information.
    for (int i = 0; i < size; i++)
    {
      array[i] = iterator;
      if (i == size - 1)
      {
        break;
      }
      for (int i = 0; i < K; i++)
      {
        iterator = iterator->next;
      }
    }
    end = n-1;
  }

  //Base case when start>=end
  if(start >= end){
    recursionLevel--;
    return;
  }

  int index = rand() % (end - start + 1) + start; // return an index from 0 to size-1.

  ///**** FINDING THE PIVOT ****///
  listOfObjects<TrainInfoPerStation *> *pivot = array[index / K];
  for (int i = 0; i < (index % K); i++)
  { // Reaching the pivot index in O(k) time.
    pivot = pivot->next;
  }
  ///**** TIME COMPLEXITY iS O(n) since we preprocessed linked list pointers ****///
  
  //The last element in the linked list currently to be sorted.
  listOfObjects<TrainInfoPerStation *> *l = array[end/K];
  for (int i = 0; i < (end%K) ; i++)
  {
    l = l->next; // Making the pointer to its next
  }
  
  // Swapping content of pivot with the last.
  swapcontent(pivot, l);

  //comparator pointer of Traininfo to compare the objects
  TrainInfoPerStation *comparator = l->object;

  ///**** MAKING A PARTITION ***///
  // A lower iterator that finds the current element lower than the content of the pivot
  listOfObjects<TrainInfoPerStation *> *lower;  
  if (start == 0) //There is no element to the previous of the head of the list.
  {
    lower = NULL;
  }
  else 
  {
    //Else the current value of l is the previous element of the head of the list to be sorted.
    lower = stnInfoList->prev;
  }

  //The lower index from which we will split
  int lowerind = start - 1;
  for (listOfObjects<TrainInfoPerStation *> *j = stnInfoList; j != l; j = j->next)
  {
    if (!compareinfo(comparator, j->object))
    {
      lowerind = (lowerind == end + 1) ? start : lowerind + 1;
      lower = (lower == NULL) ? stnInfoList : lower->next;
      swapcontent(lower, j); //Swap contents.
    }
  }

  //If the lowerind becomes greater than the end this means the starting one is the smallest.
  lowerind = (lowerind == end + 1) ? start : lowerind + 1;

  //If the lower is NULL then make it stnInfoList
  lower = (lower == NULL) ? stnInfoList : lower->next;

  //Swap content of lower and l.
  swapcontent(lower, l);

  //Changing the static variables
  int currend = end;
  end = lowerind - 1;

  //Calling the function recursively
  Quicksort(stnInfoList);

  //Changing the static variables
  end = currend;
  currend =start;
  start = lowerind +1; 

  //Calling the function recursively
  Quicksort(lower->next);

  //Changing the static variables
  start = currend;
  
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

// SimpleQuicksort with start and end known
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // The array which will store exactly n/k pointers.
  if (start >= end)
  { // The base case for recursion
    return;
  }
  // A few static variable declarations

  //The array which will store the pointers of list elements.
  //Note that this array will be 
  static listOfObjects<TrainInfoPerStation *>* *array = NULL;

  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Increment recursion level on entering the function
  recursionLevel++;

  listOfObjects<TrainInfoPerStation *> *iterator = stnInfoList;
  if (recursionLevel == 0)
  {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    int n = 0;
    while (iterator != NULL)
    {
      n++;
      iterator = iterator->next;
    }
    iterator = stnInfoList;
    int size = (n / K) + 1;
    array = new listOfObjects<TrainInfoPerStation *> *[size];
    for (int i = 0; i < size; i++)
    {
      array[i] = iterator;
      if (i == size - 1)
      {
        break;
      }
      for (int j= 0; j < K; j++)
      {
        iterator = iterator->next;
      }
    }
  }
  int index = rand() % (end - start + 1) + start; // return an index from 0 to size-1.

  ///**** FINDING THE PIVOT ****///
  listOfObjects<TrainInfoPerStation *> *pivot = array[index / K];
  for (int i = 0; i < (index % K); i++)
  { // Reaching the pivot index in O(k) time.
    pivot = pivot->next;
  }
  ///**** TIME COMPLEXITY iS O(n) since we preprocessed linked list pointers ****///
  
  //The last element in the linked list currently to be sorted.
  listOfObjects<TrainInfoPerStation *> *l = array[end/K];
  for (int i = 0; i < (end%K) ; i++)
  {
    l = l->next; // Making the pointer to its next
  }
  
  // Swapping content of pivot with the last.
  swapcontent(pivot, l);

  //comparator pointer of Traininfo to compare the objects
  TrainInfoPerStation *comparator = l->object;

  ///**** MAKING A PARTITION ***///
  // A lower iterator that finds the current element lower than the content of the pivot
  listOfObjects<TrainInfoPerStation *> *lower;  
  if (start == 0) //There is no element to the previous of the head of the list.
  {
    lower = NULL;
  }
  else 
  {
    //Else the current value of l is the previous element of the head of the list to be sorted.
    lower = stnInfoList->prev;
  }

  //The lower index from which we will split
  int lowerind = start - 1;
  for (listOfObjects<TrainInfoPerStation *> *j = stnInfoList; j != l; j = j->next)
  {
    if (!compareinfo(comparator, j->object))
    {
      lowerind = (lowerind == end + 1) ? start : lowerind + 1;
      lower = (lower == NULL) ? stnInfoList : lower->next;
      swapcontent(lower, j);
    }
  }

  //If the lowerind becomes greater than the end this means the starting one is the smallest.
  lowerind = (lowerind == end + 1) ? start : lowerind + 1;

  //If the lower is NULL then make it stnInfoList
  lower = (lower == NULL) ? stnInfoList : lower->next;

  //Swap content of lower and l.
  swapcontent(lower, l);

  //Calling the function recursively
  QuicksortSimple(stnInfoList, start, lowerind - 1);
  QuicksortSimple(lower->next, lowerind + 1, end);

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
