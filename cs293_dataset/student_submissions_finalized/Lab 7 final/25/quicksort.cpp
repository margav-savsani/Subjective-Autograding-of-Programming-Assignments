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

int calculate_length(listOfObjects<TrainInfoPerStation*> *stnInfoList, int *J){
    listOfObjects<TrainInfoPerStation *> *head = stnInfoList;
    int n = 0;
    while (head != nullptr)
    {
        n++;
        head = head->next;
    }
    *J = 10;
    return n;  
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

listOfObjects<TrainInfoPerStation*> * getElementAtIndex(int n, listOfObjects<TrainInfoPerStation*>** segments, int K, listOfObjects<TrainInfoPerStation*> *trains){
    int chunk = n/K;
    listOfObjects<TrainInfoPerStation*> *head = segments[chunk];
    for (int i=0; i<n - K*chunk; i++) {
        head = head->next;
    }
    return head;
}


bool operator<(TrainInfoPerStation a, TrainInfoPerStation b){
    for (int i=0; i<7; i++) {
        if (a.daysOfWeek[i]!=b.daysOfWeek[i]){
            return a.daysOfWeek[i];
        }
    }
    // Now the days are the same
    return (a.depTime < b.depTime);
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // A few static variable declarations
    static int K = 10; // Parameter to be experimented with
    // This can be used to find out at which level of the recursion you are in
    static int recursionLevel = -1;
    static int n = 0;
    static listOfObjects<TrainInfoPerStation*> **segments;
    static int num; // No.of segements
    static int start = 0;
    static int end;

    // Increment recursion level on entering the function
    recursionLevel++;

    // If you need to set up additional storage (upto n/K TrainInfoPerStation
    // elements), it's ok to do it *once* using static variables/array.
    // Using the static recursionLevel, you can ensure that the storage
    // allocation is done only the first time Quicksort is called, and not
    // in every recursive call.
    int *J = &K;
    // Note that if you allocate space for upto n/K TrainInfoPerStation in
    // each recursive call, you will end up using much more than n/K space
    // overall.  So you MUST NOT allocate space in each recursive call.
    //
    // A variable/array defined using static is not created afresh in
    // each recursive call.  Instead, a single copy of it is maintained
    // across all recursions.

    if (recursionLevel == 0)
    {
        // Find length of the list stnInfoList, if needed.
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.

        n = calculate_length(stnInfoList, J);
        num = (n-1) / K + 1; // number of extra pointers created
        end = num - 1;
        segments = new listOfObjects<TrainInfoPerStation*>* [num];
        listOfObjects<TrainInfoPerStation *> *head = stnInfoList;
        for (int i=0; i<n; i++) {
            if (i%K==0){
                segments[i/K] = head; //initialising the n/K pointers 
            }
            head = head->next;
        }

        for (int i=0; i<num; i++) {
            // For each segment

            // Recursively Sort this now
            start = i*K;
            end = (i!=num-1 ? start + K-1 : n-1);
            Quicksort(stnInfoList);
        }

        delete[] segments; //clean up the segments array before leaving, preventing memory leaks
    }

    else {
        // Put your code for the core of Quicksort here
        if (start>=end){
            if (recursionLevel==0){
                n=0;
            }
            recursionLevel--;
            return;
        }
        int pivot = rand()%(min(K, end - start)); // should be length of interval
        listOfObjects<TrainInfoPerStation*> * pivotNode = getElementAtIndex(start + pivot, segments, K, stnInfoList);
        TrainInfoPerStation* temp = pivotNode->object;

        listOfObjects<TrainInfoPerStation*>* head = segments[start/K]; // wrong, find start here
        for (int i=0; i<start - K*((int)start/K); i++) {
            head = head->next;
        }
        listOfObjects<TrainInfoPerStation*>* startNode = head;
        listOfObjects<TrainInfoPerStation*> *last = head;
        for (int j=0; j<end-start; j++) {
            // find last here
            last = last->next;
        }
        /*
        if (start!=K*(num-1)){
            last = segments[start/K+1]->prev;
        }
        else {
            last = segments[num-1];
            while (last->next!=nullptr){
                last = last->next;
            }
        }*/
        pivotNode->object = last->object;
        last->object = temp;

        // Partition
        listOfObjects<TrainInfoPerStation*>* tail = nullptr;
        pivot = -1;
        while (head!=last){
            if (*(head->object) < *(last->object)){
                tail = (tail==nullptr ? startNode : tail->next);
                pivot++;
                swap(tail->object, head->object);
            }
            head = head->next;
        }
        tail = (tail==nullptr ? startNode : tail->next);
        pivot++;
        swap(tail->object, last->object);
        // Partition Complete
        cout<<"pivot "<<pivot<<endl;

        int old_end = end;
        end = start + pivot-1;
        cout<<"starting at "<<start<<", ending at "<<end<<endl;
        Quicksort(stnInfoList);
        end = old_end;
        start = start + pivot + 1;
        cout<<"starting at "<<start<<", ending at "<<end<<endl;
        Quicksort(stnInfoList);
    }


    // Decrement recursion level before leaving the function
    if (recursionLevel==0){
        n=0;
    }
    recursionLevel--;
    return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    // A few static variable declarations
    static int K =4;               // Parameter to be experimented with
    // This can be used to find out at which level of the recursion you are in
    static int recursionLevel = -1; 

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
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.
    }

    // Put your code for the core of QuicksortSimple here

    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
}

#endif
