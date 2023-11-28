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

listOfObjects<TrainInfoPerStation*> * 

listOfObjects<TrainInfoPerStation*> * random(listOfObjects<TrainInfroPerSTation*>* stnInfoList, int k)
{
    int num = (rand()%k);
    for(int i = 0; i < num; ++i)
    {
        stnInfoList = stnInfoList->next;
    }
    return stnInfoList;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    int pi
    return;
}
