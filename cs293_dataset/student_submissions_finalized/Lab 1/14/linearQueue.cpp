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
  if (head == tail)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T> bool DynamicQueue<T>::isFull()
{
  if (tail-head == N) //since N-1 is the last place
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T> void DynamicQueue<T>::grow()
{
  T* B;                        //creating a new Queue with nextsize 
  int p = nextSize();
  B = new T[p];
  for(int i=head; i<tail; i++)
  {
    B[i] = A[i];               //and copying all contents from old queue
  }
  head = 0;
  tail = tail - head;
  delete[] A;                  //deleting old Queue and naming new queue as old
  A = B;
  N = p;                       //updating size variable N to nextsize value
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
  return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
  bool q=isFull();
  if(q)
  {
    grow();
    QInsert(x);
  }
  else
  {
    if(head > 0)              //this is the case when queue is filled at end but is empty for some places in the beginning
    {
      for(int i = 0;i < tail - head +1;i++)
      {
        A[i] = A[i + head];    //pushing all elements to front
      }
      tail = tail - head;
      head = 0;                //updating head and tail values
    }
    A[tail]=x;
    tail++;
  }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
  bool q = isEmpty();
  if (q)
  {
    return false;
  }
  else
  {
    *x = A[head];
    head++;
    for(int i = 0;i < tail - head +1;i++)
      {
        A[i] = A[i + head];    //pushing all elements to front
      }
      tail = tail - head;
      head = 0;                //updating head and tail values
    return true;
  }
}
