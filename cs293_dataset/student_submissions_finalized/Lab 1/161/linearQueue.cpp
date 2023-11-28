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
  if(tail==N-1)
    return true;
  else
    return false;
}

template <typename T> void DynamicQueue<T>::grow(){ //if called it will increase the size of queue only when it is full.

if( isFull() ){
                                                    
  N=nextSize();   //N increased
  T *A1 = new T[N];  //new array made of size N
  
  for(int i=0; i< this->size(); i++){
    A1[i] = A[i+head];  //all elements copied from A index starting from head till the size of the array
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
  //tail is always greater than the head in linear queue
  return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
  //isFull means the tail is the index of the only space left in the queue ...
  //before filling this space the queue will have to grow so that the tail point to next empty space 
  if(this->isFull())  
    this->grow();
  A[tail] = x;
  tail++;
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




































