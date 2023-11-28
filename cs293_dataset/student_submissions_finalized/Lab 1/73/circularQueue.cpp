#include<iostream>
using namespace std;
#define CONST_GROWTH 1000
#define INIT_SIZE 1000
#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty()
{
    if (size()==0)         //empty when head is equal to tail
        return true;        
    else 
        return false;
}
template <typename T> bool DynamicQueue<T> :: isFull()
{
    if (size()==N)           //if size is max cap then it is N
        return true;
    else 
        return false;
}
template <typename T> void DynamicQueue<T> :: grow()
{
    if (isFull())           //we should add only when array is full(i.e N)
    {
        T *A1;              //we will create a dummy array
        A1=new T[N+1];        //copy the elements of A in it
        unsigned int k=size();
        A1=A;               //incr the size of A
        A=new T[N+CONST_GROWTH+1]; //incr additionally by 1 because head == tail may also indicate full if we dont incr by 1
        N=nextSize();
        for(unsigned int i=0;i<k;i++)   //place the elements back form head 0 to tail=prev max size in original array
            A[i]=A1[(i+head)%(N+1)];
        head=0;
        tail=k;
        return;
    }
    else
        return;
}
template <typename T> unsigned int DynamicQueue<T> :: size()
//there will be 2 cases T>H and other one
{
    if (tail>=head)      //if T>H then it is like linear
        return tail-head;
    else                //in other case where H>=T ,it is like copy the n+1 elements in the array and place at last then it will be like a linear array 
        return (N+tail-head+1);
}
template <typename T> void DynamicQueue<T> :: QInsert(T x)
{
    if (isFull())       //if full grow the size
        grow();
    A[tail]=x;          //add element at tail
    tail=(tail+1)%(N+1);  //modify the tail
}
template <typename T> bool DynamicQueue<T> :: QDelete(T *x)
{
    if (isEmpty())  //if empty we cant do anyuthing
    {
        return false;
    }
    else
    {
        *x=A[head];         //copy the element that we are del
        head=(head+1)%(N+1);    //incr head value
        return true;
    }
}                   //by saran 210050036