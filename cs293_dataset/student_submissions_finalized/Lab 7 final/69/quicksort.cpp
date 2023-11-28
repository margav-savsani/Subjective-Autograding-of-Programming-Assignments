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
bool lessthan(TrainInfoPerStation *ob1, TrainInfoPerStation *ob2)
{
    for (int i = 0; i < 7; i++)
    {
        if (ob1->daysOfWeek[i] && ob2->daysOfWeek[i])
        {
            if (ob1->depTime < ob2->depTime)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (ob2->daysOfWeek[i])
        {
            return false;
        }
        else if (ob1->daysOfWeek[i])
        {
            return true;
        }
    }
    return false;
}
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // A few static variable declarations
    static int K = 4;               // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    // Increment recursion level on entering the function
    recursionLevel++;
    static listOfObjects<TrainInfoPerStation *> **checkpoints;
    int len = 1;
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
    listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;
    while (ptr->next != nullptr)
    {
        len++;
    }

    if (recursionLevel == 0)
    {
        // Find len of the list stnInfoList, if needed.
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.
        checkpoints = new listOfObjects<TrainInfoPerStation *> *[(len / K) + 1];
        listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;
        int count = 0, index = 0;
        while (ptr != nullptr)
        {
            if (count % K == 0)
            {
                checkpoints[index] = ptr;
                cout << ptr << endl;
                index++;
            }
            cout << ptr << endl;
            ptr = ptr->next;
            count++;
        }
    }

    // Put your code for the core of Quicksort here
    // srand(time(0));
    int random = rand() % len;
    cout << random << endl;
    int count = 0;
    listOfObjects<TrainInfoPerStation *> *ptr2 = checkpoints[random / K];
    while (count != random % K)
    {
        ptr2 = ptr2->next;
        count++;
    }
    listOfObjects<TrainInfoPerStation *> *pivot = ptr2;
    count = 1;
    // pointer from Last
    listOfObjects<TrainInfoPerStation *> *j = checkpoints[len / K];
    while (count != len % K)
    {
        j = j->next;
        count++;
    }
    // pointer from First
    listOfObjects<TrainInfoPerStation *> *i = checkpoints[0];

    int partition_index = 0;
    // while (true)
    // {
    //   while (lessthan(i, pivot))
    //   {
    //     i = i->next;
    //     partition_index++;
    //   }
    //   while (lessthan(pivot, j))
    //   {
    //     j = j->prev;
    //   }
    //   if (lessthan(i, j))
    //   {
    //     TrainInfoPerStation *temp = i->object;
    //     i->object = j->object;
    //     j->object = temp;
    //   }
    //   else
    //     break;
    // }
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
    static listOfObjects<TrainInfoPerStation *> **checkpoints;
    int len = 1;
    if (start < end)
    {
        cout << start << " " << end << endl;
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
        listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;

        // cout<<recursionLevel<<endl;
        if (recursionLevel == 0)
        {
            // Find len of the list stnInfoList, if needed.
            // Allocate additional space for upto n/K TrainInfoPerStation objects
            // if needed.
            // Do other things that you may want to do only at the beginning
            // as a pre-processing step.
            while (ptr->next != nullptr)
            {
                len++;
                ptr = ptr->next;
            }
            checkpoints = new listOfObjects<TrainInfoPerStation *> *[(len / K) + 1];
            listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;
            int count = 0, index = 0;
            while (ptr != nullptr)
            {
                if (count % K == 0)
                {
                    checkpoints[index] = ptr;
                    index++;
                }
                ptr = ptr->next;
                count++;
            }
        }

        // Put your code for the core of Quicksort here
        srand(time(0));
        int random = start + (rand() % (end - start + 1));
        cout << random << endl;
        int count = 0;
        listOfObjects<TrainInfoPerStation *> *ptr2 = checkpoints[random / K];
        while (count != random % K)
        {
            ptr2 = ptr2->next;
            count++;
        }
        listOfObjects<TrainInfoPerStation *> *pivot = ptr2;
        count = 0;
        // pointer from
        listOfObjects<TrainInfoPerStation *> *j = checkpoints[end / K];
        while (count != end % K)
        {
            j = j->next;
            count++;
        }
        count = 0;
        // pointer from First
        listOfObjects<TrainInfoPerStation *> *i = checkpoints[start / K];
        while (count != start % K)
        {
            i = i->next;
            count++;
        }
        count = 0;

        int partition_index = start;
        int last_index = end;
        TrainInfoPerStation *pivot_object = pivot->object;

        while (true)
        {
            while (lessthan(pivot_object, j->object))
            {
                j = j->prev;
                last_index--;
            }
            while (lessthan(i->object, pivot_object))
            {
                i = i->next;
                partition_index++;
            }
            if (partition_index < last_index)
            {
                TrainInfoPerStation *temp = i->object;
                i->object = j->object;
                j->object = temp;
            }
            else
            {
                QuicksortSimple(stnInfoList, start, partition_index - 1);
                QuicksortSimple(stnInfoList, partition_index + 1, end);
                break;
            }
        }
        if (last_index == end)
        {
            QuicksortSimple(stnInfoList, start, last_index - 1);
            QuicksortSimple(stnInfoList, last_index, end);
        }
        else
        {

            QuicksortSimple(stnInfoList, start, last_index);
            QuicksortSimple(stnInfoList, last_index + 1, end);
        }

        // Decrement recursion level before leaving the function
    }
    recursionLevel--;
    return;
}

#endif
