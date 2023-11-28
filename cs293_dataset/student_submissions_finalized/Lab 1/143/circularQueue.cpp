#include<iostream>
using namespace std;
#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){   //queue is said to be empty if size() = 0 i.e; head = tail
  if (head==tail){
    return true;
  }
  else{
    return false;
  }
} 
template <typename T> bool DynamicQueue<T>::isFull(){    //queue is said to be full if size = N-1 
  if(size()== N-1){
    return true;
  }
  else{
    return false;
  }
}
template <typename T> void DynamicQueue<T>::grow(){     //array size is updated and new queue is created    
  T *B; //new dynamic array created
  B = A; //copying elements of A
  int x = N; //prev size
  N = nextSize(); //updating N
  A=new T[N];
  for (int i =0;i<size();i++){
    A[i] = B[(head+i)%x]; //element at head with index 0
  }
  delete [] B;
  
} 
template <typename T> unsigned int DynamicQueue<T>::size(){ //returns the current number of elements in the queue
  return (tail - head + N)%N;
} 
template <typename T> void DynamicQueue<T>::QInsert(T x){
  if(isFull()){        //if array is full we will update the size of the array and then insert the element
    int prev_size = N;
    grow();     
    A[prev_size - 1] = x;      
    tail = prev_size;  
    head = 0;       
  }
  else{
    A[tail] = x;          //inserting element
    tail = (tail + 1)%N;  //updating tail
  }
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){ 
  if(size()==0){
    return false;      //delete operation do not work on empty queue hence return false
  }
  *x = A[head];        //storing the front value of the queue
  head = (head +1)%N;  //updating head
  return true;  
}
