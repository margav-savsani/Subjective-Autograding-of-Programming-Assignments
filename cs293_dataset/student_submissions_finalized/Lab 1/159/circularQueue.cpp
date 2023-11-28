#include <iostream>
#include <cmath>
#include "queue.h"
using namespace std;
template <typename T> bool DynamicQueue<T>::isEmpty(){
   return (size()==0);
}
template <typename T> bool DynamicQueue<T>::isFull(){
    return (size()==N-1);
}
template <typename T> void DynamicQueue<T>::grow(){
      T *B;
      int x=nextSize();
      B=new T[x];
      if(head==0){
        for(int i=0;i<N;i++){
          B[i]=A[i];
        }
      }
      else{
        for(int i=0;i<tail;i++){
           B[i]=A[i];
        }
        for(int i=head;i<N;i++){
           B[x-N+i]=A[i];
        }
        head=x-N+head;
      }          
      N=x;
      delete [] A;
      A=B;
}
template <typename T> unsigned int DynamicQueue<T>::size(){
    return ((N+tail-head)%N);
}
template <typename T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()){
        grow();
        A[tail]=x;
        tail=(tail+1)%N;
    }
    else A[tail]=x;tail=(tail+1)%N;
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
   if (isEmpty()){
    return false;
   }
   else {
    *x=A[head];
    head=(head+1)%N;
    return true;
   }
}
