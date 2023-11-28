#include <iostream>
#include "queue.h"
template <typename T>
bool DynamicQueue<T>::isEmpty()
{
  return size() == 0;
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
  return (size() == N-1);        //as we defined size as (N+head-tail)%N max value it can reach is N-1
}

template <typename T>
void DynamicQueue<T>::grow()
{
  T *B;
  B = new T[nextSize()];
  for (int i = 0; i < N; i++)    //first created array of big size then copied elements
  {
    B[i] = A[(head+i)%N];
  }
  delete (A);
  A = B;
  head = 0;                       // changed the values of head and tail
  tail = N;
  N = nextSize();
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
  return (N-head+tail)%N;        //as tail can be before head defined size in %N form
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
  
  if (isFull())
    grow();
  A[tail] = x;
  tail=(tail+1)%N;                  
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
  if (isEmpty())
    return false;
  *x = A[head];
  head=(head+1)%N;
  return true;
}
