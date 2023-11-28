#include "queue.h"
#include<iostream>
using namespace std;
  template <typename T>bool DynamicQueue<T>:: isEmpty()
  {
    return (head == 0 && tail == 0); // if there's no element then set head and tail to 0	  
  }; 
  template <typename T>bool DynamicQueue<T>:: isFull()
  {
    if(head == 0 && tail == N) return true; // if number of elements in queue is maximum 
    else return false;           // size of queue then array is full
  }; 
  template <typename T>void DynamicQueue<T>:: grow()
  {
    if(!isFull()) return; // if array isn't full then leave it as it is
    else 
    {
      T *B; 
      B = new T[nextSize()]; // creating a new array of increased size
      for(int i = 0;i < N;i++)
      {
	B[i] = A[i]; // copying elements of queue into a new array     
      }
      delete A; // erasing previous queue to construct a new one 
      A = B;
      N = nextSize(); // increasing maximum size of queue
      return;
    }
  };  
  template <typename T>unsigned int DynamicQueue<T>:: size()
  {
    return tail-head; // no of elements between head and tail gives size	  
  }; 
  template <typename T>void DynamicQueue<T>:: QInsert(T x)
  {
    if(isFull()) {grow(); A[tail++] = x; return;} // if the current queue is full, 
                                                  //first grow then insert the element
    else 
    {
      if(tail == N) 
      {
        for(int i = head; i < N; i++)
        {
          A[i-head] = A[i]; // if the elements are upto end of the array although queue
	  A[i] = 0;         // is not full then write the same queue with head=0
        }
        A[N-head] = x; 
	tail = N - head + 1;
	head = 0;
        return;
      }
      else  {
	     A[tail++] = x; // insert the element at tail and move tail by one position
	     return;
            }
    }
  }; 
  template <typename T>bool DynamicQueue<T>:: QDelete(T *x)
  {
    if(isEmpty()) return false; // if queue is empty return false
    else
    {
      if(size() == 1) {*x = A[head]; A[head] = 0; head = 0; tail = 0; return true;} // if there is only one element 
                                                                           // delete and set coinditions to empty queue     
      else {*x = A[head]; A[head] = 0; head++; return true;} // copy deleted element and change position of head by 1 
    }
  };
