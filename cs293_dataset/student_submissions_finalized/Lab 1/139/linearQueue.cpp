#include "queue.h"
#include <cmath>

template <class T>
bool DynamicQueue<T>::isEmpty()
{
    if (head == tail)
    {
        // if head==tail , then queue is empty
        return true;
    }
    return false;
}

template <class T>
bool DynamicQueue<T>::isFull()
{
    if (N == tail)
    {
        // If N==tail, then the queue is Full.
        return true;
    }
    return false;
}

template <class T>
void DynamicQueue<T>::grow()
{
    // Creating a New Empty Array by increasing the size of the Array by nextsize func which grows in A.P. sequence
    T *B;
    B = new T[nextSize()];
    if (isFull())
    {
        // if is full, we need to copy whole array here
        for (int i = 0; i < tail; i++)
        {
            B[i] = A[i];
        }
        // deleting old array to free memory
        delete[] A;
        // Setting our fresh array as our array which is defined in parent class
        A = B;
        // updating N
        N = nextSize();
        // Terminate the function
        return;
    }
    // else, we need to just copy the remaining elements and rearrrange..No need to update N.
    for (int i = 0; i < size(); i++)
    {
        B[i] = A[head + i];
    }
    // storing previous data
    int previoushead = head;
    int previoustail = tail;
    // freeup memory
    delete[] A;
    A = B;
    // resetting head and tail
    head = 0;
    tail = previoustail - previoushead;
}

template <class T>
unsigned int DynamicQueue<T>::size()
{
    // Size of the Linear Queue(Simple mathematic Calculation):
    return tail - head;
}

template <class T>
void DynamicQueue<T>::QInsert(T x)
{
    // Simply Growing the Size of array if the queue is Full.
    if (tail == N)
    {
        grow();
    }

    // and then,Inserting then element.
    A[tail] = x;
    tail++;
}

template <class T>
bool DynamicQueue<T>::QDelete(T *x)
{
    // If empty,return false
    if (isEmpty())
    {
        return false;
    };

    // pointing about to delete element to *x which is passed as argument.
    *x = A[head];
    // increasing head.
    head++;
    return true;
}