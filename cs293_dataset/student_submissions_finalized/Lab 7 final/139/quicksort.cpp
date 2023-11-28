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

// A simple function which returns the last node of the list.
listOfObjects<TrainInfoPerStation *> *lastNode(listOfObjects<TrainInfoPerStation *> *node)
{
  while (node && node->next)
    node = node->next;
  return node;
}

// A simple function which returns the element at the index in a doubly linked list
listOfObjects<TrainInfoPerStation *> *Get(int index, listOfObjects<TrainInfoPerStation *> *list)
{
  listOfObjects<TrainInfoPerStation *> *crawl = list;
  for (int i = 0; i < index; i++)
  {
    crawl = crawl->next;
  }
  return crawl;
}

// A Function which returns the value of the particular journey by taking day as first preference and then time.
int Value(TrainInfoPerStation *T)
{
  int day = 1;
  // finding the value of day: (sun-1,mon-2,.........sat-7)
  for (int i = 0; i < 7; i++)
  {
    if (T->daysOfWeek[i])
      break;
    day++;
  }
  // as the first priority goes to days, multiplying it by order of 10, greater than order of time., and adding it to time.
  return (day * 10000) + T->arrTime;
}

// A simple function to get index of the element passed in the given List.
int index(listOfObjects<TrainInfoPerStation *> *p, listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  int i = 0;
  // base case (-1)
  if (p == nullptr)
    return -1;

  // creeping until we get index;
  listOfObjects<TrainInfoPerStation *> *s = stnInfoList;
  while (s != p)
  {
    s = s->next;
    i++;
  }
  return i;
}

// A function to Swap two <TrainInfoPerStation **> type elements
void Swap(TrainInfoPerStation **a, TrainInfoPerStation **b)
{
  // temporary pointer
  TrainInfoPerStation *t = *a;
  *a = *b;
  *b = t;
}

// partition:
listOfObjects<TrainInfoPerStation *> *partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *h, listOfObjects<TrainInfoPerStation *> *List, listOfObjects<TrainInfoPerStation *> **Array, int first, int last, int size_of_array, int K)
{
  // First index of the Array of pointers extracted from first index information.
  int StartIndex = first / K;
  // Final index of the Array of pointers extracted from last index information.
  int FinalIndex = last / K;

  // if both starting pointer and the ending pointer are in the same choosen Array pointer's next 4 pointers, then:
  if (FinalIndex == StartIndex)
  {
    // Assuming Pivot as the starting index of the 4 pointers of choosen index'th element of Array.
    listOfObjects<TrainInfoPerStation *> *Pivot = Array[StartIndex];

    // generating a random index from first index and last index
    int R = first % K + (rand() % (last % K - first % K + 1));

    // jumping as many times as random index from original pivot.takes O(k) time complexity.
    for (int i = 0; i < R; i++)
      Pivot = Pivot->next;

    // after extracting our pivot, I just swap pivot with last element and apply the same regular quicksort with last element as pivot as it is.
    Swap(&(Pivot->object), &(h->object));
    // continuing,...
    int x = Value(h->object);

    // similar to i = l-1 for array implementation
    listOfObjects<TrainInfoPerStation *> *i = l->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (listOfObjects<TrainInfoPerStation *> *j = l; j != h; j = j->next)
    {
      if (Value(j->object) <= x)
      {
        // Similar to i++ for array
        i = (i == NULL) ? l : i->next;
        // swapping i,j th objects.
        Swap(&(i->object), &(j->object));
      }
    }
    i = (i == NULL) ? l : i->next; // Similar to i++
    // swapping i and last objects.
    Swap(&(i->object), &(h->object));

    // finally returning the pointer i as partitioning pointer.
    return i;
  }
  else
  {
    // else, we have 3 subcases here:

    // generating a random pointer and assuming that as pivot from sub-array of those pointers that contain between first and last elements of list
    int RandomIndex = StartIndex + (rand() % (FinalIndex - StartIndex + 1));
    listOfObjects<TrainInfoPerStation *> *Pivot = Array[RandomIndex];

    // 1. if the random index is starting index of array, and starting index of the current sublist not the starting element of the array's selected random pointer's list(else, it continues the usual case 3).
    if ((RandomIndex) == StartIndex && first % K != 0)
    {
      // generating a random pivot among the k elements starting from array's random pointer excluding before start pointer.
      int R = first % K + (rand() % (K - first % K));
      // creeping until we reach the destiny.takes atmost O(K) time complexity.
      for (int i = 0; i < R; i++)
        Pivot = Pivot->next;
    }
    // 2. if the random index is Final index of array, and last index of the current sublist not the last element of the array's selected random pointer's list(else, it continues the usual case 3).
    else if ((RandomIndex) == FinalIndex && last % K != K - 1)
    {
      // generating a random pivot among the k elements starting from array's random pointer excluding after last pointer.
      int R = 0 + (rand() % (last % K - 0 + 1));
      // creeping until we reach the destiny.takes atmost O(K) time complexity.
      for (int i = 0; i < R; i++)
        Pivot = Pivot->next;
    }
    // 3.the usual case: nothing special, we need to get a random pivot out of K elements starting from array's random pointer.
    else
    {
      // generating random number among the k elements starting from array's random pointer
      int R = rand() % (K);
      // creeping until we reach the destiny.takes atmost O(K) time complexity.
      for (int i = 0; i < R; i++)
        Pivot = Pivot->next;
    }
    // after extracting our pivot, I just swap pivot with last element and apply the same regular quicksort with last element as pivot as it is.
    Swap(&(Pivot->object), &(h->object));
    // continuing,...
    int x = Value(h->object);

    // similar implementation as in array:

    // similar to i = l-1 for array implementation
    listOfObjects<TrainInfoPerStation *> *i = l->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (listOfObjects<TrainInfoPerStation *> *j = l; j != h; j = j->next)
    {
      if (Value(j->object) <= x)
      {
        // Similar to i++ for array
        i = (i == nullptr) ? l : i->next;
        // swapping i,j th objects.
        Swap(&(i->object), &(j->object));
      }
    }
    i = (i == nullptr) ? l : i->next; // Similar to i++
    // swapping i and last objects.
    Swap(&(i->object), &(h->object));

    // finally returning the pointer i as partitioning pointer.
    return i;
  }
  // returning null of nothing
  return nullptr;
}

// A recursive implementation of quicksort for doubly linked list
void RecursiveQuickSort(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *h, listOfObjects<TrainInfoPerStation *> *List, int first, int last, int size_of_array, int K)
{
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Increment recursion level on entering the function
  recursionLevel++;

  // defining static array.
  static listOfObjects<TrainInfoPerStation *> **Array;
  // under level0, creating all possible data:
  if (recursionLevel == 0)
  {
    // Crawling the list whole at a tim such that we get full information about the array and others.
    listOfObjects<TrainInfoPerStation *> *crawl = List;
    // size of array:
    int size_of_array = (last + 1) / K;

    // if its 0,avoiding division,simply last+1;
    if (size_of_array == 0)
      size_of_array = last + 1;
    // initialising the array with size known
    Array = new listOfObjects<TrainInfoPerStation *> *[size_of_array];
    // index to be kept track of.
    int Ind = 0;
    // creeping until we store all information about list into array with O(n/K) space complexity.
    listOfObjects<TrainInfoPerStation *> *creep = List;
    while (creep != nullptr)
    {
      if (Ind % K == 0)
      {
        Array[Ind / K] = creep;
      }
      Ind++;
      creep = creep->next;
    }
  }

  if (h != NULL && l != h && l != h->next)
  {
    // extracting the partitioning pivot by random pivot generator and sorting sublists recursively.
    listOfObjects<TrainInfoPerStation *> *p = partition(l, h, List, Array, index(l, List), index(h, List), size_of_array, K);
    RecursiveQuickSort(l, p->prev, List, index(l, List), index(p->prev, List), size_of_array, K);
    RecursiveQuickSort(p->next, h, List, index(p->next, List), index(h, List), size_of_array, K);
  }

  // decreasing while exiting function.
  recursionLevel--;
  return;
}

// The main function to sort a linked list.
// It mainly calls RecursiveQuickSort()
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Increment recursion level on entering the function
  recursionLevel++;
  static int size = 0;
  listOfObjects<TrainInfoPerStation *> *s = stnInfoList;
  if (recursionLevel == 0)
  {
    while (s != nullptr)
    {
      size++;
      s = s->next;
    }
  }
  listOfObjects<TrainInfoPerStation *> *h = lastNode(stnInfoList);
  // Call the recursive QuickSort
  RecursiveQuickSort(stnInfoList, h, stnInfoList, 0, size - 1, size, K);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

// The main function to sort a linked list,with additional data, can skip some tests with that data.
// It mainly calls RecursiveQuickSort()
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // Increment recursion level on entering the function
  recursionLevel++;
  // size of linked list:
  if (recursionLevel == 0)
  {
  }
  listOfObjects<TrainInfoPerStation *> *h = lastNode(stnInfoList);
  // Call the recursive QuickSort
  RecursiveQuickSort(stnInfoList, h, stnInfoList, 0, end, end + 1, K);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
