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

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    listOfObjects<TrainInfoPerStation *> *rand = stnInfoList;
    int i = 0;

    while(rand != nullptr)
    //Finding length of stnInfoList
    {
        rand = rand->next;
        i++;
    }

    QuicksortSimple(stnInfoList, 0, i-1);
    //Calling quickSortsimple :)

    return;
}

bool fast_dept(TrainInfoPerStation *p1, TrainInfoPerStation *p2)
// If p1 departs fatser than p2 it returns true, else it return false
{
    int i = 0;
    while (!(p1->daysOfWeek[i]) && !(p2->daysOfWeek[i]) and i < 7) i++;

    if (p1->daysOfWeek[i] && !(p2->daysOfWeek[i])) return true;
    else if (!(p1->daysOfWeek[i]) && p2->daysOfWeek[i]) return false;
    else if (p1->depTime != p2->depTime)return (p1->depTime < p2->depTime);
    else return (p1->arrTime < p2->arrTime);
}

listOfObjects<TrainInfoPerStation *> * getPointer(int p, int K, listOfObjects<TrainInfoPerStation *> **Arr)
//Gets element at position p of stnInforList
{
    listOfObjects<TrainInfoPerStation *> *Ans = Arr[p/K];
    //Going to p/K th position

    for (int i = 0; i < p%K; i++)
    //Traversing p%K times
    {
        Ans = Ans->next;
    }
    return Ans;
}

void Swap(listOfObjects<TrainInfoPerStation *> *&a, listOfObjects<TrainInfoPerStation *> *&b)
//Swaps trainstations present in a and b
{
    TrainInfoPerStation * Temp;
    Temp = a->object;
    a->object = b->object;
    b->object = Temp;
}

int partition(int start, int end, int K, listOfObjects<TrainInfoPerStation *> Pivot, listOfObjects<TrainInfoPerStation *> **Arr)
//partition from start to end based on pivot
{
    listOfObjects<TrainInfoPerStation *> *Start = getPointer(start, K, Arr);
    listOfObjects<TrainInfoPerStation *> *End = getPointer(end, K, Arr);

    while(start < end)
    //Quicksort algorithm
    {
        if (fast_dept(Start->object, Pivot.object))
        {
            start++;
            Start = Start->next;
            continue;
        }
        else if (fast_dept(Pivot.object, End->object))
        {
            end--;
            End = End->prev;
            continue;
        }
        else 
        {
            Swap(Start, End);
        }
    }

    return start;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
//The actual ARMAGEDDON
{
    static int K = 4;
    static int recursionLevel = -1;

    if (start >= end) return;
    //Base case

    recursionLevel++;

    static listOfObjects<TrainInfoPerStation *> **Arr;
    //It stores the n/K elements

    if (recursionLevel == 0)
    //Initializing Arr if recursionLevel is 0
    {
        int n;
        n = end + 1;
        Arr = new listOfObjects<TrainInfoPerStation *> *[1+n/K];
        listOfObjects<TrainInfoPerStation *> * Temp = stnInfoList;
        int a = 0;
        while(Temp != nullptr)
        {
            if (a%K == 0) Arr[a/K] = Temp;
            a++;
            Temp = Temp->next;
        }
    }

    srand(time(0));
    int pivot = start + rand()%(end - start + 1);
    listOfObjects<TrainInfoPerStation *> *Pivot = getPointer(pivot, K, Arr);
    //Getting pivot

    int Partition = partition(start, end, K, *Pivot, Arr);
    //Finding Partition

    QuicksortSimple(stnInfoList, start, Partition-1);
    QuicksortSimple(stnInfoList, Partition + 1, end);
    //Reccursion calls

    // Decrement recursion level before leaving the function
    recursionLevel--;
    return;
}

#endif
