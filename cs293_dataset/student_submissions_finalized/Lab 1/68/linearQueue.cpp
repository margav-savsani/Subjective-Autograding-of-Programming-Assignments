#include "queue.h"
using namespace std;
template <typename T> bool DynamicQueue<T>::isEmpty()
{
    if(tail<=0) return true;
    else return false;
}
template <typename T> bool DynamicQueue<T>::isFull()
{
    if(tail>=N) return true;
    else return false;
}
template <typename T> void DynamicQueue<T>::grow()
{   
    if(!isFull()) return;
    int *B=new int (nextSize());
    for (int i=0;i<N;i++)
    {
        B[i]=A[i];
    }
    N=nextSize();
    A=B;
    cout << N << " " << head << " " << tail << "\n";
}
template <typename T> unsigned int DynamicQueue<T>::size()
{
    return tail;
}
template <typename T> void DynamicQueue<T>::QInsert(T x)
{
    grow();
    // cout << N << " " << head << " " << tail << "\n";
    A[tail++]=x;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty()) return false;
    *x=A[0];
    for(int i=1;i<tail;i++)
    {
        A[i-1]=A[i];
    }
    tail--;
    // cout << N << " " << head << " " << tail << "\n";
    return true;
}