#include "queue.h"
template <typename T> bool DynamicQueue<T>::isEmpty(){                   // is the queue empty?
     if(tail==head) return true;
     else return false;
  }; 

template <typename T> bool DynamicQueue<T>::isFull(){                    // is the queue full?
     if(tail-head==N) return true;
     else return false;
  }; 
template <typename T> unsigned int DynamicQueue<T>::size(){              // return the current number of elements in the queue
     return (tail-head);
  }; 
  
  
  template <typename T> void DynamicQueue<T>::grow(){                      // grow the queue to its next size 
       T *B=A;
       A= new T[nextSize()];
       int i=0;
       while(i<size()){
       B[i]=A[i];
       i++;
       }
       N=N+CONST_GROWTH;
       tail=size();
       head=0;
  };
  template <typename T> void DynamicQueue<T>::QInsert(T x){               // insert given element at tail of the queue; grow array size as necessary
     if(isFull()){
      grow();
      A[tail]=x;
      tail++;
      }
     else if(tail==N){
      int B[size()];
      int a=0;
      while(a<size()){
      B[a]=A[a+head];
      a++;
      }
      a=0;
      while(a<size()){
      A[a]=B[a];
      a++;
      }
      tail=size();
      head=0;
      A[tail]=x;
      tail++;
      else if(tail!=N){
      A[tail]=x;
      tail++;
 }     
 };
      
  template <typename T> bool DynamicQueue<T>::QDelete(T *x){                // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if(!isEmpty()){
      *x=A[head];
      head++;
      return true;
     }
   else return false; 
  };
