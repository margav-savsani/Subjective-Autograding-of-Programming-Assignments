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

void swap(listOfObjects<TrainInfoPerStation *> *element1, listOfObjects<TrainInfoPerStation *> *element2)
{
    TrainInfoPerStation *temp = element1->object;
    element1->object = element2->object;
    element2->object = temp;
}

listOfObjects<TrainInfoPerStation *> *randomPivot()
{
}

listOfObjects<TrainInfoPerStation *> *Partition()
{
}

bool checkPrevious(listOfObjects<TrainInfoPerStation *> *i, listOfObjects<TrainInfoPerStation *> *j)
{
    listOfObjects<TrainInfoPerStation *> *a = i;
    listOfObjects<TrainInfoPerStation *> *b = j;
    while (a->next != nullptr)
    {
        if (a->next == b)
            return true;
    }
    return false;
}

void recursiveQuicksort(listOfObjects<TrainInfoPerStation *> *i, listOfObjects<TrainInfoPerStation *> *j)
{
    listOfObjects<TrainInfoPerStation *> *pivot = randomPivot();
    if (checkPrevious(i, j))
    {
        listOfObjects<TrainInfoPerStation *> *part = Partition();
        recursiveQuicksort(i, part);
        recursiveQuicksort(part + 1, j);
    }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // Put your code here.
    listOfObjects<TrainInfoPerStation *> *last = stnInfoList;
    int n = 1;
    while (last->next != nullptr)
    {
        n++;
        last = last->next;
    }

    recursiveQuicksort(stnInfoList, last);
}
