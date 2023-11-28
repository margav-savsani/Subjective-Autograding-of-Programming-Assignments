#include <iostream>
#include "queue.h"

using namespace std;

template<typename T>

bool DynamicQueue<T>::isFull()
{
    if(tail == N)
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
    for(int i = head;i<tail;i++)
    {
        B[i-head] = A[i];
    }
    N = nextsize;
    head = 0;
    tail = tail - head;
    A = B;
}
template<typename T>
unsigned int DynamicQueue<T>::size()
{
    if(head == tail)
    {
        return 0;
    }
        return tail - head;
}
template<typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if(tail == N)
    {
        grow();
        A[tail] = x;
        tail = tail + 1;
    }

    A[tail] = x;
    tail = tail + 1;
}
template<typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if(head == tail)
    {
        return false;
    }
    *x = A[head];
    head = head +1;
    return true;
}


