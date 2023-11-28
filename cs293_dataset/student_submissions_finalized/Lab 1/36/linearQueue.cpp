#include "queue.h"

// whenever queue becomes empty head and tail are equal
template <class T>
bool DynamicQueue<T>::isEmpty()
{
    return (tail == head);
}

// i consider the queue as full when tail reaches N
template <class T>
bool DynamicQueue<T>::isFull()
{
    return tail == N;
}

// since head is starting and tail is ending the differnce is no of elements in queue
template <class T>
unsigned int DynamicQueue<T>::size()
{
    return tail - head;
}

// when queue is full, a new array with nextSize is created and elements are copied and pointer to old array is changed to new array
template <class T>
void DynamicQueue<T>::grow()
{
    T *B;
    B = new T[nextSize()];         // new array with nextSize
    for (int i = head; i < N; i++) // copying elements into new array
    {
        B[i] = A[i];
    }
    A = B;          // changing pointer to new array
    N = nextSize(); // changing current size
}

// when full first grow the queue then insert
// insert at tail of queue
template <class T>
void DynamicQueue<T>::QInsert(T x)
{
    if (tail == N)
    {
        grow();
    }
    A[tail] = x;
    tail++;
}

// delete at start of queue (at head)
template <class T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (tail - head == 0)
    {
        return false;
    }
    *x = A[head];
    head++;
    return true;
}