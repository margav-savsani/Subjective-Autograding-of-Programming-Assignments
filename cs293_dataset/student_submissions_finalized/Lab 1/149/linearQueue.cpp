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
    if (tail == N)
        return true;
    else
        return false;
}
// when the tail reaches N, the queue has reached the end. head may or may not be zero.

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return abs(-head + tail + 1);
}
// the expression inside abs() gives the size

template <typename T>
void DynamicQueue<T>::grow()
{
    T *B;
    B = new T[nextSize()];
    for (int i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
    delete []A ;
    A = B;
    head = 0;
    N += CONST_GROWTH;
}
//the queue is copied to an enlarged queue and then the address of original queue is changed to updated one

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (!isFull())
    {
        A[tail] == x;
        tail++;
    }
    //when not full simply add the elements

    else if (isFull() && head != 0)
    {
        for (int i = head; i <= tail; i++)
        {
            T z = A[i];
            A[i - head] = z;
        }
        tail = tail - head;
        head = 0;
        QInsert(x);
    }
    //when head is not at zero and tail is at N, shift the elements ahead.

    else
    {
        grow();
        QInsert(x);
    }
    //queue is full, grow and add elements
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
        head++;
        return true;
    }
}