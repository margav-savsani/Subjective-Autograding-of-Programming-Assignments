#include "linearQueue.h"


template <typename T> T* LinearQueue<T>::allTravels()
{
  return A;
}

template <typename T> int LinearQueue<T>::size()
{
  return (tail-head); // size is tail-head
}

template <typename T> bool LinearQueue<T>::isFull()
{
  if(tail-head==N)  // Queue will be full if tail-head==N
  {
    return true;
  }
  return false;
}

template <typename T> void LinearQueue<T>::grow()
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

template <typename T> void LinearQueue<T>::QInsert(T x)
{
  if(isFull())  // If our array is full... then grow it
  {
    grow();
  }
  A[tail]=x;  // After adjusting our array we add the element provided at tail
  tail++; // Updating tail to tail+1
}
