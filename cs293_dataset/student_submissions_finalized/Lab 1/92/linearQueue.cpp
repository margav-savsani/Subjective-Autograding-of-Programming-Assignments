#include<iostream>
#include<cmath>
#include "queue.h"
using namespace std;

template <typename T> bool  DynamicQueue<T>::isEmpty(){
    return head==tail;
} // is the queue empty?
template <typename T> bool DynamicQueue<T>::isFull(){
    return head==0&&tail==N;
  } // is the queue full?
template <typename T> void DynamicQueue<T>::grow(){
    T *S;
    S=new T[nextSize()];
    for(int i=0;i<N;i++){
        S[i]=A[i];
    }
    A=S;N=nextSize();
  } // grow the queue to its next size 
 template <typename T> unsigned int DynamicQueue<T>::size(){
    return tail-head;
  } // return the current number of elements in the queue
 template <typename T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()){
        grow();
        A[tail]=x;
        tail++;}
    else if(tail==N) {int j=0;
        for(int i=head;i<tail;i++){
            A[j]=A[i];
            j++;}
        head=0;tail=j;}
    else {A[tail]=x;
    tail++;}    
  } // insert given element at tail of the queue; grow array size as necessary
 template <typename T> bool DynamicQueue<T>::QDelete(T *x){if(isEmpty()==1){return 0;}
  else {*x=A[head];
  head++;
  return 1;}

  }