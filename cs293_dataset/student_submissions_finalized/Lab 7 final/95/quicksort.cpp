#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP
#include <cstdlib>
#include <ctime>
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






// function for comparing two linked list node of TrainInfoPerStation
bool less_than(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{

  for (int i = 0; i < 7; i++)
  {


    if (a->object->daysOfWeek[i] == true && b->object->daysOfWeek[i] == false)
    {

        return false;

    }
    else if (b->object->daysOfWeek[i] == true && a->object->daysOfWeek[i] == false)
    {

        return true;

    }


  }

  if (a->object->depTime < b->object->depTime)
  {

    return true;

  }
  else
  {

    return false;

  }


}




//function for swaping two linked list node
void swap(listOfObjects<TrainInfoPerStation *> *&a, listOfObjects<TrainInfoPerStation *> *&b)
{

  if (a == b)
  {
    return;
  }

  int dep, arr;
  bool daysOfWeek[7];
  dep = a->object->depTime;
  arr = a->object->arrTime;
  for (int i = 0; i < 7; i++)
  {
    daysOfWeek[i] = a->object->daysOfWeek[i];
  }
  a->object->depTime = b->object->depTime;
  a->object->arrTime = b->object->arrTime;
  for (int i = 0; i < 7; i++)
  {
    a->object->daysOfWeek[i] = b->object->daysOfWeek[i];
  }
  b->object->depTime = dep;
  b->object->arrTime = arr;
  for (int i = 0; i < 7; i++)
  {
    b->object->daysOfWeek[i] = daysOfWeek[i];
  }


}





//partion function for Quicksort
listOfObjects<TrainInfoPerStation *> *partion(listOfObjects<TrainInfoPerStation *> *&start, listOfObjects<TrainInfoPerStation *> *&end, listOfObjects<TrainInfoPerStation *> *pivot)
{

  while (true)
  {
    if (start == end)
    {
      return start;
    }
    while (less_than(start, pivot))
    {

      start = start->next;
      if (start == end)
      {
        return start;
      }
    }
    while (less_than(pivot, end))
    {

      end = end->prev;
      if (start == end)
      {
        return start;
      }
    }

    swap(start, end);
  }
}






//function inside the Quicksort
void Quicksort_part_2(listOfObjects<TrainInfoPerStation *> *&stnInfoList, int n, int K, listOfObjects<TrainInfoPerStation *> *v[], listOfObjects<TrainInfoPerStation *> *&a)
{
  cout << stnInfoList->object << endl;
  if (stnInfoList == a)
  {
    return;
  }
  srand(time(0));

  int q = rand();

  int r = (q) % K;
  listOfObjects<TrainInfoPerStation *> *pivot = stnInfoList;
  for (int i = 0; i < r; i++)
  {
    if (pivot != a)
    {
      pivot = pivot->next;
    }
  }
  listOfObjects<TrainInfoPerStation *> *j = partion(stnInfoList, a, pivot);
  
  Quicksort_part_2(stnInfoList, n, K, v, j->prev);
  Quicksort_part_2(j->next, n, K, v, a);
}




//Quicksort funcition 
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  listOfObjects<TrainInfoPerStation *> *a = stnInfoList;
  int n = 1;
  if (a != NULL)
  {
    while (a->next != NULL)
    {
      n++;
      a = a->next;
    }
  }
  else
  {
    n = 0;
  }

  listOfObjects<TrainInfoPerStation *> **v = new listOfObjects<TrainInfoPerStation *> *[n / K];
  int i = 0, p = 0;
  listOfObjects<TrainInfoPerStation *> *aa = stnInfoList;
  while (aa != NULL)
  {

    if (i % K == 0)
    {
      v[p] = aa;
      p++;
      i++;
      aa = aa->next;
    }
    else
    {
      i++;
      aa = aa->next;
    }
  }

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
  Quicksort_part_2(stnInfoList, n, K, v, a);
  

  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  
  return;
}






//partion for SimpleQuicksort
int partion_2(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *end_node, int start, int end, int K, listOfObjects<TrainInfoPerStation *> **v)
{
  srand(time(0));
  int q;
  if (start != end)
  {
    q = start + (rand()) % (end - start);
  }
  else
  {
    q = 0;
  }
  int p = q / K;
  int r = q % K;
  listOfObjects<TrainInfoPerStation *> *pivot = v[p];
  for (int i = 0; i < r; i++)
  {
    if (pivot->next != NULL)
    {
      pivot = pivot->next;
    }
  }
  
 
  while (true)
  {
    while (less_than(stnInfoList, pivot))
    {
      
      stnInfoList = stnInfoList->next;
      start++;
      
    }
    while (less_than(pivot, end_node))
    {
      
      end_node = end_node->prev;
      end--;
     
    }
   
    if (start < end)
    {
      swap(stnInfoList, end_node);
    }
    else
    {
      return end;
    }
  }
}





//function QuicksortSimple
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  if (start < end)
  {
    static int K = 4;               // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    // Increment recursion level on entering the function
    recursionLevel++;
    static int n = 0;
    listOfObjects<TrainInfoPerStation *> *a = stnInfoList;
    static listOfObjects<TrainInfoPerStation *> **v;

    if (recursionLevel == 0)
    {
      while (a != NULL)
      {


        a = a->next;
        n++;
      }
      v = new listOfObjects<TrainInfoPerStation *> *[n / K];
      a = stnInfoList;
      int p = 0, i = 0;
      while (a != NULL)
      {
        if (i % K == 0)
        {
          v[p] = a;
          i++;
          p++;
          a = a->next;
        }
        else
        {
          i++;
          a = a->next;
        }
      }
    }
  int h=start/K;
    listOfObjects<TrainInfoPerStation *> *end_node = v[h];
    int g = start;
    while ((g-1)!=end)
    {
      g++;
      end_node = end_node->next;
    }
    int q = partion_2(stnInfoList, end_node, start, end, K, v);
    QuicksortSimple(stnInfoList, start, q - 1);
    QuicksortSimple(end_node, q + 1, end);
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

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    // Put your code for the core of QuicksortSimple here

    // Decrement recursion level before leaving the function
  }
  return;
}

#endif
