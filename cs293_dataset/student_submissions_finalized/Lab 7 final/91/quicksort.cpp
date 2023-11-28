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
#include <cstdlib>

// Comparison operator for TrainInfoPerStation class
bool operator<(TrainInfoPerStation const& t1, TrainInfoPerStation const& t2)
{
    int d1, d2;
    for (int k = 0; k < 7; k++) {
        if (t1.daysOfWeek[k]) {
            d1 = k;
        }
        if (t2.daysOfWeek[k]) {
            d2 = k;
        }
    }

    if (d1 < d2)
        return true;
    else if (d2 < d1)
        return false;
    
    if (t1.depTime < t2.depTime)
        return true;
    else if (t1.depTime > t2.depTime)
        return false;
    if (t1.arrTime < t2.arrTime)
        return true;
    return false;
}

// Swapping TrainInfoPerStation pointers in two nodes of a listOfObjects
void swap(listOfObjects<TrainInfoPerStation*>* n1, listOfObjects<TrainInfoPerStation*>* n2)
{
    TrainInfoPerStation* temp = n2->object;
    n2->object = n1->object;
    n1->object = temp;
}

// Partitions the linked list between starting node (stnInfoList) and endingNode (lastNode) and returns the pivot index based on the pivotValue and start and end index
int partition(listOfObjects<TrainInfoPerStation*>* stnInfoList, listOfObjects<TrainInfoPerStation*>* lastNode, TrainInfoPerStation* pivotValue, int start, int end)
{
    int i = start - 1;
    int j = end + 1;
    while (true) {
        do {
            if(i != start - 1)
                stnInfoList = stnInfoList->next;
            i++;
        } while (*(stnInfoList->object) < *pivotValue);
        do{
            if (j != end+1)
                lastNode = lastNode->prev;
            j--;
        } while (*pivotValue < *(lastNode->object));
        if (i < j)
            swap(stnInfoList,lastNode);
        else
            return j;
    }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    std::cerr << "Use QuicksortSimple\n";
    exit(-1);
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    // A few static variable declarations
    static int K = 4; // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which level of the recursion you are in

    // Base case of the recursion
    if (end <= start)
        return;

    // If the list has 0 elements or 1 element
    if(stnInfoList == nullptr || stnInfoList->next == nullptr)
        return;

    // Stores the node with index end
    listOfObjects<TrainInfoPerStation *>* lastNode = stnInfoList;
    int i = start;
    while (i < end) {
        lastNode = lastNode->next;
        i++;
    }

    //Array to store pointers to linked list nodes at K intervals
    static listOfObjects<TrainInfoPerStation *>** Array;

    // Increment recursion level on entering the function
    recursionLevel++;
    
    if (recursionLevel == 0) {
        // Length of the list
        static int len = end - start + 1;
        srand(time(0));
        
        // Initializing the array
        Array = new listOfObjects<TrainInfoPerStation *>*[len / K + 1];
        //Adding elements at each K interval to the static array
        int i = start;
        listOfObjects<TrainInfoPerStation*>* currList = stnInfoList; 
        while (i < end) {
            if(i % K == 0)
                Array[i / K] = currList;
            currList = currList->next;
            i++;
        }
    }

    // Choosing Pivot in O(K) time
    // Generating random pivot index in [start, end]
    int pivotIndex = start + (rand() % (end - start + 1));

    // Going to pivot in O(K) time using the static pointer array
    listOfObjects<TrainInfoPerStation*>* pivot = Array[pivotIndex / K];
    for(int z = 0; z < pivotIndex % K; z++)
        pivot = pivot->next;

    // Partitioning the list and returning the pivot index
    int p = partition(stnInfoList, lastNode, pivot->object, start, end);
    // newStart stores the linked list node after the pivot index 
    listOfObjects<TrainInfoPerStation*>* newStart = Array[p / K];
    for(int z = 0; z < p % K; z++)
        newStart = newStart->next;
    newStart = newStart->next;

    // Recursive QuickSort calls
    QuicksortSimple(stnInfoList, start, p);
    QuicksortSimple(newStart, p + 1, end);


    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
}

#endif
