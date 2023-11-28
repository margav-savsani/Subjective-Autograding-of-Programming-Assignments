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
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int TrainInfoPerStation.daysOfweek[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i
        = (low
           - 1); // Index of smaller element and indicates
                 // the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (TrainInfoPerStation.daysOfweek[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&TrainInfoPerStation.daysOfweek[i + 1], &TrainInfoPerStation.daysOfweek[high]);
    return (i + 1);
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{ 
   int low=0;
   int high =6;

    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(TrainInfoPerStation.daysOfweek[], high, low);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(TrainInfoPerStation.daysOfweek, low, pi - 1);
        quickSort(TrainInfoPerStation.daysOfweek, pi + 1, high);
    }

   }





}
