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
#include "planner.cpp"
#ifndef CODES_H
#include "codes.h"
#endif

bool gt(TrainInfoPerStation a, TrainInfoPerStation b)
{
  // first checking for days if some is on earlier day it will get priority and will be smaller.
  for (int i = 0; i < 7; i++)
  { 
    if (a.daysOfWeek[i] == true && b.daysOfWeek[i] == false)
    {
      return false;
    }
    else if (a.daysOfWeek[i] == false && b.daysOfWeek[i] == true)
    {
      return true;
    }
  }
    // if on sameday doing comparison by dept. time.
  return (b.depTime < a.arrTime);
}
bool lt(TrainInfoPerStation a, TrainInfoPerStation b)
{
   // first checking for days if some is on earlier day it will get priority and will be smaller.
  for (int i = 0; i < 7; i++)
  {
    if (a.daysOfWeek[i] == true && b.daysOfWeek[i] == false)
    {
      return true;
    }
    else if (a.daysOfWeek[i] == false && b.daysOfWeek[i] == true)
    {
      return false;
    }
  }
  // if on sameday doing comparison by dept. time.
  return (b.depTime > a.arrTime);
}

void myswap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
  // swapping the objects in a cyclic making the third object c.
  TrainInfoPerStation *c = a->object;
  a->object = b->object;
  b->object = c;
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

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 3;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int s_start = 0;  //This mimics the start parameter of QuicksortSimple
  static int s_end = 0;    //This mimics the end parameter of QuicksortSimple
  static int no = 0;       // The size of array of pointers.
  // Pointer's array intially set to nullptr.
  static listOfObjects<TrainInfoPerStation *> **pointer = nullptr;
  // Increment recursion level on entering the function
  recursionLevel++;

  
  // Setting up the things at Recursion level zero like the pointers array its size , s_start and s_end.
  if (recursionLevel == 0)
  {
    int n = 1;
    // getting up the last element of list.
    listOfObjects<TrainInfoPerStation *> *last = stnInfoList;
    // finding size of intial travelling through entire list till next equals nullptr
    // also simulaneously storing the last element.
    while (last->next != nullptr)
    {
      last = last->next;
      n++;
    }
    // intial last index of s_end is n-1.
    s_end = n - 1;
    // denoting the size of pointer's array.
    int c = (n + K - 1) / K;
    // setting up pointer to travel's linked list to set pointer's array. 
    listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;
    // setting up the pointer's array. at a distance of k elements from start.
    // so basically the 0th,kth,.. etc elements are stored in array.
    pointer = new listOfObjects<TrainInfoPerStation *> *[c];
    for (int i = 0; i < c; i++)
    {
      pointer[i] = curr;
      for (int j = 0; j < K && i != c - 1; j++)
      {
        curr = curr->next;
      } // iterating to finding pointers at n/k point.
    }
  }

  //copying up the static start and end to our local mystart and myend  basically helpful in 
  // setting up s_start and s_end for different quicksort calls.
  int mystart = s_start, myend = s_end;
  // setting up the size of linked list.
  int N = myend - mystart + 1;
  
  // base case for recursion.
  if (stnInfoList == nullptr || N <=1)
  {
  // decreasing the recursionlevel before returning.
    recursionLevel--;
    return;
  }
  // finding the last element of stnList by traversing the list.
  listOfObjects<TrainInfoPerStation *> *last = stnInfoList;
  for (int i = 0; i < myend - mystart; i++)
  {
    last = last->next;
  }
  
  // randomly setting the pivot index in between mystart and myend
  int c = rand() % N + mystart;
  // finding index of column of pivot in array by /k and its row no by %k.
  int x = c / K , y = c % K;
  listOfObjects<TrainInfoPerStation *> *pivot = pointer[x];
  // selecting pivot in O(K) time travelling through pointer list.
  for (int j = 0; j < y; j++)
  {
    pivot = pivot->next;
  }
  // swapping pivot with the last element 
  myswap(pivot, last);
  // storing up the pivot's value for comparison..
  TrainInfoPerStation value = *last->object;
  // setting up the index for partion.
  int i = 0 , j = N - 2;
  listOfObjects<TrainInfoPerStation *> *start = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *end = last->prev;

  // Following Naveen Garg's algorithm with just a slight modification. Moving from last till find a element
  // smaller than value of pivot and moving from front till find a element larger than value of pivot and
  // swapping these 2 if i>=j else breakout.
  while (i <= j)
  {
    while (lt(*start->object, value) && i < N - 1)
    {
      start = start->next;
      i++;
    }
    while (gt(*end->object, value) && j >= 0)
    {
      if (j != 0)
      {
        end = end->prev;
      }
      j--;
    }
    if (i <= j)
    {
      myswap(start, end);
      continue;
    }
  }

  {
    if (j != -1)
    {// if j doesn't reach till the start pivot is not the smallest element so swapping pivot with the
      // next element of current j's location and then calling the Quickstart on two sub arrays keeping
      // the pivot on its right position. //Also setting the correct value of s_start and s_end before
      // calling the required Quickstart function.
      myswap(end->next, last);
      s_start = mystart; s_end = j + mystart;
      Quicksort(stnInfoList);
      s_start = j + mystart + 2; s_end = myend;
      Quicksort(end->next->next);
    }
    if (j == -1)
    { // if pivot is the smallest element putting pivot to first and calling the Quicksort
      // on rest of the array. //Also setting the correct value of s_start and s_end before
      // calling the required Quickstart function.

      myswap(end, last);
      s_start = 1 + mystart;
      s_end = myend;
      Quicksort(end->next);
    }
  }

  // decreasing recursion level before leaving the function.
  recursionLevel--;
  if (recursionLevel == -1)
  {   // setting back the intial static variable to intial state.
    no = 0;
    listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;
    pointer = nullptr;
    s_start = 0;
    s_end = 0;
  }
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int mystart, int myend)
{
  // A few static variable declarations
  static int K = 1;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  // static variable to store pointer's array size
  static int no = 0;
  // static pointer's array to select pivot
  static listOfObjects<TrainInfoPerStation *> **pointer = nullptr;
  // Increment recursion level on entering the function
  recursionLevel++;
  // setting up the no of elements in list.
  int N = 1 + myend - mystart;
  // base case if list is empty or is of size 1..
  if (N-1 <= 0 || stnInfoList==nullptr)
  {
    recursionLevel--;
    return;
  }

  listOfObjects<TrainInfoPerStation *> *last = stnInfoList;
  // getting up the last elemnt of array for use afterwards.
  for (int i = 0; i < myend - mystart; i++)
  {
    last = last->next;
  }
  

// DOING modifications at recursion level 0.
  if (recursionLevel == 0)
  {
    int n = 1 + myend - mystart;
    // getting c size of pivot list.
    int c = (n + K - 1) / K;
    listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;
    // no of elements in pivot list is (n+k-1)/k.
    no = n / K;
    // setting the pointer's list. storing elements that are at a distance of k .// so (n-k+1)/K memory is required
    // and u can get any element in k time if you know its index.
    pointer = new listOfObjects<TrainInfoPerStation *> *[c];
    for (int i = 0; i < c; i++)
    {
      pointer[i] = curr;
      for (int j = 0; j < K && i != c - 1; j++)
      {
        curr = curr->next;
      }
    }
  }
  // randomly setting the pivot index in between mystart and myend
  int c = rand() % N + mystart;
  // finding index of column of pivot in array by /k and its row no by %k.
  int x = c / K, y = c % K;
  listOfObjects<TrainInfoPerStation *> *pivot = pointer[x];
  // selecting pivot in O(K) time travelling through pointer list.
  for (int j = 0; j < y; j++)
  {
    pivot = pivot->next;
  }
  myswap(pivot, last);
  TrainInfoPerStation value = *last->object;
  int i = 0, j = N - 2;
  // pointer to the start of the list for Quickstart
  listOfObjects<TrainInfoPerStation *> *start = stnInfoList;
  // pointer to the end of the list for Quickstart.
  listOfObjects<TrainInfoPerStation *> *end = last->prev;
  // Following Naveen Garg's algorithm with just a slight modification. Moving from last till find a element
  // smaller than value of pivot and moving from front till find a element larger than value of pivot and
  // swapping these 2 if i>=j else breakout.

  while (i <= j)
  {
    while (lt(*start->object, value) && i < N - 1)
    {
      start = start->next;
      i++;
    }
    while (gt(*end->object, value) && j >= 0)
    {
      if (j != 0)
      {
        end = end->prev;
      }
      j--;
    }
    if (i < j)
    {
      myswap(start, end);
      continue;
    }
    else
    {
      break;
    }
  }

  {
    if (j != -1)
    { // if j doesn't reach till the start pivot is not the smallest element so swapping pivot with the
      // next element of current j's location and then calling the Quickstart on two sub arrays keeping
      // the pivot on its right position.
      myswap(end->next, last);
      QuicksortSimple(stnInfoList, mystart, j + mystart);
      QuicksortSimple(end->next->next, j + mystart + 2, myend);
    }
    if (j == -1)
    { // if pivot is the smallest element putting pivot to first and calling the Quicksort
      // on rest of the array.
      myswap(end, last);
      QuicksortSimple(end->next, 1 + mystart, myend);
    }
  }
  // Decrement recursion level before leaving the function
  recursionLevel--;
  if (recursionLevel == -1)
  {
    // setting back the intial static variable to intial state.
    no = 0;
    pointer = nullptr;
  }
  return;
}

#endif
