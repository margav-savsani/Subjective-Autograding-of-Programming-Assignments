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
    return ((tail+1)%N==head);
}
template <typename T>
void DynamicQueue<T>::grow()
{
    T *b = new T[nextSize()]; // i initilize  a queue b which store current queue
    int i=head,count=0;
    while(count<N-1)
    {
        b[i-head] = A[i%N];
        i++;count++;
    }
    // delete[] A;
    // A = new T[nextSize()];
    // for (int i = 0; i < N-1; i++)
    // {
    //     A[i] = b[i]; // copy element from b to A
    // }
    A=b;
  
    head=0;tail=N-1;
      N=nextSize();
    //delete[] b; // deletion of b for memory release
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (N+tail-head)%N;
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if(isFull()==true){
        grow();
        A[tail]=x;
        tail++;
    }
    else {A[tail]=x;
    tail=(tail+1)%N;}
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (tail == head)
    {
        return false;
    }
    *x = A[head];
    head=(head+1)%N;
    return true;
}