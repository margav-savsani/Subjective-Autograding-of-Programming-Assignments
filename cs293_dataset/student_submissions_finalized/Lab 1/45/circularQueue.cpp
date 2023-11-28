#include<iostream>
#include "queue.h"

using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (head==tail);
}
template <typename T>
bool DynamicQueue<T>::isFull()
{
    return ((head-tail+N)%N==1);
}
template <typename T>
void DynamicQueue<T>::grow()
{
    T* A_new;
    N=nextSize();
    A_new=new T[N];
    
    unsigned int N_old=N-CONST_GROWTH;
    for(unsigned int i=0;i<N_old-1;i++){
        A_new[i]=A[(i+head)%N_old];
    }
    A=A_new;
    head=0;
    tail=N_old-1;
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (tail-head+N)%N;
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull()){
        grow();
    }
    A[tail]=x;
    tail=(tail+1)%N;
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty()){
        return false;
    }
    *x=A[head];
    head++;
    return true;
}