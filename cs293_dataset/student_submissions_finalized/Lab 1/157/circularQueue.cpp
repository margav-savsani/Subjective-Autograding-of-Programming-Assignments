#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>

#include "queue.h"

template <typename T>
  bool DynamicQueue<T>::bool isEmpty() // is the queue empty?
  {
  if(head==tail) return true;
  else return false;
  };

    template <typename T>
  bool DynamicQueue<T>::unsigned int size() // return the current number of elements in the queue
  {
  if (this->isEmpty()==true) return 0; //if empty return 0
  else if (tail>head) return tail-head; //else return number of elements
  else return N-head+tail;
  };

    template <typename T>
  bool DynamicQueue<T>::bool isFull() // is the queue full?
  {
  int h=head; //convert unsigned int to int to avoid negative number overflow
  int t=tail;
  if ((h-t+N)%N==0) return true;
  else return false;
  };

    template <typename T>
  bool DynamicQueue<T>::void grow() // grow the queue to its next size
  {
  int siz=this->size(); //store size of initial array
  T *B= new T[N+CONST_GROWTH]; //create a new array
  for(int i=0;i<this->size();i++){ //copy elements into the new array
    B[i]=A[(head+i)%N];
    }
  delete[] A; //delete the initial array
  A=B; //initial array pointer points to the new array
  head=0; //reset head and tail
  tail=siz;
  N+=CONST_GROWTH; //set array size to the next size
  };

    template <typename T>
  bool DynamicQueue<T>::void QInsert(T x) // insert given element at tail of the queue; grow array size as necessary
  {
  if(!this->isFull()) {A[tail]=x; tail=(tail+1)%N;}
  else {this->grow(); A[tail]=x; tail=(tail+1)%N;}
  };

    template <typename T>
  bool DynamicQueue<T>::QDelete(T *x) // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  {
  if (this->isEmpty()) return false;
  *x= A[head]; //store element in *T and increment head
  head=(head+1)%N;
  return true;
  };
};
