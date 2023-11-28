#include <iostream>
#include <cmath>
#include "queue.h"
using namespace std;
template <typename T> bool DynamicQueue<T>::isEmpty(){
   return (tail-head==0);
}
template <typename T> bool DynamicQueue<T>::isFull(){
    return (tail-head==N);
}
template <typename T> void DynamicQueue<T>::grow(){
      T *B;
      B=new T[nextSize()];
      for(int i=0;i<N;i++){
        B[i]=A[i];
      }
      N=nextSize();
      delete [] A;
      A=B;
}
template <typename T> unsigned int DynamicQueue<T>::size(){
    return (tail-head);
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()){
        grow();
        A[tail]=x;
        tail++;
    }
    else if(tail==N){
         for(int i=0;i<tail-head;i++){
            A[i]=A[i+head];
         }
         A[tail-head]=x;
         tail=tail-head;
         head=0;
    }
    else A[tail]=x;tail++;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
   if (isEmpty()){
    return false;
   }
   else {
    *x=A[head];
    head++;
    return true;
   }
}

