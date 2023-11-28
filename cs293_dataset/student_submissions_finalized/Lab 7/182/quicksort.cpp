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
    }
 
    // Giving pivot element its correct position
    

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    int p = Partition(stnInfoList);

    quickSort(arr, start, p - 1);
 
    quickSort(arr, p + 1, end);
}
