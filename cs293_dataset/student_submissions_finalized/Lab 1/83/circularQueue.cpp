#include <iostream>
#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (head == tail); //  // it is obv. that if tail is equal to head then the size is zero.
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
    if (size() == N)
        return true; // here I used circular increment. As we need tail to be 0 to start next round.
    else
        return false;
}

template <typename T>
void DynamicQueue<T>::grow()
{
    if (isFull())
    {
        unsigned int growSize = nextSize();
        ;
        T *Anew = A;         // Inrtroducing a array to copy elements of A.
        A = new T[growSize]; // increasing the size of A.
        for (int i = 0; i < N; i++)
        {
            A[i] = Anew[(head + i) % N]; // here I used circular increament.
        }
        head = 0;
        tail = N - 1;
        N = growSize;
        return;
    }
    else
        return;
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return tail - head; // in my case I will increase tail and when I need to access it as index
                        // I will use %N will be clear in furthur code
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    { // Same as linearQueue but for accessing the tail in array I used %N.
        grow();
        A[tail % N] = x;
        tail++;
        return;
    }
    else
    {

        A[tail % N] = x;
        tail++;
        return;
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return false;
    }
    else
    { // same as linearQueue except the %N that has a important role here as we are implementing CircularQueue,
        *x = A[head % N];
        head++;
        return true;
    }
}