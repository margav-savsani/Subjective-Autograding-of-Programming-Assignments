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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    listOfObjects<TrainInfoPerStation *> * a = stnInfoList;
    int b = 0;

    while (a != nullptr)
    {
        b = b+1;
        a = a->next;
    }
     
    // Put your code here.
}
