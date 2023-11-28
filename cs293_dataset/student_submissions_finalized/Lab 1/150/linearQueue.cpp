#include <iostream>
#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (tail == head); // if head and tail at same position this will imply queue has no element.
}

template <typename T>
void DynamicQueue<T>::grow()
{
    T *B = new T[nextSize()]; // creating new dynamic array for allocation
    for (int i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
    N = nextSize();
    A = B;
}

// checking size by head and tail position
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (tail - head);
}

template <typename T> // checking difference of head and tail if its equal to N then its full
bool DynamicQueue<T>::isFull()
{
    return (tail - head == N);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (tail < N) // if we are not at end then simply increase.
    {
        A[tail] = x;
        tail++;
        return;
    }

    else if (!isFull() && tail == N) // if we have reached till last but queue has some space in start then shifting the queue to start.
    {
        int size = tail - head;
        T *B = new T[N];
        for (int i = 0; i < size; i++)
        {
            B[i] = A[i + head];
        }
        head = 0;
        tail = size;
        A = B;
        A[tail] = x;
        tail++;
    }

    else if (isFull()) // checking if queue is full and increasing the size while inserting new element.
    {
        grow();
        A[tail] = x;
        tail++;
    }
}

// for delete i am simply changing the head pointer to one step forward so that ur queue don't have access to it there is no
// much difference made if we also  reintialize the deleted element .
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        *x = (A[head]);
        head++;
        return true;
    }
}
