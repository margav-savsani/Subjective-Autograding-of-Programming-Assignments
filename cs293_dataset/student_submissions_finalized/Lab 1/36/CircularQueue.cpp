#include "queue.h"

// whenever queue becomes empty head and tail are equal
template <class T>
bool DynamicQueue<T>::isEmpty()
{
    return tail == head;
}

// since it is filled in circular manner tail can be more than N
// difference in tail and head is the size
// when size = N, it is considered fu;;
template <class T>
bool DynamicQueue<T>::isFull()
{
    return tail - head == N;
}

// difference in tail and head is the size
template <class T>
unsigned int DynamicQueue<T>::size()
{
    return tail - head;
}

// when queue is full, a new array with nextSize is created and elements are copied and pointer to old array is changed to new array
// we start from 0 when copying the elements into new array
template <class T>
void DynamicQueue<T>::grow()
{
    j = head; // starting element of old queue
    T *B;
    B = new T[nextSize()];      // new array with increased size
    for (int i = 0; i < N; i++) // copying elements into new array
    {
        B[i] = A[j % N];
        j++;
    }
    A = B;          // changing pointer to new array
    head = 0;       // copying was done from start of array
    tail = N;       // copying ends at previous size
    N = nextSize(); // changing current size
}

// when full first grow the queue then insert
// insert at tail of queue
template <class T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    {
        grow();
    }
    A[tail % N] = x;
    tail++;
}

// delete at start of queue (at head)
template <class T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return false;
    }
    *x = A[head % N];
    head++;
    return true;
}
