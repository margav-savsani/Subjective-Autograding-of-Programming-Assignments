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

const int k = 4;

int getnum(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    int num = 0;
    listOfObjects<TrainInfoPerStation *> * tmp = stnInfoList;
    while (tmp != nullptr)
    {
        tmp = tmp->next;
        num++;
    }
    return num;
}

bool make_arr(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> * nodes[size])
{
    int n = getnum(stnInfoList);
    int size = n / k;
    listOfObjects<TrainInfoPerStation *> * tmp = stnInfoList;
    int i;
    for (i = 0; i < size; i++)
    {
        nodes[i] = tmp;
        for (int i = 0; i < k; i++)
        {
            tmp = tmp->next;
            if (tmp == nullptr) break;
        }
    }
    if (i < size) return 0;
    return 1;
}

void swap(TrainInfoPerStation * a, TrainInfoPerStation * b)
{
    TrainInfoPerStation tmp = *a;
    *a = *b;
    *b = tmp;
}

listOfObjects<TrainInfoPerStation *> * getLast(listOfObjects<TrainInfoPerStation *> * stnInfoList)
{
    if (stnInfoList == nullptr) return nullptr;
    listOfObjects<TrainInfoPerStation *> * x = stnInfoList;
    while (x->next != nullptr) x = x->next;
    return x;
}

listOfObjects<TrainInfoPerStation *> * getPivot(listOfObjects<TrainInfoPerStation *> * nodes[], int size)
{
    return nodes[0];
}

listOfObjects<TrainInfoPerStation *> * Partition(listOfObjects<TrainInfoPerStation *> * stnInfoList, listOfObjects<TrainInfoPerStation *> * last)
{
    int n = getnum(stnInfoList);
    int size = n / k;
    listOfObjects<TrainInfoPerStation *> * nodes[size];
    make_arr(stnInfoList, nodes);
    listOfObjects<TrainInfoPerStation *> pivot = getPivot(nodes, size);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void Quicksort(listOfObjects<TrainInfoPerStation *> * stnInfoList)
{
    // Put your code here.
    if (stnInfoList == nullptr) return;
    listOfObjects<TrainInfoPerStation *> prttn = Partition(stnInfoList, getLast(stnInfoList));

    bool validleft = 1, validright = 1;

    listOfObjects<TrainInfoPerStation *> left = stnInfoList;
    listOfObjects<TrainInfoPerStation *> left_last = stnInfoList;
    if (left_last == prttn) validleft = 0;
    if (validleft)
    {
        while (left_last->next != prttn) left_last = left_last->next;
        left_last->next = nullptr;
        Quicksort(left);
    }

    listOfObjects<TrainInfoPerStation *> right = prttn->next;
    listOfObjects<TrainInfoPerStation *> right_last = right;
    if (right == nullptr) validright = 0;
    if (validright)
    {
        // while (left_last->next != prttn) left_last = left_last->next;
        // left_last->next = nullptr;
        // Quicksort(left);
        while (right_last->next != nullptr) right_last = right_last->next;
        Quicksort(right);
    }
    
}
