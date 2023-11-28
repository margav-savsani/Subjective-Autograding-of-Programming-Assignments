#include <iostream>
#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    if (head == tail)
        return true;
    else
        return false;
}
// head = tail implies that the queue is empty

template <typename T>
bool DynamicQueue<T>::isFull()
{
    if ((N-head+tail)%N == N-1)
        return true;
    else
        return false;
}
// there is difference of one element when the queue is full

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return ((N-head+tail)%N);
}

template <typename T>
void DynamicQueue<T>::grow()
{
    T *B;
    B = new T[nextSize()];
    for (int i = head; i < N; i++)
    {
        B[i-head] = A[i];
    }
    for(int i = 0; i < head; i++)
    {
        B[N-head+1] = A[i];
    }
    tail = N;
    head = 0;
    delete[]A;
    A = B;
    N += CONST_GROWTH;
}
// simply grows the size of the queue by copying it on a new queue and updating the address of original queue

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (!isFull())
    {
        A[tail] = x;
        tail = (tail+1)%N;
        // simply add element to the queue
    }
    else
    {   
        grow();
        A[tail] = x;
        tail = (tail+1)%N;
    }
    //grow the queue and insert the element
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        *x = A[head];
        head = (head+1)%N;
        return true;
    }
}