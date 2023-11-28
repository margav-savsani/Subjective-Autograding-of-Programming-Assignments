#include <iostream>
#include "queue.h"

using namespace std;

template<typename T> bool DynamicQueue<T>::isEmpty()
{
    return (size() == 0);
}

template<typename T> bool DynamicQueue<T>::isFull()
{
    return (size() == N); // tail == N and head == 0
}

template<typename T> void DynamicQueue<T>::grow()
{
    unsigned int prevN = N; // stores the previous size
    N = nextSize(); // size is increased
    // B is the bigger array which stores all the values in A
    T * B = new T[N];
    for (int i = 0; i < prevN; i++)
    {
        B[i] = A[i];
    }
    // A points at B's location
    A = B;
}

template<typename T> unsigned int DynamicQueue<T>::size()
{
    return (tail - head);
}

template<typename T> void DynamicQueue<T>::QInsert(T x)
{
    A[tail] = x; // element inserted at the end
    tail++;
    // if we reach the end, push all elements to the start
    if (tail == N)
    {
        for (int i = head; i < tail; i++)
        {
            A[i - head] = A[head];
        }
        head = 0;
        tail = size();
        // if the queue is full, increase the size
        if (isFull()) grow();
    }    
}

template<typename T> bool DynamicQueue<T>::QDelete(T * x)
{
    if (isEmpty()) return 0;
    // x points to the (former) first element
    *x = A[head];
    //(position of) first element changes
    head++;
    return 1;
}