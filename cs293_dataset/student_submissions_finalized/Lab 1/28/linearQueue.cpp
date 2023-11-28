#include <iostream>
#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (head == tail);
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
    return (head == 0 & tail == N);
}

template <typename T>
void DynamicQueue<T>::grow()
{

    T *b;

    b = new T[N + CONST_GROWTH]; // creating a bigger array

    for (int i = 0; i++; i < N)
    {
        b[i] = A[i];
    }
    delete[] A;
    A = b;
    N = N + CONST_GROWTH;
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (tail - head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (tail < N)
    {
        A[tail] = x;
        tail++;
    }
    else if (tail == N && head == 0)
    {
        grow();
        A[tail] = x;
        tail++;
    }
    else if (tail == N)
    {
        int size = tail - head;
        for (int i = 0; i < size; i++)
        {
            A[i] = A[head + i];
        }
        tail = tail - head;
        head = 0;
        A[tail] = x;
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (tail > head) // Delete only if it has elements
    {
        *x = A[head];
        head++;

        return true;
    }

    else
        return false;
}
