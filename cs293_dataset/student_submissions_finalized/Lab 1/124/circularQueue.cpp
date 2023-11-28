// code by Krishna Chaitanya Gorle
#include <iostream>
#include "queue.h"
using namespace std;
// This queue is an array implementation(circular)
template <class T>
unsigned int DynamicQueue<T>::size()
{
  int p = (tail-head+N)% N;
  return p;
  // Some times tail-head may be negative so i have computed size like this
}
template <class T>
bool DynamicQueue<T>::isEmpty()
{
  if (tail == head)
  {
    return true;
  }
  // If head and tail are equal then I assumed that there is no element in the the queue
  else
    return false;
}
template <class T>
bool DynamicQueue<T>::isFull()
{
  if (size() == N-1)
  {
    return true;
  }
  //  If size()= N-1 then queue reached the maximum so there is no place to fill
  else
    return false;
}
template <class T>
void DynamicQueue<T>::grow()
{
  int p = nextSize();
  T *B = new T[p];
  for (int i = 0; i < N; i++)
  {
    {
      B[i] = A[i];
    }
    N = p;
    A = B;
  }
  // The main purpose of the grow() that I understand is if the queue is
  // full then we should extend the queue by this function
  // so first I created the larger array and I copied the previous elements
  // into the larger array
}
template <class T>
void DynamicQueue<T>::QInsert(T x)
{

  if (head > 0 && tail == N)
  {
    for (int i = 0; i < tail - head; i++)
    {
      A[i] = A[head + i];
    }
    tail = tail - head;
    head = 0;
    A[tail] = x;
    tail = (tail+1)%N;
  }
  if (head == 0 && tail == N)
  {
    grow();
    A[tail] = x;
    tail = (tail+1)%N;
  }

  else
  {
    A[tail] = x;
    tail = (tail+1)%N;
  }
}
// The insert() function is used to insert the element
// I have considered three cases
// In first 2 cases I will discuss about what happen if tail is N
// First case: If tail is N but head is not zero(size is not n) then I
//              move the queue to the origin then I added the element
// Second case: if queue is full then we should increase the size of array
//            by grow() function and add the element
// Third case: If tail is not equal to N then we can add directly the element
//Here in every case I written that tail = (tail+1)%N instead of tail =tail+1 because 
//when we try to increment the pointer and we reach the end of the queue, we start from the beginning of the queue.
template <class T>
bool DynamicQueue<T>::QDelete(T *x)
{
  if (isEmpty())
  {
    return false;
  }
  else
  {
    *x = A[head];
    A[head] = 0;
    head = (head+1)%N;
    return true;
  }
  // The main purpose of the delete() function is we should delete the head element
  // and store it in *x so I impelmented in such a way that I stored the element in
  //*x and overwritten its value to zero and increased the haed value
  //Here in every case I written that head = (head+1)%N instead of head =head+1 because 
  //when we try to increment the pointer and we reach the end of the queue, we start from the beginning of the queue.
}
// end of code
