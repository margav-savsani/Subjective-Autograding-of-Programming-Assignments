#include <iostream>
#include "queue.h"

using namespace std;

template<typename T> bool DynamicQueue<T>::isEmpty()
{
    return (head == tail);
}

template<typename T> bool DynamicQueue<T>::isFull()
{
    // is "full" if the only spot left is right behind the head.
    // done so that we can distinguish between an empty and a full queue.
    return ((head - tail == 1) || (head == 0 && tail == N - 1));
}

template<typename T>  void DynamicQueue<T>::grow()
{
    unsigned int prevN = N; // stores the previous size
    N = nextSize(); // N is increased
    T * B = new T[N]; // new array (larger)
    int qsize = size();
    if (head <= tail) // ie, the (N - 1)th index isn't crossed
    {
        // B is filled from ) to qsize - 1
        for (int i = 0; i < qsize; i++)
        {
            B[i] = A[i + head];
        }
    }
    else // (N - 1)th index is crossed
    {
        // B is filled starting from 0
        for (int i = head; i < N; i++) // from the head to N - 1
        {
            B[i - head] = A[i];
        }
        for (int i = 0; i < tail; i++) // from 0 to the tail
        {
            B[N - head + i] = A[i];
        }
    }
    head = 0;
    tail = qsize;
    A = B;
}

template<typename T> unsigned int DynamicQueue<T>::size()
{
    if (head <= tail) return tail - head;
    else return N - head + tail; // (N-1) - head + 1 + tail
}

template<typename T> void DynamicQueue<T>::QInsert(T x)
{
    if (head - tail == 2 || tail - head == N - 2) grow(); // only one spot before the queue is filled
    A[tail] = x;
    tail = (tail + 1) % N;
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