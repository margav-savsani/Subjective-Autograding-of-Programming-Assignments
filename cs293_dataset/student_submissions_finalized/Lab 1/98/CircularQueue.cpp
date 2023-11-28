#include <iostream>
#include "queue.h"

using namespace std;

template<typename T>
bool DynamicQueue<T>::isFull()
{
    if((tail+1)%N == head)
    {
        return true;
    }
    return false;
}

template<typename T>
bool DynamicQueue<T>::isEmpty()
{
    if (head == tail)
    {
        return true;
    }
    return false;

}

template<typename T>
void DynamicQueue<T>::grow()
{
    int nextsize = nextSize();
    int *B = new int[nextsize];
    if(tail>head)
        for(int i = head;i<tail;i++)
        {
            B[i-head] = A[i%N];
        }
    else
    {
        for(int i=head; i<N+tail+1;i++)
        {
            B[i-head] = A[i%N];
        }
    }
    N = nextsize;
    head = 0;
    tail = N+tail-head;
    A = B;
}

template<typename T>
unsigned int DynamicQueue<T>::size()
{
    if(isEmpty())
    {
        return 0;
    }
    if(tail>head)
    {
        return tail - head;
    }
    else
    {
        return N + tail - head;
    }
}

template<typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if(isFull())
    {
        grow();
        A[tail] = x;
        tail = (tail + 1)%N;
    }

    A[tail] = x;
    tail = (tail + 1)%N;
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty())
    {
        return false;
    }
    *x = A[head];
    head = (head +1)%N;
    return true;
}
