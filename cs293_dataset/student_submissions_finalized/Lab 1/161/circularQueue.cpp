#include<iostream>
#include"queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty() {
  if(head==tail)
    return true;
  else
    return false;
}
 
template <typename T> bool DynamicQueue<T>::isFull() {
  if((head==0 && tail==N-1)||(head==tail+1))
    return true;
  else
    return false;
}

template <typename T> void DynamicQueue<T>::grow(){
  //if called it will increase the size of queue only when it is full.

if( isFull() ){
 
  unsigned int pN = N; 
  N=nextSize();
  T *A1 = new T[N];
  unsigned int temp = head;
  for(int i=0; i< this->size(); i++){
    //for copying all the elements of the previous array to te new array 
    //need to see that the tail can be less than head also so keep a temp
    //which will move to all the elements of the prev queue using modulo with previous N - pN 
    A1[i] = A[temp];
    temp++;
    temp=temp%pN;
  }
  unsigned int t= this->size(); 
  head=0;        // head changed to 0
  tail = t;      //tail moved at the just right of last element 
                 //any element will get inserted in A[tail]
  delete[] A;    //freed the memory taken by A
  A = A1;        //now A pointing to starting index of A1
}
}

template <typename T> unsigned int DynamicQueue<T>::size(){
  //if head is greater size will be total minus empty space 
  if(tail>head) 
    return tail-head;
  else
    return N-(head-tail);
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
  //isFull means the tail is the index of the only space left in the queue ...
  //before filling this space the queue will have to grow so that the tail point to next empty space
  //so head cannot be equal to tail in full condition 
  if(this->isFull()){
    this->grow();
    }
  A[tail] = x;
  tail++;
  tail = tail%N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
  if(this->isEmpty())
    return false;
  else{
    *x = A[head];
    head++;
    return true;
  }
}




































