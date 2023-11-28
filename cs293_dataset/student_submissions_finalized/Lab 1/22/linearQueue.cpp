/*
    Name:- Tanmay Arun Patil
    Roll no. :- 210050156
*/

#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty()
{
    if(head == tail) return true;   // As we keep removing elements,  head will keep incrementing by 1. As we remove the last element, head becomes equal to tail.
    else return false;
}

template <typename T> bool DynamicQueue<T>::isFull()
{
    if(tail == N) return true; //For eg, a queue is of size 4. Therefore, N = 4. The tail of a full queue will be 4,
                               //since last element is at index = 3. Hence, tail = 4. 
    else return false;
}

template <typename T> void DynamicQueue<T>::grow()
{
    if(isFull())
    {
        T a[N]; //To store elements of queue
        for(int i = head; i<tail; i++)
        {
            a[i - head] = A[i];
        }

        N = nextSize();

        A = new T[N];
        for(int i = 0; i<tail-head; i++)
        {
            A[i] = a[i];
        }
        tail = tail - head;
        head = 0; //This makes sure that next time grow is used only when the queue is completely filled.

    }

    return;
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
    return (tail - head);
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
    if(isFull()) grow();

    A[tail] = x;
    tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty()) return false;

    *x = A[head];
    head++;

    return true;
}