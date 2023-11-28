#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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

bool firstIsGreater(TrainInfoPerStation * A, TrainInfoPerStation * B)
{
    if (A == nullptr) {return false;}
    if (B == nullptr) {return true;}
    for (int i = 0; i < 7; i++)
    {
        if (A->daysOfWeek[i] == 0 && B->daysOfWeek[i] == 1) return true;
        else if (A->daysOfWeek[i] == 1 && B->daysOfWeek[i] == 0) return false;
        else if (A->daysOfWeek[i] == 0 && B->daysOfWeek[i] == 0) continue;
        else
        {
            if (A->depTime >= B->depTime) return true;
            else return false;
        }
    }
    return false;
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // A few static variable declarations
    static int K = 4; // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    // Increment recursion level on entering the function
    recursionLevel++;
    listOfObjects<TrainInfoPerStation *> * x = stnInfoList;
    if (x == nullptr) return;
    int y = 0;
    while (x->next != nullptr)
    {
        y++;
        x = x->next;
    }
    QuicksortSimple(stnInfoList, 0, y);
    recursionLevel--;
    return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    static int K = 4;
    static int recursionLevel = -1;
    static listOfObjects<TrainInfoPerStation *> ** LIST = (listOfObjects<TrainInfoPerStation *> **)malloc(sizeof(listOfObjects<TrainInfoPerStation *>*));

    if (stnInfoList == nullptr || stnInfoList->object == nullptr || start >= end) return;

    recursionLevel++;
// make the array
    if (recursionLevel == 0)
    {
        static listOfObjects<TrainInfoPerStation *> * tmp = stnInfoList;
        int a = 0, b = 0;
        while (stnInfoList != nullptr)
        {
            if (a % K == 0)
            {
                LIST[b] = stnInfoList;
                b++;
            }
            a++;
            stnInfoList = stnInfoList->next;
        }
        stnInfoList = tmp;
    }
    

// get a random pivot
    int index = rand() % (end - start + 1);
    int array_index = (start + index) / (K + 1);
    int steps = start + index - (K + 1)*array_index;
    listOfObjects<TrainInfoPerStation *> * pivot = LIST[array_index];
    for (int i = 0; i < steps; i++) pivot = pivot->next;
    listOfObjects<TrainInfoPerStation *> * mvr = LIST[0];
    listOfObjects<TrainInfoPerStation *> * initial1 = new listOfObjects<TrainInfoPerStation *>(nullptr), 
                                         * last = new listOfObjects<TrainInfoPerStation *>(nullptr);
    for (int i = 0; i <= end; i++)
    {
        if (mvr == nullptr) return;      
        if (initial1->object != nullptr && last->object != nullptr) break;
        if (i == start) 
        {
            initial1 = mvr;
            initial1->prev = mvr->prev;
        }
        if (i == end)
        {
            last = mvr;
            last->next = mvr->next;
        }
        mvr = mvr->next;
    }
    int p_jcode = pivot->object->journeyCode, 
        p_at = pivot->object->arrTime,
        p_dt = pivot->object->depTime;
    unsigned short p_s = pivot->object->stopSeq;
    bool p_dow[7];
    for (int i = 0; i < 7; i++) p_dow[i] = pivot->object->daysOfWeek[i];

    pivot->object->journeyCode = last->object->journeyCode;
    pivot->object->arrTime = last->object->arrTime;
    pivot->object->depTime = last->object->depTime;
    pivot->object->stopSeq = last->object->stopSeq;
    for (int i = 0; i < 7; i++) pivot->object->daysOfWeek[i] = last->object->daysOfWeek[i];

    last->object->journeyCode = p_jcode;
    last->object->arrTime = p_at;
    last->object->depTime = p_dt;
    last->object->stopSeq = p_s;
    for (int i = 0; i < 7; i++) last->object->daysOfWeek[i] = p_dow[i];
    pivot = last;
    pivot->next = last->next;
    listOfObjects<TrainInfoPerStation *>* initial = initial1->prev;

    int x = 0;
    for (listOfObjects<TrainInfoPerStation *> * start = initial1; start != pivot; start = start->next)
    {
        x++;
        if (firstIsGreater(pivot->object, start->object))
        {
            if (initial == nullptr) {initial = initial1;}
            else {initial = initial->next;}

            // swap the two
            int i_jcode = initial->object->journeyCode, 
                i_at = initial->object->arrTime,
                i_dt = initial->object->depTime;
            unsigned short i_s  = initial->object->stopSeq;
            bool i_dow[7];
            for (int i = 0; i < 7; i++) i_dow[i] = initial->object->daysOfWeek[i];

            initial->object->journeyCode = start->object->journeyCode;
            initial->object->arrTime = start->object->arrTime;
            initial->object->depTime = start->object->depTime;
            initial->object->stopSeq = start->object->stopSeq;
            for (int i = 0; i < 7; i++) initial->object->daysOfWeek[i] = start->object->daysOfWeek[i];

            start->object->journeyCode = i_jcode;
            start->object->arrTime = i_at;
            start->object->depTime = i_dt;
            start->object->stopSeq = i_s;
            for (int i = 0; i < 7; i++) start->object->daysOfWeek[i] = i_dow[i];
        }
    }
    if (initial == nullptr) initial = initial1;
    else initial = initial->next;
    int i_jcode = initial->object->journeyCode, 
        i_at = initial->object->arrTime,
        i_dt = initial->object->depTime;
    unsigned short i_s  = initial->object->stopSeq;
    bool i_dow[7];
    for (int i = 0; i < 7; i++) i_dow[i] = initial->object->daysOfWeek[i];

    initial->object->journeyCode = pivot->object->journeyCode;
    initial->object->arrTime = pivot->object->arrTime;
    initial->object->depTime = pivot->object->depTime;
    initial->object->stopSeq = pivot->object->stopSeq;
    for (int i = 0; i < 7; i++) initial->object->daysOfWeek[i] = pivot->object->daysOfWeek[i];

    pivot->object->journeyCode = i_jcode;
    pivot->object->arrTime = i_at;
    pivot->object->depTime = i_dt;
    pivot->object->stopSeq = i_s;
    for (int i = 0; i < 7; i++) pivot->object->daysOfWeek[i] = i_dow[i];
    pivot = initial;
 
    int m = 0;
    listOfObjects<TrainInfoPerStation * > * tmp4 = LIST[0];
    while (tmp4->next != nullptr)
    {
        bool same = 1;
        same = same * (tmp4->object->depTime == pivot->object->depTime);
        for (int i = 0; i < 7; i++) same = same * (tmp4->object->daysOfWeek[i] == pivot->object->daysOfWeek[i]);
        if (same) break;
        m++;
        tmp4 = tmp4->next;
    }
    if (start < m - 1) QuicksortSimple(stnInfoList, start, m - 1);
    if (m + 1 < end) QuicksortSimple(stnInfoList, m + 1, end);

    recursionLevel--;
    return;
}

#endif