#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty()
{
  if(head==tail)  // Queue will be empty if we have head==tail i.e. the element to be added next is at head
  {
    return true;
  }
  return false;
}

template <typename T> bool DynamicQueue<T>::isFull()
{
  if(size()==(N-1))  // Queue will be full if size()== N-1
  {
    return true;
  }
  return false;
}

template <typename T> void DynamicQueue<T>::grow()
{
  T *B = new T[nextSize()]; // Creating a new array of size nextSize() i.e. increased size
  for(int i=0; i<N-1; i++)  // Copying elements into new array such that head=0
  {
    B[i]=A[(head+i)%N];
  }
  head= 0;  // head is at 0
  tail= N-1;  // tail is at N-1 as there are N-1 elements
  delete [] A;  // Deleting the previous occupied memory
  A=B;  // A is assigned the address to which our new array B is pointing
  N=nextSize(); // N is updated to its increased value
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
  return (N+tail-head)%N; // if tail>=head then size is tail-head else size is N+tail-head... both of these expressions can be written in one expression (N+tail-head)mod N.
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
  if(isFull())  // If our array is full... then grow it
  {
    grow();
  }
  A[tail]=x;  // After adjusting our array we add the element provided at tail
  tail=(tail+1)%N;  // Updating tail to (tail+1)mod N
}

template <typename T> bool DynamicQueue<T>::QDelete(T* x)
{
  if(isEmpty())
  {
    return false;
  }
  *x=A[head];
  head=(head+1)%N;  // Updating head to (head+1)mod N
  return true;
}
