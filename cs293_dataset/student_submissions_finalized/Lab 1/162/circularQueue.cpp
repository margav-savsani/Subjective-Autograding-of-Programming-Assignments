#include "queue.h"
#include<iostream>
using namespace std;
template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (head == tail);
}
template <typename T>
bool DynamicQueue<T>::isFull()
{
    return ((size())  == N-1); //one block of the array is always kept empty for the tail to reside
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (N - head + tail)%N;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{   
    //cout<<size()<<endl;
    if (isFull())
    {

        grow();
        A[tail] = x;
        tail = (tail+1)%N;
    }
     
    A[tail] = x;
    tail = (tail+1)%N;
    
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return 0;
    }
    else
    {      
        *x = A[head];
        head = (head +1) % N;
        return 1;
    }
}

template <typename T>
void DynamicQueue<T>::grow()
{   
   
    if (!isFull())
        return; // should never be executed, just in case
    
    
    
    T* Anew = new T[nextSize()];
    for (int i = 0; i < size(); i++)
    {   
   
        Anew[i] = A[(head + i)%N];
    }
    
    tail = size();
    head = 0;
    N = nextSize();
    //Freeing A to prevent memory leaks
    delete[] A;
    A = Anew;
    
}

