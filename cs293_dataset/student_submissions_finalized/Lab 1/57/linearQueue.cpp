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
  return (size() == N);
}

template <typename T>
void DynamicQueue<T>::grow()
{
  T *B;
  B = new T[nextSize()];      //creating new array and copying elements present in array A
  for (int i = 0; i < N; i++)  
  {
    B[i] = A[i];
  }
  delete (A);                //deleting element present in array A to save memory
  A = B;
  head = 0;
  tail = N;
  N = nextSize();
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
  return tail - head;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
  if ((tail == N) && !(isFull()))      //checking to weather rearrange or not
  {
    T *B;
    B = new T[N];
    for (int i = 0; i < size(); i++)   //for rearranging elements present in it
    {
      B[i] = A[head + i];
    }
    delete (A);
    A = B;
    tail = size();
    head = 0;
  }
  if (tail == N)                        //after rearranging still tail=N then we have to grow
    grow();
  A[tail] = x;
  tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
  if (isEmpty())
    return false;
  *x = A[head];
  head++;
  return true;
}