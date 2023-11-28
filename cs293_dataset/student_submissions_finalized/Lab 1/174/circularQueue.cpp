#include<iostream>
#include"queue.h"
using namespace std;
template <class T> bool DynamicQueue<T> :: isEmpty()
{
    return(head == tail);
}
template <class T> bool DynamicQueue <T> :: isFull()
{
    return((tail+1)%N == head); //here my array is full when N-1 elements are there
}
template <class T> void DynamicQueue<T> :: grow()
{
    T* ptr=new T[nextSize()]; //creating a new array 
    for (int i = 0; i < size(); i++)
    {
        ptr[i] = A[(head+i)%N]; //copying the elements into the new array
    }
    delete []A; 
    A=ptr;
    tail=size();
    head=0; //updating head and tail according to new array
    N=nextSize();
    return;
}
template <class T>
unsigned int DynamicQueue<T> :: size()
{
    if(head<=tail)
        return(tail-head);
    else 
        return(tail+N-head);
}
template <class T>
void DynamicQueue<T> :: QInsert(T x)
{
    //here iam creating a new array if insert is called when my array is full i.e N-1 elemnts are present
    if (isFull()){
        grow();
    }    
    A[tail]=x;
    tail=(tail+1)%N;
}
template <class T>
bool DynamicQueue<T> :: QDelete(T* x)
{
    if (isEmpty())
    {
        return false;
    }
    *x=A[head];
    head=(head+1)%N;
    return true;

}