#include <iostream>
using namespace std;
#include <cmath>
#include "queue.h"

template <typename T>bool DynamicQueue<T>::isEmpty(){
      return (tail==head);
  } // is the queue empty?
template <typename T>bool DynamicQueue<T> ::isFull(){
      return (head==0 && tail==N);
  } // is the queue full?
template <typename T>void DynamicQueue<T> ::grow(){
      N = N+CONST_GROWTH;
      T *B;
      B= new T[N];
      for(int i=0;i<N-CONST_GROWTH;i++){
          B[i]=A[i];
      }
      A=B;
  } // grow the queue to its next size 
template <typename T>unsigned int DynamicQueue<T> ::size(){
      return tail-head;
  } // return the current number of elements in the queue
template <typename T>void DynamicQueue<T> :: QInsert(T x){
      if(tail<N){
          tail++;
          A[tail]=x;
      }
      else if(head>0 && tail==N){
          for(int i=head;i<tail;i++){
              A[i-head]=A[i];
          }
          tail=tail-head;
          head=0;
          A[tail]=x;
          tail++;
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
          head++;
          return true;
      }
    }
