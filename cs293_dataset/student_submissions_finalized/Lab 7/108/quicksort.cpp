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

int partition(listOfObjects<TrainInfoPerStation*> *stnInfoList, int pivot, int l) {
    std::swap(*get(stnInfoList, l-1), *get(stnInfoList, pivot));

    int i {};
    for (int j=0; j<l; j++) {

    }

    return i;
}

int len(listOfObjects<TrainInfoPerStation*> *stnInfoList) {
    listOfObjects<TrainInfoPerStation*> *list = stnInfoList;
    int l {};
    while (stnInfoList) {
        l++;
        list = list->next;
    }
    return l;
}

listOfObjects<TrainInfoPerStation*> * get(listOfObjects<TrainInfoPerStation*> *stnInfoList, int i) {
    listOfObjects<TrainInfoPerStation*> *list = stnInfoList;
    while (i--) list = list->next;
    return list;
}

void Quicksort(listOfObjects<TrainInfoPerStation*> *stnInfoList) {  
    int l = len(stnInfoList);
    if (l == 1) return;
    int pivot = rand()%l;

    int k = partition(stnInfoList, pivot, l);

    Quicksort(stnInfoList);
    Quicksort(get(stnInfoList, k));
}