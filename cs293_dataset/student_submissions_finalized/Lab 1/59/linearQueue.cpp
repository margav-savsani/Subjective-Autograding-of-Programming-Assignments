  #include<iostream>
  using namespace std;

  template <typename T> bool DynamicQueue<T>::isEmpty(){
  if(head==tail) return 1;
  else return 0;
  }; // is the queue empty?

  template <typename T> bool DynamicQueue<T>::isFull(){
  if(head==0 && tail==N-1) return 1;
  else return 0;
  }; // is the queue full?

  template <typename T> void DynamicQueue<T>::grow(){
  N+=CONST_GROWTH;
  }; // grow the queue to its next size

  template <typename T> unsigned int DynamicQueue<T>::size(){
  int s=tail-head+1;
  return s;}; // return the current number of elements in the queue

  template <typename T> void DynamicQueue<T>::QInsert(T *x){
  if(tail!=N-1){
  A[N]=x;
  }
  else{
  grow();
  A[N]=x;
  }}; // insert given element at tail of the queue; grow array size as necessary

  template <typename T> bool DynamicQueue<T>::QDelete(T *x){
  if(isEmpty()) return 0;
  else {
  x=A[head];
  return 1;
  }
  }; // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
