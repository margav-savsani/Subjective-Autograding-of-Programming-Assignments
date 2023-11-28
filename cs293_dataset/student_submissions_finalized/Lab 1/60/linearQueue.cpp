#include<iostream>
using namespace std;

template <typename T> 
bool DynamicQueue<T> :: isEmpty()
{
//tail equals to head means linear Queue is empty.
    return (tail-head)==0;
}
template <typename T> 
bool DynamicQueue<T> :: isFull()
{
    return (tail-head)==N;
}
template <typename T> 
void DynamicQueue<T> :: grow()
{
//I created a dynamic array named B with next size.
    T *B = new T[N];
    for(int i=0; i<size(); i++)
    {
        B[i]=A[i+head]; //copying data of old array to new array.
    }
    A = new T[nextSize()]; //redifining array A, with nextSize()
    A=B;
    tail=tail-head; //new tail
    head=0; //new head
    N=nextSize();
}
template <typename T> 
unsigned int DynamicQueue<T> :: size()
{
    return (tail-head); //size of linear queue is given by (tail-head)
}
template <typename T> 
void DynamicQueue<T> :: QInsert(T x)
{
    if(tail==N) //is tail reaches at end, grow() function is called
    {
        grow();
    }
    A[tail]=x; //adding element
    tail=tail+1; //new tail
}
template <typename T> 
bool DynamicQueue<T> :: QDelete(T *x)
{
    if(isEmpty()) //if queue is empty, function returns false
    {
        return false;
    }
    *x = A[head]; //storing value at head before deletion in *x(value at address x)
    head = head+1; //updating head.
    
    return true; //function returns the boolean value of !isEmpty()
}
