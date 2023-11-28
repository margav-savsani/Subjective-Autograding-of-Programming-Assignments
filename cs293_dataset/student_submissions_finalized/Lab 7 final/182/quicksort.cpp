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
int Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,int start , int end){
    TrainInfoPerStation pivot() ;
 
    int count = 0;
    int i=start+1;
    TrainInfoPerStation a = ;
    for(int j=0;j<i;j++){
      a=a->next;
    }
    while( i <= end) {
        if (arr[i] <= pivot)
            count++;
            i++;
    }3
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    int p = Partition(stnInfoList);

    quickSort(arr, start, p - 1);
 
    quickSort(arr, p + 1, end);
}
