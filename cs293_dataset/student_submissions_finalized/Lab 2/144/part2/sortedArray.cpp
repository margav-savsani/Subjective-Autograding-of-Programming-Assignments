#include <iostream>
#include "planner.h"

void sortedArray::grow()
{ // Increases size of array if filled
    if (size == N)
    {
        Journey *temp = new Journey[N + INCREMENT_SIZE];

        for (int i = 0; i < N; i++)
        {
            temp[i] = A[i];
        }

        delete[] A;
        N += INCREMENT_SIZE;
        A = temp;
    }
    return;
}

int sortedArray::getSize()
{
    return size;
}

sortedArray::sortedArray()
{
    N = SORTED_ARR_SIZE;
    A = new Journey[N];
    size = 0;
}

sortedArray::~sortedArray()
{
    delete[] A;
}

int sortedArray::getIndex(float time)
{ //Gets index of first element with starting time greater than or equal to input time using binary search
    if (size == 0)
    {
        return -1;
    }

    if (A[0].start_time >= time)
        return 0;

    if (A[size - 1].start_time < time)
    {
        return -1;
    }

    int start = 0;
    int end = size - 1;

    while (end > start)
    {
        if (end - start == 1 && A[start].start_time < time && A[end].start_time >= time)
            return end;

        int mid = (start + end) / 2;

        if (A[mid].start_time >= time)
            end = mid;
        else
            start = mid;
    }

    return start;
}

void sortedArray::insert(Journey J)
{ //Inserts element in binary tree
    if (size == N)
        grow();

    int index = getIndex(J.start_time);

    if (index == -1)
    {
        A[size] = J;
        size++;
        return;
    }

    for (int i = size - 1; i >= index; i--)
    {
        A[i + 1] = A[i];
    }
    A[index] = J;
    size++;
};

Journey *sortedArray::getJourney(int index)
{ //Returns pointer to element at given index.
    if (index < 0 || index >= size)
    {
        return nullptr;
    }

    return &A[index];
}