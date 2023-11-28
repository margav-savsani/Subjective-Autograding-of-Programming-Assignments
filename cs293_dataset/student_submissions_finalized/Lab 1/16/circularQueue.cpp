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
  // I declare queue as full, when number of elemnts are N, as if head and tail are becoming same on adding element\
  I make the tail to point to N(the index which it normally wont take unless given explicitly and modify the inser and \
  remove to work based on the condition checking if tail is N or not)
  return (size() == N);
}
template <typename T> void DynamicQueue<T>::grow() // grow the queue to its next size 
{
  //even if you call explicitly grow() it won't increase queue size if the queue is not full.
  if (isFull())
  {
    //updating the N, to next value that it will take
    N = nextSize();
    T *B = new T[N];
  
    //copying the previous full queue to new queue, also making sure that they are copied such that head is 0 index\
    this implementation takes care that at present our array be curled around
    //Not changing the tail as the queue is declared full only when tail == N(previous capacity of queue) and in new array the tail\
    ahould anyhow take that value
    int m = N - CONST_GROWTH;
    for (int i = 0; i < m - 1; i++)
    {
      B[i] = A[(head + i) % (m)];
    }
    head = 0;
  
    //To prevent memory hogg up
    delete A;
  
    A = B;
  }
}
template <typename T> unsigned int DynamicQueue<T>::size() // return the current number of elements in the queue
{
  //as head and tail can be in either of the two possible configuration where head > tail or tail > head, hence \
  taking modulus to account for that
  //array becomes full only when tail is N
  if (tail == N) return N;
  return ((N + tail - head) % N);
}
template <typename T> void  DynamicQueue<T>::QInsert(T x) // insert given element at tail of the queue; grow array size as necessary
{
  //checking if queue is full, so that we can grow the queue if necessary
  if (isFull())
  {
    grow();
  }
  A[tail] = x;

  //accounting for the fact that tail and head can become same in two cases that queue is full or empty,\
  to tackle that I make the tail to have value N, which it wont ordinarily go on addition, but only when I make it to \
  have that value, which I do when on adding an element the head and tail are becoming same, so in that case I make tail as N\
  thus telling me that array is full 
  if ((tail + 1 % N) == head){
      tail = N;
      return;
  }

  tail = (tail + 1) % N;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x) // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
{
  //making sure queue is not empty
  if(!isEmpty())
  {
    //Now if my tail is at N, during deletion, I need to take it back to the value it was supposed to be that is same as head\
    so if during deletion I have tail as N, I first change it to be same as head and then change the head normally so that now my tail again \
    comes back to non-fulled configuration and queue works properly.
    if(tail == N){
        tail = head;
    }
    *x = A[head];
    head = (head + 1) % N;
    return true;
  }
  return false;
}

