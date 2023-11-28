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
#include <ctime>

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
// void printer(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *end){
//   string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//    listOfObjects<TrainInfoPerStation *> *currList = start;
//   while (currList != end->next) {
//     TrainInfoPerStation *currInfo = currList->object;
//     if (currInfo != nullptr) {
//       cout << GREEN << "Day(s): " << RESET;
//       for (int i=0; i<7; i++) {
// 	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
//       }
//       cout << endl;
//       cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
//       cout << RED << "Arr: " << RESET;
//       if (currInfo->arrTime == -1) {
// 	cout << "Starts";
//       }
//       else {
// 	cout << currInfo->arrTime;
//       }
//       cout << RED << " Dep: " << RESET;
//       if (currInfo->depTime == -1) {
// 	cout << "Ends";
//       }
//       else {
// 	cout << currInfo->depTime;
//       }
//       cout << endl;
//     }
//     currList = currList->next;
//   }
//   cout << endl;

// }
int Planner ::Partition(listOfObjects<TrainInfoPerStation *> *ending, listOfObjects<TrainInfoPerStation *> *starting, int start, int end)
{

  static listOfObjects<TrainInfoPerStation *> *pivot;
  pivot = ending;
  if (start < end) // we will return -1 if start<finish
  {

    static int a;
    a = start - 1;
    static int b;
    b = end + 1;

    while (true)
    {
      while (b >= start) // normal quicksort algorithm
      {

        b = b - 1;
        
        static int y;
        static int z;
        static int j;
        j = 0;
        while (j <= 6)
        {
          if (ending->object->daysOfWeek[j])
          {
            y = j * 5000;
            break;
          }
          j++;
        }
        y = y + ending->object->arrTime;
        j = 0;
        while (j <= 6)
        {
          if (pivot->object->daysOfWeek[j]) //first preference is days of if days differ by even one ,nothing can  balance it 
          {
            z = j * 5000;
            break;
          }
          j++;
        }
        z = z + pivot->object->arrTime;
        if (y <= z)
        {

          break;
        }
        ending = ending->prev;

        // {
        //     break;
        // }
      }
      while (a <= end)
      {
        a = a + 1;

        // comparisons++;
        // if (array[a].getJourneyCode() >= x.getJourneyCode())
        // {
        //     break;
        // }
        static int y;
        static int z;
        static int j;
        j = 0;
        while (j <= 6)
        {
          if (starting->object->daysOfWeek[j])
          {
            y = j * 5000;
            break;
          }
          j++;
        }
        y = y + starting->object->arrTime;
        j = 0;
        while (j <= 6)
        {
          if (pivot->object->daysOfWeek[j])
          {
            z = j * 5000;
            break;
          }
          j++;
        }
        z = z + pivot->object->arrTime;
        if (y >= z)
        {

          break;
        }
        starting = starting->next;
      }
      if (a < b)
      {
        swap(*(starting->object), *(ending->object)); //swapping
        ending = ending->prev; //going to previous pointer and next pointer
        starting = starting->next; 
      }
      else // edgecase if we don't include this case , we might get into infinite loop .
      {
        if (a == b)
        {
          b--;
        }
        return b;
      }
    }
  }
  return -1;
}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  srand(time(0));
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
  static listOfObjects<TrainInfoPerStation *> **v; //array
  // level of the recursion you are in
  if (start >= end)
  {
    // recursionLevel --;
    return;
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

  static int count;
  count = 1;
  // listOfObjects<TrainInfoPerStation *> *ending;
  if (recursionLevel == 0)
  {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    listOfObjects<TrainInfoPerStation *> *s = stnInfoList; //to count the length
    while (s->next != nullptr)
    {
      count++;
      s = s->next;
    }
    v = new listOfObjects<TrainInfoPerStation *> *[count / K + 1]; // array of nodes having length N/K +1
    //  s=stnInfoList;
    // ending = s;
  }

  if (recursionLevel == 0)
  {
    // if(count/K > 0 ){

    count = 0;
    listOfObjects<TrainInfoPerStation *> *s = stnInfoList;
    // stnddd[0] = stnInfoList;
    // count ++;
    while (s != nullptr)
    {
      if (count % K == 0) // filling the array
      {
        v[count / K] = s;
        // count ++;
      }
      s = s->next;
      count++;
    }
  }
  static int y; //random number 

  y = start + rand() % (end - start + 1);

  static listOfObjects<TrainInfoPerStation *> *ending;
  ending = v[end / K];
  static listOfObjects<TrainInfoPerStation *> *starting;
  starting = v[start / K];

  count = 0;
  while (count < start % K)
  {
    starting = starting->next;
    count = count + 1;
  }
  count = 0;
  while (count < end % K)
  {
    count = count + 1;
    ending = ending->next;
  }
  // starting->next;

  static listOfObjects<TrainInfoPerStation *> *randompivot;
  randompivot = v[y / K];
  count = y % K;
  while (count != 0) // pivot is calculated in O(K)
  {
    randompivot = randompivot->next;
    count--;
  }
  swap(*(randompivot->object), *(ending->object));
  // printer(ending,ending);

  static int q;
  q = Partition(ending, starting, start, end);
  // cout<<q<<endl;
  // printer(starting , ending);
  QuicksortSimple(stnInfoList, start, q);
  QuicksortSimple(stnInfoList, q + 1, end);

  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1;
  // This can be used to find out at which
  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> **v;
  static int start; // to store start and end else everything same as Quicksort simple
  static int end;

  // level of the recursion you are in

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
  static int count;
  count = 1; //to calculate length
  if (recursionLevel == 0)
  {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.

    listOfObjects<TrainInfoPerStation *> *s = stnInfoList;
    while (s->next != nullptr)
    {
      count++;
      s = s->next; 
    }
    v = new listOfObjects<TrainInfoPerStation *> *[count / K + 1];
    start = 0;
    end = count - 1;
    //  s=stnInfoList;
    // ending = s;
  }
  if (recursionLevel == 0)
  {
    count = 0;
    listOfObjects<TrainInfoPerStation *> *s = stnInfoList;
    // stnddd[0] = stnInfoList;
    // count ++;
    while (s != nullptr)
    {
      if (count % K == 0)
      {
        v[count / K] = s;
        // count ++;
      }
      s = s->next;
      count++;
    }

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  if (start >= end)
  {
    recursionLevel--;
    return;
  }
  srand(time(0));
  static int y;

  y = start + rand() % (end - start + 1);

  static listOfObjects<TrainInfoPerStation *> *ending;
  ending = v[end / K];
  static listOfObjects<TrainInfoPerStation *> *starting;
  starting = v[start / K];

  count = 0;
  while (count < start % K)
  {
    starting = starting->next;
    count = count + 1;
  }
  count = 0;
  while (count < end % K)
  {
    // cout<<"GO"<<endl;
    count = count + 1;
    ending = ending->next;
  }
  // cout<<"PO"<<endl;
  // starting->next;

  static listOfObjects<TrainInfoPerStation *> *randompivot;
  randompivot = v[y / K];
  count = y % K;
  while (count != 0)
  {
    randompivot = randompivot->next;
    count--;
  }
  swap(*(randompivot->object), *(ending->object));
  // printer(ending,ending);
  int q;
  q = Partition(ending, starting, start, end); //store the PARTITION INDEX
  // cout<<q<<endl;

  int A = end;
  end = q; //changing end to q , because first call was for start,q
  Quicksort(stnInfoList);
  start = q + 1;// changing start to q+1 because second call was for q+1,end I had to use a variable A because end is static and changing
  end = A;
  Quicksort(stnInfoList);
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
