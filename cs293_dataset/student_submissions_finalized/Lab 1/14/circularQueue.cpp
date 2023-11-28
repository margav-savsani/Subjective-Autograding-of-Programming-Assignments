/* Roll no : 210050098
   Name : Moningi Srija */

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
using namespace std;

#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty()
{
  return(head == tail);
}

template <typename T> bool DynamicQueue<T>::isFull()
{
  int p = size();
  //tail == head can imply 2 cases here empty or full
  //to avoid the possibility of full assuming that queue is full at the moment it's size reaches N-1
  return(p == N-1);
}

template <typename T> void DynamicQueue<T>::grow()
{
  T* B;
  int t = nextSize();
  B = new T[t];              //creating a new Queue with nextsize 
  for(int i=0; i<N-1; i++)
  {
    B[i] = A[(head+i)%N];
  }
  head = 0;
  tail = N-1;
  delete[] A;                //deleting old Queue and naming new queue as old
  A = B;                     
  N = t;                     //updating size variable N to nextsize value
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
  return (N+tail-head)%N;
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
  bool q = isFull();
  if(q)
  {
    grow();
    QInsert(x);
  }
  else
  {
    A[tail] = x;
    tail = (tail+1)%N;
  }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
  bool r = isEmpty();
  if(r)
  {
    return false;
  }
  else
  {
    *x = A[head];
    head = (head+1)%N;
    return true;
  } 
}
