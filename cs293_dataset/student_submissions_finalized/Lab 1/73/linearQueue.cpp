#include<iostream>
using namespace std;
#define CONST_GROWTH 1000
#define INIT_SIZE 1000
#include "queue.h"
template <typename T> bool DynamicQueue<T> :: isEmpty()
{
    if (head == tail)               //empty if both tail and head are same then no element 
        return true;
    else 
        return false;
}
template <typename T> bool DynamicQueue<T> :: isFull()      //full if tail =N and head =0 if any of this is false then there is space in it
{
    if(size()==N)
        return true;
    else 
        return false;
}
template <typename T> void DynamicQueue<T> :: grow()
{
    if (tail==N && head==0)        //grow will work only when it is full
    {
        T* A1;          //take a dummy arr and copy the elements in it
        A1=new T[N];
        A1=A;
        A=new T[N+CONST_GROWTH];    //increase the size of original array
        N=nextSize();
        for (unsigned int i=head;i<tail;i++)    //copy back the elements in it
            A[i]=A1[i];
        return;
    }
    else 
        return;
}
template <typename T> unsigned DynamicQueue<T> :: size() // size is tail-head 
//here tail stores the index next to last elements index
//head stores first elements index
{
    return tail-head;
}
template <typename T> void DynamicQueue<T> :: QInsert(T x)
{
    if (tail-head==N)       //we will grow if Queue is full and then add the element to it
        grow();
    else if (tail==N)       //if its not full but tail==N then change the head and tail values and the array values
    {                       //because starting elements may be empty
        unsigned int k=size();
        for(unsigned int i=0;i<k;i++)
            A[i]=A[i+head];
        tail=k;
        head=0;
    }
    A[tail]=x;              //add the element
    tail++;
}
template <typename T> bool DynamicQueue<T> :: QDelete(T *x)
{
    if (head==tail)     //do only if queue is non empty 
    {
        return false;
    }
    else
    {
        *x=A[head];     //copy the element into x
        head++;         //remove the first element by incr the head
        return true;
    }
}           //by saran 210050036