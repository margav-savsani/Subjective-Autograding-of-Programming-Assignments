#include "queue.h"
#include<iostream>
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty() // is the queue empty?
{
  // would be empty only when head and tail index are same
  return (tail == head);
}

template <typename T> bool DynamicQueue<T>::isFull() // is the queue full?
{
  // queue is full when head points at 0 anmd tail at N
  return (head == 0 && tail == N);
}
template <typename T> void DynamicQueue<T>::grow() // grow the queue to its next size 
{
  //even if you call explicitly grow() it won't increase queue size if the queue is not full.
  if (isFull())
  {
    N = nextSize();
    T *B = new T[N];
    if (B == nullptr) return;
    
    //copying each element into the new array
    for (int i = 0; i < N - CONST_GROWTH; i++)
    {
      B[head + i] = A[head + i];
    }
    delete A;
    A = B;
    //delete B;
  }
}
template <typename T> unsigned int DynamicQueue<T>::size() // return the current number of elements in the queue
{
  //as tail - head is the size, it returns that
  return (tail - head);
}
template <typename T> void  DynamicQueue<T>::QInsert(T x) // insert given element at tail of the queue; grow array size as necessary
{
  //checks if array is full and if is then increases the array size
  if(size() == N)
  {
    grow();
  }
  
  //this extra else if makes sure we dont increase the size of array whenever tail is having value N,\
  rather it shifts our array to accomodate any extra space we might have lefgt at the start of the array.
  else if (tail == N)
  {
    //as I want to shift my queue now to make head as 0, and tail as num_elements + 1, which will be equal to size()
    tail = size();
    
    //then I am copying all the elements to rearange my new queue, here as tail 
    for (int j = 0; j < tail; j++)
    {
      A[j] = A[head + j];
    }
    head = 0;
  }
  A[tail] = x;
  tail++;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x) // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
{
  //making sure queue is not empty
  if(!isEmpty())
  {
    *x = A[head];
    head++;
    return true;
  }
  return false;
}
