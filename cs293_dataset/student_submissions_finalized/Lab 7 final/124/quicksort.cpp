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
#include <time.h>

//Code by Krishna Chaitanya Gorle 

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
// and departure time within the day (next). Thus Sun 900 < Sun 1100
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
bool lessThan(TrainInfoPerStation *station1, TrainInfoPerStation *station2)
{
  for (int i = 0; i < 7; i++)//initializing for all days of the week(7days)
  {
    if (station1->daysOfWeek[i] && station2->daysOfWeek[i])
    {
     if (station1->daysOfWeek[i])//checking only source station  exist retuen true 
    {
      return true;
    }
    else if (station2->daysOfWeek[i])//if only destination exist in that day return false
    {
      return false;
    }
      else if (station1->depTime < station2->depTime)//if both exist return true
      {
        return true;
      }
      else//if both not exist return false
      {
        return false;
      }
    }
  }
  return true;
}
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation *> **check_the_point;
  int level = 1;
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  listOfObjects<TrainInfoPerStation *> *pointer = stnInfoList;
  while (pointer->next != nullptr)//This means that if list is not empty then proceed
  {
    level++;//increase the level(count)
  }

  if (recursionLevel == 0)
  {
    // Find level of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    check_the_point = new listOfObjects<TrainInfoPerStation *> *[(level / K) + 1];
    listOfObjects<TrainInfoPerStation *> *pointer = stnInfoList;
    int x = 0;
    int y = 0;//this is the index
    while (pointer != nullptr)
    {
      if (x % K == 0)
      {
        check_the_point[y] = pointer;
        cout << pointer << endl;
        y++;
      }
      cout << pointer << endl;
      pointer = pointer->next;
      x++;
    }
  }

  // Put your code for the core of Quicksort here
  int random = rand() % level;//intialization of random quicksort that print numbers between 1 and level
  cout << random << endl;
  int x_a = 0;
  listOfObjects<TrainInfoPerStation *> *pointer2 = check_the_point[random / K];//a pointer
  while (x_a != random % K)//this checks until the value is not equal to that point
  {
    pointer2 = pointer2->next;
    x_a++;//stores the value that how manypoints has that value(like station name,time)
  }
  listOfObjects<TrainInfoPerStation *> *pivot = pointer2;//choosen the pointer as the pivot for quick sort
  x_a = 1;
  listOfObjects<TrainInfoPerStation *> *a = check_the_point[level / K];//a pointer
  while (x_a != level % K)
  {
    a = a->next;//this checks until the value is not equal to that point
    x_a++;
  }
  listOfObjects<TrainInfoPerStation *> *b = check_the_point[0];

  int partition_y = 0;

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
  static listOfObjects<TrainInfoPerStation *> **check_the_point;
  int level = 1;
  if(start<end){
  cout<<start<<" "<<end<<endl;
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  listOfObjects<TrainInfoPerStation *> *pointer = stnInfoList;

  // cout<<recursionLevel<<endl;
  if (recursionLevel == 0)
  {
    // Find level of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    while (pointer->next != nullptr)
    {
      level++;
      // cout<<level<<endl;
      pointer = pointer->next;
    }
    check_the_point = new listOfObjects<TrainInfoPerStation *> *[(level / K) + 1];
    listOfObjects<TrainInfoPerStation *> *pointer = stnInfoList;
    int x = 0, y = 0;
    while (pointer != nullptr)//same as the above one but checking both bool and listofobjects condition at a time you can refer
    //the previous comments to know about them
    {
      if (x % K == 0)
      {
        check_the_point[y] = pointer;
        y++;
      }
      pointer = pointer->next;
      x++;
    }
  }

  // Put your code for the core of Quicksort here
  srand(time(0));
  int random = start + (rand() % (end - start + 1));
  cout<<random<<endl;
  int x_a = 0;
  listOfObjects<TrainInfoPerStation *> *pointer2 = check_the_point[random / K];
  while (x_a != random % K)//same as the above one.you can refer the previous comments to know about them
  {
    pointer2 = pointer2->next;
    x_a++;
  }
  listOfObjects<TrainInfoPerStation *> *pivot = pointer2;
  x_a = 0; 
  listOfObjects<TrainInfoPerStation *> *j = check_the_point[end/K];
  while (x_a != end % K)
  {
    j = j->next;
    x_a++;
  }
  x_a = 0;
  listOfObjects<TrainInfoPerStation *> *i = check_the_point[start/K];
  while (x_a != start % K)
  {
    i = i->next;
    x_a++;
  }
  x_a = 0;
  
  int partition_y = start;
  int last_y = end;
  TrainInfoPerStation* pivot_object = pivot->object;
  
  while (true)
  {
    while(lessThan(pivot_object, j->object))
    {
      j = j->prev;
      last_y--;
    }
    while (lessThan(i->object, pivot_object))
    {
      i = i->next;
      partition_y++;
    }
    if (partition_y < last_y)
    {
      TrainInfoPerStation *temp = i->object;
      i->object = j->object;
      j->object = temp;
      
    }
    else{ 
    cout<<"partitions"<<partition_y<< " "<<last_y<<endl;
    
    QuicksortSimple(stnInfoList, start, partition_y-1);//partion competed and quicksort starts
    QuicksortSimple(stnInfoList, partition_y + 1, end);
    break;
    }
  }
  }
  recursionLevel--;
  return;
}

#endif