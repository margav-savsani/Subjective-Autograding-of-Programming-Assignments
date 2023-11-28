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
// sort the list of TrainInfoPerStation objects in stnInfoList. The
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
// function Quicksort with only stnInfoList as its argument. However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead. Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList) {
    // A few static variable declarations
    static int K = 4; // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    // Increment recursion level on entering the function
    recursionLevel++;

    listOfObjects<TrainInfoPerStation *> *n = stnInfoList;

    
    // If you need to set up additional storage (upto n/K TrainInfoPerStation
    // elements), it's ok to do it *once* using static variables/array.
    // Using the static recursionLevel, you can ensure that the storage
    // allocation is done only the first time Quicksort is called, and not
    // in every recursive call.
    //
    // Note that if you allocate space for upto n/K TrainInfoPerStation in
    // each recursive call, you will end up using much more than n/K space
    // overall. So you MUST NOT allocate space in each recursive call.
    //
    // A variable/array defined using static is not created afresh in
    // each recursive call. Instead, a single copy of it is maintained
    // across all recursions.

    // Compares 2 TrainInfoPerStation* variables to check if a > b or not
    auto gt { [] (TrainInfoPerStation* a, TrainInfoPerStation* b) -> bool {
                for (int c=0; c<7; c++) {
                    if (a->daysOfWeek[c] || b->daysOfWeek[c]) {
                        if (a->daysOfWeek[c]) {
                            if (b->daysOfWeek[c] && b->depTime < a->depTime) return true;
                            return false;
                        }
                        return true;
                    }
                }
            }};


    vector<listOfObjects<TrainInfoPerStation*>*> checkpoints;
    int len {};
    if (recursionLevel == 0) {
        // Find length of the list stnInfoList, if needed.
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.

        // Create checkpoints in the linked list at every k elements which 
        // can be accessed in constant time and allow any element of list
        // to accessed in at most O(k) time.
        listOfObjects<TrainInfoPerStation*>* node = stnInfoList;
        while (node) {
            if (!(len%K)) checkpoints.push_back(node);
            node = node->next;
            len++;
        }

        vector<tuple<listOfObjects<TrainInfoPerStation*>*, int, int>> partitions {{stnInfoList, 0, len-1}};  // Partitions to be sorted
        while (!partitions.empty()) {
            const auto [cur, start, end] = partitions.back();
            partitions.pop_back();

            if (start >= end) continue;

            // Choosing the pivot
            int p = start + rand()%(end-start+1);
            auto pivot = checkpoints[p/K];
            for (int i=0; i<p%K; i++) pivot = pivot->next;
            swap(cur->object, pivot->object);

            // Partioning the list
            auto i = cur->next;
            int idx { start+1 };
            while (i->next && gt(cur->object, i->object)) {
                i = i->next;
                idx++;
            }
            auto j = i;
            for (int a=idx; a<=end; a++) {
                if (gt(cur->object, j->object)) {
                    swap(i->object, j->object);
                    i = i->next;
                    idx++;
                }
                j = j->next;
            }
            if (i) swap(cur->object, i->prev->object);

            // Add 2 new partitions to be sorted
            partitions.push_back({i, idx, end});
            partitions.push_back({cur, start, idx-2+(idx>end)});
        }
    }
    
    // Put your code for the core of Quicksort here

    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end) {
    // A few static variable declarations
    static int K = 4; // Parameter to be experimented with
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
    // overall.    So you MUST NOT allocate space in each recursive call.
    //
    // A variable/array defined using static is not created afresh in
    // each recursive call.    Instead, a single copy of it is maintained
    // across all recursions.
    
    if (recursionLevel == 0) {
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.
    }
    
    // Put your code for the core of QuicksortSimple here
    Quicksort(stnInfoList);

    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
}

#endif