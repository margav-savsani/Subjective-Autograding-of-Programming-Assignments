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
int day_index(TrainInfoPerStation *pointer)
{
  for (int i = 0; i < 7; i++)
  {
    if (pointer->daysOfWeek[i] == true)
    {
      return i;
    }
  }
}

int depart_time(TrainInfoPerStation *pointer)
{
  return pointer->depTime;
}

bool lessthan(TrainInfoPerStation *a, TrainInfoPerStation *b)
{
  if (day_index(a) < day_index(b))
  {
    return true;
  }
  else if (day_index(a) == day_index(b))
  {
    if (depart_time(a) < depart_time(b))
    {
      return true;
    }
    else
      return false;
  }
  else
    return false;
}

bool equal(TrainInfoPerStation *a, TrainInfoPerStation *b)
{
  if (day_index(a) == day_index(b) && depart_time(a) == depart_time(b))
    return true;
  else
    return false;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  if (start < end)
  {

    // cout << "entered" << endl;
    // cout << "starting index: " << start << endl;
    // cout << " ending index: " << end << endl;
    //  A few static variable declarations
    static int K = 4;               // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in
    int len_linkedlist = 0;
    static int len_short = 0;
    static listOfObjects<TrainInfoPerStation *> **short_list;

    int len_list = end - start + 1;
    // Increment recursion level on entering the function
    recursionLevel++;
    // cout << "recursion:" << recursionLevel << endl;
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
      listOfObjects<TrainInfoPerStation *> *point = stnInfoList;
      while (point != nullptr)
      {
        len_linkedlist++;
        // cout << "point day: " << day_index(point->object) << endl;
        // cout << "point deptime: " << depart_time(point->object) << endl;
        point = point->next;
      }
      //cout << "length of the linkedlist: " << len_linkedlist << endl;

      point = stnInfoList;
      len_short = (len_linkedlist / K) + 1;
      short_list = new listOfObjects<TrainInfoPerStation *> *[len_short];
      for (int i = 0; i < len_short; i++)
      {
        short_list[i] = point;
        if (i < len_short - 1)
        {
          short_list[i] = point;
          for (int j = 0; j < K; j++)
          {
            point = point->next;
          }
        }
      }
      // Find length of the list stnInfoList, if needed.
      // Allocate additional space for upto n/K TrainInfoPerStation objects
      // if needed.
      // Do other things that you may want to do only at the beginning
      // as a pre-processing step.
    }
    // Put your code for the core of Quicksort here

    // choosing pivot open
    srand(time(0));
    int random1 = rand() % len_list;
    //cout << "pivot index: " << start + random1 << endl;
    int a = (start + random1) / K;
    int b = (start + random1) % K;
    listOfObjects<TrainInfoPerStation *> *pivot = short_list[a];
    for (int i = 0; i <= b; i++)
    {
      // cout << "iterative loop for pivot, loop num: " << i << endl;
      if (i < b)
      {
        pivot = pivot->next;
      }
    }
    // cout << "pivot day: " << day_index(pivot->object) << endl;
    // cout << "pivot deptime: " << depart_time(pivot->object) << endl;
    // choosing pivot close

    listOfObjects<TrainInfoPerStation *> *head;
    listOfObjects<TrainInfoPerStation *> *tail;

    int s1 = start / K;
    int l1 = start % K;
    listOfObjects<TrainInfoPerStation *> *header = short_list[s1];
    for (int i = 0; i <= l1; i++)
    {
      if (i < l1)
      {
        header = header->next;
      }
    }
    // cout << "header day: " << day_index(header->object) << endl;
    // cout << "header deptime: " << depart_time(header->object) << endl;
    head = header;

    int s2 = end / K;
    int l2 = end % K;
    listOfObjects<TrainInfoPerStation *> *tailer = short_list[s2];
    for (int i = 0; i <= l2; i++)
    {
      if (i < l2)
      {
        tailer = tailer->next;
      }
    }
    // cout << "tailer day: " << day_index(tailer->object) << endl;
    // cout << "tailer deptime: " << depart_time(tailer->object) << endl;
    tail = tailer;

    int i = start;
    int j = end;

    TrainInfoPerStation *compare = pivot->object;
    // pivot->object=tailer->object;
    // tailer->object=pivot->object;

    while (true)
    {
      // cout << "into while loop no1 " << endl;
      // cout << depart_time(compare) << "pivot&" << depart_time(header->object) << "header" << endl;
      // cout << day_index(compare) << "pivot&" << day_index(header->object) << "header" << endl;

      // if (equal(header, pivot))
      //   return;
      while (lessthan(header->object, compare))
      {
        // cout << depart_time(compare) << "pivot&" << depart_time(header->object) << "header" << endl;
        // cout << day_index(compare) << "pivot&" << day_index(header->object) << "header" << endl;
        // cout << "into while loop i: " << i << endl;
        i++;
        header = header->next;
        // cout << depart_time(compare) << "pivot&" << depart_time(header->object) << "header" << endl;
        // cout << day_index(compare) << "pivot&" << day_index(header->object) << "header" << endl
        //      << endl;
      }
      //cout << "out1" << endl;

      //cout << depart_time(compare) << "pivot&" << depart_time(tailer->object) << "tailer" << endl;
      //cout << day_index(compare) << "pivot&" << day_index(tailer->object) << "tailer" << endl;
      // if (equal(tailer, pivot))
      //   return;
      while (lessthan(compare, tailer->object))
      {
        // cout << depart_time(compare) << "pivot&" << depart_time(tailer->object) << "tailer" << endl;
        // cout << day_index(compare) << "pivot&" << day_index(tailer->object) << "tailer" << endl;
        // cout << "into while loop no j: " << j << endl;
        j--;
        tailer = tailer->prev;
        // cout << depart_time(compare) << "pivot&" << depart_time(tailer->object) << "tailer" << endl;
        // cout << day_index(compare) << "pivot&" << day_index(tailer->object) << "tailer" << endl;
      }
      //cout << "out2" << endl;

      if (i < j)
      {
        //cout << "exchange happening" << endl;
        TrainInfoPerStation *exchange = header->object;
        header->object = tailer->object;
        tailer->object = exchange;
      }
      // else if (i == j)
      //   return;
      // else if(equal(header->object,compare) && equal(tailer->object,compare))
      // {
      //   QuicksortSimple(stnInfoList, start, i-1);
      //   QuicksortSimple(stnInfoList, i + 1, end);
      // }
      else
      {
        //cout << "will go into recursive call" << endl;
        QuicksortSimple(stnInfoList, start, i-1);
        QuicksortSimple(stnInfoList, i + 1, end);
        break;
        // Decrement recursion level before leaving the function
      }
    }

    // recursive calling of the two parts.
    //  int pivot_index = random1;
    //  QuicksortSimple(stnInfoList,start,pivot_index-1);
    //  QuicksortSimple(stnInfoList, pivot_index, end);

    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
  }
  else return;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int len_list = 0;
  static int len_short = 0;
  static listOfObjects<TrainInfoPerStation *> **short_list;
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
    listOfObjects<TrainInfoPerStation *> *point = stnInfoList;
    while (point->object != nullptr)
    {
      len_list++;
      point = point->next;
    }

    point = stnInfoList;
    len_short = (len_list / K) + 1;
    short_list = new listOfObjects<TrainInfoPerStation *> *[len_short];
    for (int i = 0; i < len_short; i++)
    {
      if (i == (len_short - 1))
      {
        short_list[i] = point;
      }
      else
      {
        short_list[i] = point;
        for (int j = 0; j < 3; j++)
        {
          point = point->next;
        }
      }
    }
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  // Put your code for the core of Quicksort here

  // choosing pivot open
  int random1 = rand() % len_short;
  int random2 = rand() % 4;
  listOfObjects<TrainInfoPerStation *> *pivot = short_list[random1];
  for (int i = 0; i <= random2; i++)
  {
    if (i < random2)
    {
      pivot = pivot->next;
    }
  }
  int pivot_index = 4 * random1 + random2;
  // choosing pivot close
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif

// // A few static variable declarations
//   static int K = 4;               // Parameter to be experimented with
//   static int recursionLevel = -1; // This can be used to find out at which

//                                   // level of the recursion you are in

//   // Increment recursion level on entering the function
//   recursionLevel++;

//   // If you need to set up additional storage (upto n/K TrainInfoPerStation
//   // elements), it's ok to do it *once* using static variables/array.
//   // Using the static recursionLevel, you can ensure that the storage
//   // allocation is done only the first time Quicksort is called, and not
//   // in every recursive call.
//   //
//   // Note that if you allocate space for upto n/K TrainInfoPerStation in
//   // each recursive call, you will end up using much more than n/K space
//   // overall.  So you MUST NOT allocate space in each recursive call.
//   //
//   // A variable/array defined using static is not created afresh in
//   // each recursive call.  Instead, a single copy of it is maintained
//   // across all recursions.

//   if (recursionLevel == 0)
//   {
//     // Allocate additional space for upto n/K TrainInfoPerStation objects
//     // if needed.
//     // Do other things that you may want to do only at the beginning
//     // as a pre-processing step.
//   }

//   // Put your code for the core of QuicksortSimple here

//   // Decrement recursion level before leaving the function
//   recursionLevel--;
//   return;