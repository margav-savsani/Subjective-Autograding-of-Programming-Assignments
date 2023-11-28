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

#define lst listOfObjects<TrainInfoPerStation *>


// gets the element at index i (analogy to an array) of the list with th help of the static array
// every element accessed in O(k) time
// since the array elements are uniformly spread across the list at at k distance
lst* get_element_at(int i, lst* list, lst **array, int K) {
    lst *start = (i/K == 0) ? list : array[i/K - 1];
    for(int j = 0 ; j < (i - K*(i/K)); j++)
        start = start->next;
    return start;
}


// swapping two numerical datas
template<typename T> void swap_t(T &a, T &b) {
   (a ^= b), (b ^= a), (a ^= b);
}


// swaps the data stored in objects referenced by pointers, without disturbing the pointers
void swap_data(lst *a, lst *b) {
    if(a == b)  // no swapping required
        return;

    // swapping the variables stored in object
    swap_t (a->object->journeyCode, b->object->journeyCode);
    swap_t (a->object->stopSeq, b->object->stopSeq);
    swap_t (a->object->arrTime, b->object->arrTime);
    swap_t (a->object->depTime, b->object->depTime);
    for(int i=0; i<7; i++)
        swap_t (a->object->daysOfWeek[i], b->object->daysOfWeek[i]);
}



// Compares two objects based on conditions required and returns a bool indicating the comparison
// ordering wrt to day of week primarily, and if same, by the arrival time
// train with arrival time -1 (i.e. starting at that station), is given the first preference in ordering
bool less_than (TrainInfoPerStation const &a, TrainInfoPerStation const &b) {
    for (int i=0; i<7; i++) {   // comparing with days first
        if (a.daysOfWeek[i] && !b.daysOfWeek[i])
            return 1;
        else if(!a.daysOfWeek[i] && b.daysOfWeek[i])
            return 0;
    }
    return a.arrTime <= b.arrTime;  // comparing with arrival time if day is same
}



// Returns the analogous index of the pivot, which divdes the elements less than and greater than it
int Planner::partition(lst* list, lst **array, int start, int end, int K) {

    // Random Pivot
    int i = start + rand() % (end - start + 1);
    lst *pivot = get_element_at(i, list, array, K);

    // Pivot swapped with last element
    swap_data(pivot, get_element_at(end, list, array, K));
    pivot = get_element_at(end, list, array, K);

    lst *head = get_element_at(start, list, array, K);
    lst *left = head->prev;
    int m = start - 1;      // analogous to index of element of next swap, which is less than pivot 

    lst* ptr = head;    // iterating through the list
    for(int j = start; j <= end; j++) {
        if (less_than(*(ptr->object), *(pivot->object))) {
            left = (left == nullptr) ? head : left->next;
            m++;
            swap_data(left, ptr);       // swap to first part of the list
        }
        ptr = ptr->next;
    }
    return m;   // index of pivot after swappings
}



void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    int N = 0;  // number of elements in the list
  
    lst* temp = stnInfoList;
    while(temp != nullptr) {
        N++;
        temp = temp->next;
    }

    QuicksortSimple(stnInfoList, 0, N-1);
    return;
}



void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    // A few static variable declarations
    static int K = 4; // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    static lst** array = new lst*[(end-start+1)/K];   // array of pointers scattered evenly across the list

    // Increment recursion level on entering the function
    recursionLevel++;
    if (recursionLevel == 0) {    // setting the array of N/K variables at the first function call
        int i = 0;  // analogous to index of object i list
        lst *temp = stnInfoList;
        while(temp != nullptr) {
            if(i % K == 0 && i!=0)      // every K-th element is added to the array
                array[i/K - 1] = temp;
            i++;
            temp = temp->next;
        }
    }

    // The Quicksort algorithm
    if (start < end) {
        int m = partition(stnInfoList, array, start, end, K);
        QuicksortSimple(stnInfoList, start, m-1);
        QuicksortSimple(stnInfoList, m+1, end);
    }

    // Decrement recursion level before exiting the function
    recursionLevel--;

    // freeing the dynamic memory before exiting the original recursion call
    // to make it free for the next call on a different station
    if (recursionLevel == -1) {
        delete[] array;
    }
    return;
}

#endif

