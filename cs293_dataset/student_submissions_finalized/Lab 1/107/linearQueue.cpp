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
  if(size()==N)  // Queue will be full if size()=N
  {
    return true;
  }
  return false;
}

template <typename T> void DynamicQueue<T>::grow()
{
  T *B = new T[nextSize()]; // Creating a new array of size nextSize() i.e. increased size
  for(int i=0; i<N; i++)  // Copying elements into new array
  {
    B[i]=A[i];
  }
  delete [] A;  // Deleting the previous occupied memory
  A=B;  // A is assigned the address to which our new array B is pointing
  N=nextSize(); // N is updated to its increased value
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
  return (tail-head); // Size is same as tail-head as our elements are from head, head+1,...,tail-1
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
  if(isFull())  // If our array is full... then grow it
  {
    grow();
  }
  else if(tail==N)  // If next element has to be inserted at N i.e. outside the array range and since isFull() is false... so we have to move all the elements head times back
  {
    for(int i=head; i<N; i++)
    {
      A[i-head]=A[i];
    }
    tail=N-head;  // updated tail will be tail-head as we have moved head times backward
    head=0;   // updated head will be head-head=0 as we have moved head times backward
  }
  A[tail]=x;  // After adjusting our array we add the element provided at tail
  tail++; // Updating tail to tail+1
}

template <typename T> bool DynamicQueue<T>::QDelete(T* x)
{
  if(isEmpty())
  {
    return false;
  }
  *x=A[head];
  head++; // Updating head to head+1
  return true;
}
