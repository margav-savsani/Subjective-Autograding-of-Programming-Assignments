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
    return (tail-head==N);
}
template <typename T>
void DynamicQueue<T>::grow()
{
    T* A_new;
    N=nextSize();
    A_new=new T[N];
    for(int i=0;i<tail;i++){
        A_new[i]=A[i];
    }
    A=A_new;
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return tail-head;
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull()){
        grow();
    }
    else if (tail==N){
        for(int i=head;i<N;i++){
            A[i-head]=A[i];
        }
        tail-=head;
        head=0;   
    }
    A[tail]=x;
    tail++;
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