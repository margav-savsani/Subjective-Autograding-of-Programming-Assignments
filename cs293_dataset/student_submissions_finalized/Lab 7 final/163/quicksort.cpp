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

bool isLess(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{ // Function to compare two train info
    for (int i = 0; i < 7; i++)
    {
        if (a->object->daysOfWeek[i] == false && b->object->daysOfWeek[i] == false)
            continue; // we check next day
        else if (a->object->daysOfWeek[i] == true && b->object->daysOfWeek[i] == false)
            return true; // a train is first
        else if (a->object->daysOfWeek[i] == false && b->object->daysOfWeek[i] == true)
            return false; // b train is first
        else
            return a->object->arrTime < b->object->arrTime; // bot train on same day, compare by time
    }
    return false; // function should never reach here
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // A few static variable declarations
    static int K = 4;               // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
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

    static int n = 1;                                                // no. of elements in list
    static listOfObjects<TrainInfoPerStation *> **pointer;           // array of pointers to list objects
    static listOfObjects<TrainInfoPerStation *> *last = stnInfoList; // the pointer to last of array
    static int start;                                                // start of where we want to sort
    static int end;                                                  // end of where we want to sort

    if (recursionLevel == 0)
    {
        // Find length of the list stnInfoList, if needed.
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.
        listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
        while (last->next != nullptr)
        {
            n++; // n is calculated
            last = last->next;
        }
        pointer = new listOfObjects<TrainInfoPerStation *> *[(n / K) + 1]; // array stores n/K pointers each after K indices
        for (int i = 0; i < n; i++)
        {
            if (i % K == 0)
            {
                pointer[i / K] = temp;
            }
            temp = temp->next;
        }
        start = 0;
        end = n - 1; // start and end are set initially
    }

    // Put your code for the core of Quicksort here
    if (end == start)
        return; // sorted

    int p = start + rand() % (end - start + 1); // random index for pivot from start to end
    listOfObjects<TrainInfoPerStation *> *pivot = pointer[p / K];
    for (int i = 0; i < p % K; i++)
        pivot = pivot->next; // random pivot found in O(K).

    int left = start, right = end; // indices for right and left markers
    listOfObjects<TrainInfoPerStation *> *r = pointer[end / K];
    for (int i = 0; i < end % K; i++)
        r = r->next; // pointer to the right marker
    listOfObjects<TrainInfoPerStation *> *l = pointer[start / K];
    for (int i = 0; i < start % K; i++)
        l = l->next; // pointer to the left marker
    while (true)
    {
        while (isLess(pivot, r) && right > start)
        {
            right--;
            r = r->prev; // right marker is changed as needed
        }
        while (isLess(l, pivot) && left < end)
        {
            left++;
            l = l->next; // left marker is changed as needed
        }
        if (left < right)
        {
            TrainInfoPerStation *temp = l->object;
            l->object = r->object;
            r->object = temp; // right and left date are swapped
            if (pivot == l)
                pivot = r;
            else if (pivot == r)
                pivot = l; // in case one of l or r was the pivot, use also need to change the pivot pointer
        }
        else if (left == right)
        {
            if (left < end)
                left++;
            if (right > start)
                right--;
            break;
        }
        else
            break;
    }

    int t = end;
    end = right;
    Quicksort(stnInfoList);
    start = left;
    end = t;
    Quicksort(stnInfoList); // both partitions are sorted

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

    static int n = 1;                                                // no. of elements in list
    static listOfObjects<TrainInfoPerStation *> **pointer;           // array of pointers to list objects
    static listOfObjects<TrainInfoPerStation *> *last = stnInfoList; // the pointer to last of array
    if (recursionLevel == 0)
    {
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.
        listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
        while (last->next != nullptr)
        {
            n++; // n is calculated
            last = last->next;
        }
        pointer = new listOfObjects<TrainInfoPerStation *> *[(n / K) + 1]; // array stores n/K pointers each after K indices
        for (int i = 0; i < n; i++)
        {
            if (i % K == 0)
            {
                pointer[i / K] = temp;
            }
            temp = temp->next;
        }
    }

    // Put your code for the core of QuicksortSimple here
    if (end == start)
        return; // sorted

    int p = start + rand() % (end - start + 1); // random index for pivot from start to end
    listOfObjects<TrainInfoPerStation *> *pivot = pointer[p / K];
    for (int i = 0; i < p % K; i++)
        pivot = pivot->next; // random pivot found in O(K).

    int left = start, right = end; // indices for right and left markers
    listOfObjects<TrainInfoPerStation *> *r = pointer[end / K];
    for (int i = 0; i < end % K; i++)
        r = r->next; // pointer to the right marker
    listOfObjects<TrainInfoPerStation *> *l = pointer[start / K];
    for (int i = 0; i < start % K; i++)
        l = l->next; // pointer to the left marker
    while (true)
    {
        while (isLess(pivot, r) && right > start)
        {
            right--;
            r = r->prev; // right marker is changed as needed
        }
        while (isLess(l, pivot) && left < end)
        {
            left++;
            l = l->next; // left marker is changed as needed
        }
        if (left < right)
        {
            TrainInfoPerStation *temp = l->object;
            l->object = r->object;
            r->object = temp; // right and left date are swapped
            if (pivot == l)
                pivot = r;
            else if (pivot == r)
                pivot = l; // in case one of l or r was the pivot, use also need to change the pivot pointer
        }
        else if (left == right)
        {
            if (left < end)
                left++;
            if (right > start)
                right--;
            break;
        }
        else
            break;
    }

    QuicksortSimple(stnInfoList, start, right);
    QuicksortSimple(stnInfoList, left, end); // both partitions are sorted

    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
}

#endif
