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

/*
Swaps all the attributes 2 elements of listOfObjets
*/
void swap(listOfObjects<TrainInfoPerStation *> *s1, listOfObjects<TrainInfoPerStation *> *s2)
{
  TrainInfoPerStation *temp;
  temp = new TrainInfoPerStation(s2->object->journeyCode, s2->object->stopSeq, s2->object->arrTime, s2->object->depTime);
  for (int i = 0; i < 7; i++)
  {
    temp->daysOfWeek[i] = s2->object->daysOfWeek[i];
    s2->object->daysOfWeek[i] = s1->object->daysOfWeek[i];
    s1->object->daysOfWeek[i] = temp->daysOfWeek[i];
  }
  s2->object->arrTime = s1->object->arrTime;
  s1->object->arrTime = temp->arrTime;
  s2->object->depTime = s1->object->depTime;
  s1->object->depTime = temp->depTime;
  s2->object->journeyCode = s1->object->journeyCode;
  s1->object->journeyCode = temp->journeyCode;
  s2->object->stopSeq = s1->object->stopSeq;
  s1->object->stopSeq = temp->stopSeq;
}


/*
In the partitionFunc, we update the list such that all elements left to pivot are less than it and towards right are greater than it. Stating from starting element of list and pivot->next,we check are values if they are not according to convention, we swap then till we reach the end.
*/
listOfObjects<TrainInfoPerStation *> *Planner::partitionfunc1(listOfObjects<TrainInfoPerStation *> *h, listOfObjects<TrainInfoPerStation *> *initial, listOfObjects<TrainInfoPerStation *> *final, int &range)
{
  // set pivot as h element
  int day;
  for (day = 0; day < 7; day++)
  {
    if (h->object->daysOfWeek[day])
    {
      break;
    }
  }
  //  similar to i = l-1 for array implementation
  listOfObjects<TrainInfoPerStation *> *pivot = h;
  listOfObjects<TrainInfoPerStation *> *l = initial;
  h = h->next;

  // Similar to "for (int j = l; j <= h- 1; j++)"
  while (true)
  {
    while (l != pivot)
    {
      int day2;
      for (day2 = 0; day2 < 7; day2++)
      {
        if (l->object->daysOfWeek[day2])
        {
          break;
        }
      }
      if (day2 > day)
      {
        break;
      }
      else if (day2 == day)
      {
        if (l->object->depTime > pivot->object->depTime)
        {
          break;
        }
        else if (l->object->depTime == pivot->object->depTime)
        {
          if (l->object->arrTime > pivot->object->arrTime)
          {
            break;
          }
        }
      }
      l = l->next;
      range++;
    }
    while (h != final)
    {
      int day2;
      for (day2 = 0; day2 < 7; day2++)
      {
        if (h->object->daysOfWeek[day2])
        {
          break;
        }
      }

      if (day2 < day)
      {
        break;
      }
      else if (day2 == day)
      {
        if (h->object->depTime < pivot->object->depTime)
        {
          break;
        }
        else if (h->object->depTime == pivot->object->depTime)
        {
          if (h->object->arrTime < pivot->object->arrTime)
          {
            break;
          }
        }
      }
      h = h->next;
    }

    if (l == pivot && h == final)
    {
      return l;
    }
    else if (l == pivot)
    {

      swap(pivot, h);
      listOfObjects<TrainInfoPerStation *> *temp = h;
      pivot = temp;
      h = h->next;
    }
    else if (h == final)
    {
      swap(pivot, l);
      listOfObjects<TrainInfoPerStation *> *temp = l;
      pivot = temp;
      h = pivot->next;
    }
    else
    {
      swap(l, h);
    }
  }
}
/*
Gives a random pivot based on the start and end value
*/
listOfObjects<TrainInfoPerStation *> *pivotchooser1(listOfObjects<TrainInfoPerStation *> *stnInfoList, float k, listOfObjects<TrainInfoPerStation *> *array[], float start, float end)
{
  srand(time(0));
  int w = rand() % (int(end) - int(start) + 1) + int(start);
  int x = int(w / k);
  w = w % int(k);

  listOfObjects<TrainInfoPerStation *> *resultNode = array[x];

  while (w > 0)
  {
    resultNode = resultNode->next;
    w--;
  }
  return resultNode;
}


/*For recurssion level 0, we calculate the size of the listOfObjects to get N, after that we define an array of size ceil(n/k), and store pointer of every Kth element in linked list in the array. Then we use start & end.As start is 0 and end is Size-1. Then choose a random pivot in the range start to end. We then set 2 list initial and start with inital been the first element of StnInfoList and final being nullptr. After that we call the partititon function and then update end as position of pivot -1 and final as pointer to pivot and then again call the Quicksort on the initial part of the list. Then we update start as pivot of pivot +1 and end as n-1 and call the quicksort on 2nd part of the list.*/
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    //  A few static variable declarations
  static int K = 3; // Parameter to be experimented with
  static int recursionLevel = -1;
  static float n=end+1; // This can be used to find out at which
                  // level of the recursion you are in
  static int size;
  static listOfObjects<TrainInfoPerStation *> **array = nullptr;
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
 
  size = ceil((float(end+1)) / float(K)); //  MODIFY THIS TO USE IT WITHOUT CEIL FUNCITON
  static const int s = size;
  int sample = 0;
  if (recursionLevel == 0)
  {
    array = new listOfObjects<TrainInfoPerStation *> *[s];
    listOfObjects<TrainInfoPerStation *> *st = stnInfoList;
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < K; j++)
      {
        if (j == 0)
        {
          array[i] = st;
        }
        st = st->next;
        if (st == nullptr)
        {
          break;
          sample = 1;
        }
      }
      if (sample == 1)
      {
        break;
      }
    }
  }

  // Find length of the list stnInfoList, if needed.
  // Allocate additional space for upto n/K TrainInfoPerStation objects
  // if needed.
  // Do other things that you may want to do only at the beginning
  // as a pre-processing step.


  listOfObjects<TrainInfoPerStation *> *l = stnInfoList;
  if (end > 0 && start <= end)
  {

    listOfObjects<TrainInfoPerStation *> *pivot = pivotchooser1(stnInfoList,K, array, start, end);

    static listOfObjects<TrainInfoPerStation *> *initial = stnInfoList;
    static listOfObjects<TrainInfoPerStation *> *final = nullptr;
    int status = end;
    listOfObjects<TrainInfoPerStation *> *liststatus = final;
    end = start;

    listOfObjects<TrainInfoPerStation *> *part = partitionfunc1(pivot, initial, final, end);
    final = part;
    end = end - 1;
    QuicksortSimple(l,start,end);

    initial = part->next;
    start = end + 2;
    if (status == n - 1)
    {
      final = nullptr;

      end = n - 1;
    }
    else
    {
      final = liststatus;
      end = status;
    }
    QuicksortSimple(part->next,start,end);
  }
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
  }


/*
For recurssion level 0, we calculate the size of the listOfObjects to get N, after that we define an array of size ceil(n/k), and store pointer of every Kth element in linked list in the array. Then we define 2 static variables- start & end.Setting start as 0 and end as Size-1. Then choose a random pivot in the range start to end. We then set 2 list initial and start with inital been the first element of StnInfoList and final being nullptr. After that we call the partititon function and then update end as position of pivot -1 and final as pointer to pivot and then again call the Quicksort on the initial part of the list. Then we update start as pivot of pivot +1 and end as n-1 and call the quicksort on 2nd part of the list.
*/
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  //  A few static variable declarations
  static float K = 3; // Parameter to be experimented with
  static int recursionLevel = -1;
  static float n; // This can be used to find out at which
                  // level of the recursion you are in
  static int size;
  static listOfObjects<TrainInfoPerStation *> **array = nullptr;
  static int start = 0;
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

    while (point != nullptr)
    {
      point = point->next;
      n++;
    }
    size = ceil(n / K); //  MODIFY THIS TO USE IT WITHOUT CEIL FUNCITON
  }
  static int end = n - 1;
  static const int s = size;
  int sample = 0;
  if (recursionLevel == 0)
  {
    array = new listOfObjects<TrainInfoPerStation *> *[s];
    listOfObjects<TrainInfoPerStation *> *st = stnInfoList;
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < K; j++)
      {
        if (j == 0)
        {
          array[i] = st;
        }
        st = st->next;
        if (st == nullptr)
        {
          break;
          sample = 1;
        }
      }
      if (sample == 1)
      {
        break;
      }
    }
  }

  // Find length of the list stnInfoList, if needed.
  // Allocate additional space for upto n/K TrainInfoPerStation objects
  // if needed.
  // Do other things that you may want to do only at the beginning
  // as a pre-processing step.


  listOfObjects<TrainInfoPerStation *> *l = stnInfoList;
  if (end > 0 && start <= end)
  {

    listOfObjects<TrainInfoPerStation *> *pivot = pivotchooser1(stnInfoList, K, array, start, end);

    static listOfObjects<TrainInfoPerStation *> *initial = stnInfoList;
    static listOfObjects<TrainInfoPerStation *> *final = nullptr;
    int status = end;
    listOfObjects<TrainInfoPerStation *> *liststatus = final;
    end = start;

    listOfObjects<TrainInfoPerStation *> *part = partitionfunc1(pivot, initial, final, end);
    final = part;
    end = end - 1;
    Quicksort(l);

    initial = part->next;
    start = end + 2;
    if (status == n - 1)
    {
      final = nullptr;

      end = n - 1;
    }
    else
    {
      final = liststatus;
      end = status;
    }
    Quicksort(part->next);
  }
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif