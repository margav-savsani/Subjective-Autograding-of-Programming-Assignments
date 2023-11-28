#include <iostream>
using namespace std;
#include <cmath>
#include "queue.h"

template <typename T>bool DynamicQueue<T>::isEmpty(){
      return (head==tail);
  } // is the queue empty?
 
template <typename T>bool DynamicQueue<T> ::isFull(){
      if((head==0&&tail==N-1)||(head==1&&tail==N)){
        return true;
      }
      return ((tail-head+N)%N==N-1);
  } // is the queue full?
template <typename T>void DynamicQueue<T> ::grow(){
      int n=N;
      N=N+CONST_GROWTH;
      T *B;
      B= new T[N];
      for(int i=0;i<n-1;i++){
          B[i]=A[(i+head)%n];
      }
      head=0;
      tail=n-1;
      A=B;
  } // grow the queue to its next size 
template <typename T>unsigned int DynamicQueue<T> ::size(){
      return ((tail-head+N)%N);
  }
template <typename T>void DynamicQueue<T> :: QInsert(T x){
      if(!isFull()){
          A[tail]=x;
          tail=(tail+1)%N;
      }
      
      else{
          grow();
          QInsert(x);
      }
  } // insert given element at tail of the queue; grow array size as necessary
template <typename T>bool DynamicQueue <T>::QDelete(T *x){
      // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
      if(isEmpty()){
          return false;
      }
      else{
          x=&A[head];
          head=(head+1)%N;
          return true;
      }
    }