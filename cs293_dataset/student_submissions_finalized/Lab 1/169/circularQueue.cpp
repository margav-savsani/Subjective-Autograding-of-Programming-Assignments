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
       for(unsigned int i=0;i<size();i++){
          B[i]=A[i];
       }
       N=N+CONST_GROWTH;
       tail=size();
       head=0;
  };
  // to insert element 
template <typename T> void DynamicQueue<T> :: QInsert(T x){         //
    if(isFull()){
     grow();       
    A[tail%N] = x;
    tail++;
}
}
// to delete element
template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
    if(!isEmpty()) {
    *x = A[head%N]; 
    head++;
    return true;     
}    
else return false;
}
