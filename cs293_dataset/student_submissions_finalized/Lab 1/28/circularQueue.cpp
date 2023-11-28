#include <iostream>
#include "queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (size()==0);
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
    return size() == N -1;
}

template <typename T>
void DynamicQueue<T>::grow()
{
    T *b = new T[N + CONST_GROWTH];
    if (tail > head)             //if tail is more than head
    {
        for (int i = 0; i < (tail - head); i++)
        {
            b[i] = A[i + head];
        }
    }
    else
    {
        for (int i = 0; i < N - head; i++)  //copying the elements so that head and tail can be shifted
        {
            b[i] = A[i + head];
        }
        for (int i = 0; i < tail; i++)
        {
            b[N - head + i] = A[i];
        }
        tail = size();
        head = 0;
    }
    delete [] A;
    A=b;
    N=nextSize();
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return ((N-head+tail)%N);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{

    if (size() == N - 1)    //A circular queue has N-1 elements
    {
        grow();
        A[tail] = x;
        tail = (tail + 1) % N;
    }
    else {
        A[tail]=x;
        tail=(tail+1)%N;
    }
}


template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty()){
        return false;
    }

    else{
        *x = A[head];
        head = (head + 1) % N;
        return true;
    }

}
