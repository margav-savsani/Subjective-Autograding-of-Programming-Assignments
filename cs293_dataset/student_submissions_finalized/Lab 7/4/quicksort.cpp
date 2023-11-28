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
listOfObjects<TrainInfoPerStation *> * parition(listOfObjects<TrainInfoPerStation *> * first, listOfObjects<TrainInfoPerStation *> * last)
{
    listOfObjects<TrainInfoPerStation *> * pivot = first;
    listOfObjects<TrainInfoPerStation *> * front = first;
    int temp = 0;
    while (front != NULL && front != last) {
        if (front->object->arrTime < last->object->arrTime) {
            pivot = first;
            temp = first->object->arrTime;
            first->object->arrTime = front->object->arrTime;
            front->object->arrTime = temp;
            first = first->next;
        }
        front = front->next;
    }
    temp = first->object->arrTime;
    first->object->arrTime = last->object->arrTime;
    last->object->arrTime = temp;
    return pivot;
}void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

  // Put your code here.
}
