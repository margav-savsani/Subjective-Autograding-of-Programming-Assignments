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

int partition(listOfObjects<TrainInfoPerStation*> *p, listOfObjects<TrainInfoPerStation*> *r, listOfObjects<TrainInfoPerStation*> *stnInfoList){
    listOfObjects<TrainInfoPerStation*> *i = nullptr;
    listOfObjects<TrainInfoPerStation*> *j = p;
    while (j!=r){
        if (j->object->arrTime < r->object->arrTime){
            i = i->next;
            // swap A[j] with A[i]
        }
    }
}

/**
 * @brief Expand the train info list into as many entries as the number of days the train runs.
 * The list can now be sorted based on arrival time and day.
 * 
 * @param stnInfoList The linked List containing elements which are pointers to TrainInfoPerStation objects
 * @returns The sorted linked list
 */
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList) {
    listOfObjects<TrainInfoPerStation*>* train = stnInfoList;
    while (train!=nullptr){
        int first_day = -1;
        for (int i=0; i<7; i++) {
            if (first_day==-1){
                first_day = i;
                continue;
            }
            if (train->object->daysOfWeek[i]){
                listOfObjects<TrainInfoPerStation*> *temp = train->prev;
                train->prev = new listOfObjects<TrainInfoPerStation*>(*train);
                train->prev->next = train;
                train->prev->prev = temp;
                temp->next = train->prev;
            }
        }
    }

}
