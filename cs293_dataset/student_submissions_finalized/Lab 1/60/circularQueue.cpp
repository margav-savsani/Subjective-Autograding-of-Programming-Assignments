#include <iostream>
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty()
{
//Circular Array is empty, if head equals to tail
//I have defined this as, head can't be equal to tail if it is't empty.
    return head==tail;
}
template <typename T>
bool DynamicQueue<T>::isFull()
{
//if (tail+1)%N equal's head, it means that queue is full
    if((tail+1)%N==head)
    {
        return true;
    }
    else{
        return false;
    }
}
template <typename T>
void DynamicQueue<T>::grow()
{
//I defined a new array named B with N size
    T *B = new T[N];
    for(int i=0; i<N; i++)
    {
         B[i]=A[(head+i)%N]; //copying data
    }
    A = new T[nextSize()]; //redifinig array A with nextSize()
    A = B;
    head=0; //new head
    tail=N-1; //new tail
    N = nextSize(); //updating N
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (N-head+tail)%(N); //size of queue
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if(isFull()) //if queue is full, then its size must be grown
    {
         grow();
    }
    A[tail]=x;
    tail = (tail+1)%N; 
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty()) //is queue is empty, this function returns false
    {
         return false;
    }
    *x = A[head]; //storing value (that will be deleted) in address x
    head=(head+1)%N;
    return true;
}
