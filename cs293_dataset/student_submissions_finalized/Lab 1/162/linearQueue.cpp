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
    return (size()  == N-1); //one block of the array is always kept empty for the tail to reside
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
   
    return tail - head;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{   
    
    if (isFull())
    {
        grow();
        A[tail++] = x;
    }
    else
    {   
        //if tail reaches the end of the array, but the array isn't full yet, we regrow it
        if (tail >= N-1)
        {
            T* Anew = new T[N];
         
            for (int i = 0; i < size(); i++)
            {
                Anew[i] = A[(head + i)];
            }
            tail = size();
            head = 0;
            delete[] A;
      
            A = Anew;
       
        }
       
        A[tail++] = x;
    }
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
        *x = A[head++];
        if (isEmpty())
        {
            head = tail = 0;
        }
        return 1;
    }
}

template <typename T>
void DynamicQueue<T>::grow()
{
    if (!isFull())
        return; // should never be executed, just in case
    N = nextSize();
    
    T* Anew = new T[N];
    for (int i = 0; i < size(); i++)
    {
        Anew[i] = A[(head + i)]; 
    }
    tail = size();
    head = 0;
    
    //Freeing A to prevent memory leaks
    delete[] A;
    A = Anew;
    
    
}

