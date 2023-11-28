#include "queue.h"
#include<iostream>
using namespace std;
  template <typename T>bool DynamicQueue<T>:: isEmpty()
  {
    return (head == 0 && tail == 0);  // as the constructor is initialised, i am setting head and tail to 0 when queue is empty	  
  }; 
  template <typename T>bool DynamicQueue<T>:: isFull()
  {
    if(head == 0) 
    {
      if(tail == N) return true; // if head is 0 and tail is N, then queue is full. converse not true
      else return false;
    } 
    else
    {
      if(head == (tail%N)) return true; // is head and tail are at same index, then queue is full
      else return false;      
    }
     
  }; 
  template <typename T>void DynamicQueue<T>:: grow()
  {
    if(!isFull()) return; // is queue isnt full, dont implement grow()
    else 
    {
      T *B = new T[nextSize()]; 
      for(int i = 0;i < N;i++)
      {
	B[i] = A[(head + i)%N]; // creating a new queue and copying elements into it
      }
      delete A; // erasing previous data
      A  = B; // updating existing queue with grown size
      head = 0; // after grow, elements are starting from index 0
      tail = N;
      N = nextSize(); // size grown
    }
  };  
  template <typename T>unsigned int DynamicQueue<T>:: size()
  { 
    if(isFull()) return N; 
    else return ((tail-head)%N); // no of elements between head and tail	  
  }; 
  template <typename T>void DynamicQueue<T>:: QInsert(T x)
  {
    if(isFull()) {grow(); A[tail++] = x; return;} // if queue is full, grow the array and then copy the new element
    else 
    {
      if(size() == N-1)
      {
	A[tail] = x; // if after insertion queue is full then set 
        head = 0; // head to 0 and
        tail = N; // tail to N
        return;	
      }
      else
      {
      A[tail] = x;
      tail = (tail + 1)%N; // else just insert elemnt into index and move tail to ots next position
      return; 
      }      
    }
  }; 
  template <typename T>bool DynamicQueue<T>:: QDelete(T *x)
  {
    if(isEmpty()) return false; // if queue is empty return false
    else
    {
      if(size() == 1) {*x = A[head]; A[head] = 0; head = 0; tail = 0; return true;} // if after deletion queue is empty then set both head and tail to 0
      else {*x = A[head]; A[head] = 0; head = ((head + 1)%N); return true;} // else store the deleted element to given variable and move head to next posm
    }
  };
