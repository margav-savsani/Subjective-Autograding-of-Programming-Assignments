#include<iostream>
#include"queue.h"
using namespace std;
template <class T> bool DynamicQueue<T> :: isEmpty()
{
    return(head==tail);
}
template <class T> bool DynamicQueue <T> :: isFull()
{
    return(tail==N); //here my array is full when tail goes to N
}
template <class T> void DynamicQueue<T> :: grow()
{
    T* ptr=new T[nextSize()]; //creating a new array
    for (int i = 0; i < size(); i++)
    {
        ptr[i]=A[(head+i)]; //copying all the elements to new array
    }
    delete [] A;
    A=ptr;
    N=nextSize();    
}
template <class T>
unsigned int DynamicQueue<T> :: size()
{
    return(tail-head);
}
template <class T>
void DynamicQueue<T> :: QInsert(T x)
{
    //here iam creating a new array if an insert is called when no. of elements are greater than N/2 and the queue is full
    //i.e tail is equal to N
    //if the queue is full(tail==N) and the no. of elements are below N/2 then iam using the same array by shifting the elements 
    //so that the head element is at index 0
    if (isFull())
    {
        if (size()<N/2)
        {
            for (int i = 0; i < size(); i++)
            {
                A[i]=A[head+i];
            }            
        }
        else
            {
                grow();
            }
        tail=size();
        head=0;    
    }
    A[tail]=x;
    tail++;
    return;
}
template <class T>
bool DynamicQueue<T> :: QDelete(T* x)
{
    if (isEmpty())
    {
        return false;
    }
    *x=A[head];
    head++;
    return true;
}
