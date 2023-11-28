#include "queue.h"
#include <iostream>
using namespace std;

bool DynamicQueue::isEmpty()
{
    return (head == tail);
}

bool DynamicQueue::isFull()
{
    return ((size()) == N - 1); // one block of the array is always kept empty for the tail to reside
}

unsigned int DynamicQueue::size()
{
    return (N - head + tail) % N;
}

void DynamicQueue::QInsert(Journey x)
{

    // cout<<size()<<endl;
    if (isFull())
    {

        grow();
        QInsert(x);
    }

    if (isEmpty())
    {
        A[tail] = x;
        tail = (tail + 1) % N;
    }
    else
    {
        int j = tail;
        int moves = 0;
        while(comparator(A[j - 1], x) && moves != size())
        {
            //std::cout << j << std::endl;
            A[j] = A[(j == 0) ? (N - 1) : j - 1];
            j = (j == 0) ? (N - 1) : j - 1;
            moves++;
        }
        A[j] = x;
        tail = (tail + 1) % N;
    }
}
unsigned int  DynamicQueue::trueSize()
{
    return N;
}
bool DynamicQueue::QDelete(Journey *x)
{
    if (isEmpty())
    {
        return 0;
    }
    else
    {
        *x = A[head];
        head = (head + 1) % N;
        return 1;
    }
}

void DynamicQueue::grow()
{

    if (!isFull())
        return; // should never be executed, just in case

    Journey *Anew = new Journey[nextSize()];
    for (int i = 0; i < size(); i++)
    {

        Anew[i] = A[(head + i) % N];
    }

    tail = size();
    head = 0;
    N = nextSize();
    // Freeing A to prevent memory leaks
    delete[] A;
    A = Anew;
}

bool DynamicQueue::comparator(Journey a, Journey b)
{

    return a.startTime < b.startTime;
}

void DynamicQueue::show()
{
    
    if (tail > head)
    {
        for (int i = head; i < tail; i++)
        {   
            Journey j = A[i];
            cout << j.startTime << " " << j.station1.stationName << " " << j.endTime << " " << j.station2.stationName << endl;
        }
    }
    else
    {
        for (int i = head; i < N; i++)
        {
             Journey j = A[i];
            cout << j.startTime << " " << j.station1.stationName << " " << j.endTime << " " << j.station2.stationName << endl;
        }

        for (int i = 0; i < tail; i++)
        {
             Journey j = A[i];
            cout << j.startTime << " " << j.station1.stationName << " " << j.endTime << " " << j.station2.stationName << endl;
        }
    }
}
