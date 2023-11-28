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

/// @brief function aiding the comparision of two traininfoperstation objects
/// @param a a TrainInfoPerStation Object
/// @return day*2400 + arrival time at that station
int value(TrainInfoPerStation *a)
{
  for (int i = 0; i < 7; i++)
  {
    if (a->daysOfWeek[i])
    {
      return i * 2400 + a->arrTime;
    }
  }
}

/// @brief comparing two TrainInfoPerStation objects to be used in quicksort
/// @param a the first object to be compared
/// @param b the second object to be compared
/// @return true if a <= b else false
bool compare(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
  return (value(a->object) <= value(b->object));
}

/// @brief Partition function of the quicksort. It is called with thw pivot at the end. The function then sorts the list in such a way that all elements to the left of it are less than or equal to pivot and all elements to the right are greater than pivot.
/// @param first starting point of the list
/// @param last end point of the node, it contains the random pivot.
/// @return the index of the pivot after sorting accordingly
int Partition(listOfObjects<TrainInfoPerStation *> *first, listOfObjects<TrainInfoPerStation *> *last)
{
  int x = -1;
  listOfObjects<TrainInfoPerStation *> *i = first->prev;
  listOfObjects<TrainInfoPerStation *> *j;
  for (j = first; j != last; j = j->next)
  {
    if (compare(j, last))
    {
      i = (i == NULL) ? first : i->next;
      x++;
      swap(*i->object, *j->object);
    }
  }
  i = (i == NULL) ? first : i->next;
  x++;
  swap(*i->object, *last->object);
  return x;
}

/// @brief It sorts the function with just one argument, i.e., the list. The function actually stores the value of the first and last element in static variables and uses it to find the first and last node for any recursive call.
/// @param stnInfoList The list to be sorted
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
 
  static int start; // static variable to store the start point
  static int end; // static variable to store the end point
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation *> **info; // array to store n/K list objects

  // in the following block, info, start and end are initialised
  if (recursionLevel == 0)
  {
    int n = 0;
    listOfObjects<TrainInfoPerStation *> *currnode = stnInfoList;
    while (currnode != nullptr)
    {
      currnode = currnode->next;
      n++;
    }
    start = 0;
    end = n - 1;
    info = new listOfObjects<TrainInfoPerStation *> *[(n / K) + 1];
    currnode = stnInfoList;
    for (int i = 0; i < n; i++)
    {
      if (i % K == 0)
      {
        info[i / K] = currnode;
      }
      currnode = currnode->next;
    }
  }

  // at any point if start exceeds end, return the function
  if (start >= end)
  {
    recursionLevel--;
    return;
  }

  // in the following block, random pivot is generated and passed on to partition function. Then before calling quicksort again, start and end variables for current call of the function is stored in variables so that they can be used later, as start and end static varible might be modified at a later call.
  if (start < end)
  {
    srand(time(0));
    int x = rand() % (end - start + 1) + start;
    listOfObjects<TrainInfoPerStation *> *pivot;
    pivot = info[x / K];
    for (int i = 0; i < x % K; i++)
    {
      pivot = pivot->next;
    }
    listOfObjects<TrainInfoPerStation *> *first = info[start / K];
    listOfObjects<TrainInfoPerStation *> *last = info[end / K];
    for (int i = 0; i < start % K; i++)
    {
      first = first->next;
    }
    for (int i = 0; i < end % K; i++)
    {
      last = last->next;
    }
    swap(*pivot->object, *last->object);
    x = Partition(first, last);
    int s = start, e = end;
    start = s;
    end = x + s - 1;
    Quicksort(stnInfoList);

    start = x + s + 1;
    end = e;
    Quicksort(stnInfoList);
  }
  recursionLevel--;
  return;
}

/// @brief QuicksortSimple is much similar to the previous Quicksort function, except the fact that instead of using static variables for storing start and end, start and end are passed to the function. Hence all other comments are also same :) Trust me I have copied the same code to Quicksort.
/// @param stnInfoList the list to be sorted
/// @param start start index of the list
/// @param end end index of the list
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation *> **info;

  if (start >= end)
  {
    recursionLevel--;
    return;
  }

  if (recursionLevel == 0)
  {
    int n = end - start + 1;
    info = new listOfObjects<TrainInfoPerStation *> *[(n / K) + 1];
    listOfObjects<TrainInfoPerStation *> *currnode = stnInfoList;
    for (int i = 0; i < n; i++)
    {
      if (i % K == 0)
      {
        info[i / K] = currnode;
      }
      currnode = currnode->next;
    }
  }

  if (start < end)
  {
    srand(time(0));
    int x = rand() % (end - start + 1) + start;
    listOfObjects<TrainInfoPerStation *> *pivot;
    pivot = info[x / K];
    for (int i = 0; i < x % K; i++)
    {
      pivot = pivot->next;
    }
    listOfObjects<TrainInfoPerStation *> *first = info[start / K];
    listOfObjects<TrainInfoPerStation *> *last = info[end / K];
    for (int i = 0; i < start % K; i++)
    {
      first = first->next;
    }
    for (int i = 0; i < end % K; i++)
    {
      last = last->next;
    }
    swap(*pivot->object, *last->object);
    x = Partition(first, last);
    QuicksortSimple(stnInfoList, start, x + start - 1);
    QuicksortSimple(stnInfoList, x + start + 1, end);
  }

  recursionLevel--;
  return;
}

#endif
