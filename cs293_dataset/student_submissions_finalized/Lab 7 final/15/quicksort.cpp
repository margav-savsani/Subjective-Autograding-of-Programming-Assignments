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

int time_val(TrainInfoPerStation *station1) // This functions is used to get a value that can be used for comparing the time of two stations.
{
    int day1 = 0;
    while (!station1->daysOfWeek[day1]) // getting the day when the train runs
    {
        day1++;
    }
    return day1 * 10000 + station1->depTime; // as depTime is of the format HHMM we can take any int having more than 4 zeros.
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

    static int K = 4;               // Parameter to be experimented with
    static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    // Increment recursion level on entering the function
    recursionLevel++;

    static int is; // a sort of a starting index because later we will use a shortened array
    static int il; // a sort of a ending index

    if (recursionLevel == 0) // we assign is and il at the first recursion
    {
        listOfObjects<TrainInfoPerStation *> *curr = stnInfoList;
        is = 0;
        il = -1;
        while (curr != nullptr)
        {
            curr = curr->next;
            il++;
        }
    }
    // cout<<"is"<<is<<"il"<<il<<endl;
    if (il <= is) // base case
    {
        recursionLevel--;
        return;
    }
    static listOfObjects<TrainInfoPerStation *> **arr; // the array which we wil use to calculate the pivots

    if (recursionLevel == 0)
    {
        int n = il - is + 1;                                         // length of list.
        arr = new listOfObjects<TrainInfoPerStation *> *[n / K + 1]; // array of size almost n/k
        listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
        for (int i = 0; i <= n / K; i++)
        {

            arr[i] = currNode;

            if (i == n / K)
                break;
            for (int j = 0; j < K; j++)
            {
                currNode = currNode->next;
            }
        }
    }

    int p = rand() % (il - is + 1) + is; // Taking pivot

    listOfObjects<TrainInfoPerStation *> *pivot = arr[p / K]; // finding pivot through the array
    for (int i = 0; i < p % K; i++)
    {
        pivot = pivot->next;
    }

    listOfObjects<TrainInfoPerStation *> *last = arr[il / K]; // We also need to find the last node for quicksort
                                                              //  We do it similarly using the array
    for (int i = 0; i < il % K; i++)
    {
        last = last->next;
    }

    // cout<<pivot->object->depTime<<ill;
    int pivot_val = time_val(pivot->object); // the time value at the pivot
    // cout << "pivot is"<<p <<"value"<< pivot_val<<" "<<ill;
    listOfObjects<TrainInfoPerStation *> *currNode = arr[is / K];
    for (int i = 0; i < is % K; i++) // As we are passing the whole list every time we need to get at the index at the start is.
    {
        currNode = currNode->next;
    }
    int i = is, j = il;
    swap(pivot->object, last->object); // Taking the pivot to the last
    while (i < j)
    {
        while (time_val(last->object) > pivot_val)
        {
            last = last->prev;
            j--;
        }
        while (time_val(currNode->object) <= pivot_val)
        {
            currNode = currNode->next;
            i++;
            if (i >= j)
                break;
        }
        if (i < j)
        {
            swap(currNode->object, last->object);
        }
    }

    if (j == il) // if j == il then there is no recursion as the size remains same
                 // This means that the pivot was the largest element.
    {
        il = il - 1;
        Quicksort(stnInfoList);
        il = il + 1;
    }
    else
    {
        int temp = il;
        il = j; // changing the end index
        Quicksort(stnInfoList);
        il = temp; // the end index should be assigned its previous value.
        temp = is;
        is = j + 1; // changing the start index.
        Quicksort(stnInfoList);
        is = temp; // the start index should be assigned its previous value.
    }
    // Decrement recursion level before leaving the function

    recursionLevel--;
    return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    if (end <= start)
    {
        return;
    }
    static int K = 2;
    static int recursionLevel = -1;

    recursionLevel++;

    static listOfObjects<TrainInfoPerStation *> **arr;

    if (recursionLevel == 0)
    {
        int n = end - start + 1;
        arr = new listOfObjects<TrainInfoPerStation *> *[n / K + 1];
        listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
        for (int i = 0; i <= n / K; i++)
        {

            arr[i] = currNode;

            if (i == n / K)
                break;
            for (int j = 0; j < K; j++)
            {
                currNode = currNode->next;
            }
        }
    }

    int p = rand() % (end - start + 1) + start;

    listOfObjects<TrainInfoPerStation *> *pivot = arr[p / K];
    for (int i = 0; i < p % K; i++)
    {
        pivot = pivot->next;
    }

    listOfObjects<TrainInfoPerStation *> *last = arr[end / K];
    for (int i = 0; i < end % K; i++)
    {
        last = last->next;
    }

    int pivot_val = time_val(pivot->object);
    listOfObjects<TrainInfoPerStation *> *currNode = arr[start / K];
    for (int i = 0; i < start % K; i++)
    {
        currNode = currNode->next;
    }
    int i = start, j = end;
    swap(pivot->object, last->object);
    while (i < j)
    {
        while (time_val(last->object) > pivot_val)
        {
            last = last->prev;
            j--;
        }
        while (time_val(currNode->object) <= pivot_val)
        {
            currNode = currNode->next;
            i++;
            if (i >= j)
                break;
        }

        if (i < j)
        {
            swap(currNode->object, last->object);
        }
    }

    if (j == end)
    {
        QuicksortSimple(stnInfoList, start, end - 1);
    }
    else
    {
        QuicksortSimple(stnInfoList, start, j);
        QuicksortSimple(stnInfoList, j + 1, end);
    }
    recursionLevel--;
    return;
}

#endif
