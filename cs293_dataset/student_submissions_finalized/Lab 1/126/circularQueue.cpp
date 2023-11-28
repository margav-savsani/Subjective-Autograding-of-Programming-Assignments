#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "queue.h"
using namespace std;
using namespace std::chrono;


#define CONST_GROWTH 1000
#define INIT_SIZE 1000



  template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(tail==head){
        return true;
    }
    else{
        return false;
    }
  } // is the queue empty?
  template <typename T> bool DynamicQueue<T>::isFull(){
    if((tail+2)%N==head){
        return true;
    }
    else{
        return false;
    }
  } // is the queue full?
  template <typename T> void DynamicQueue<T>::grow(){
    T *B;
    B= new T[N+CONST_GROWTH];
    unsigned int temp=head;
    for(unsigned int i=0; i<N; i++){
        B[i]=A[temp];
        temp=(temp+1)%(N+CONST_GROWTH);
    }
    N+=CONST_GROWTH;
    A=B;
    head=0;
    tail=temp;
  } // grow the queue to its next size 
  template <typename T> unsigned DynamicQueue<T>::size(){
    return (tail-head)%N;
  } // return the current number of elements in the queue
  template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(!isFull()){
        A[tail]=x;
        tail=(tail+1)%N;
    }
    else{
        grow();
        A[tail]=x;
        tail=(tail+1)%N;
    }
  } // insert given element at tail of the queue; grow array size as necessary
  template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){
        return false;
    }

    else{
        *x=(A[head]);
        head=(head+1)%N;
        return true;
    }
  } // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise

