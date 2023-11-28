#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>

template<typename T>
bool DynamicQueue<T> :: isEmpty(){
  return (tail == 0);   //if tail is at the first element of array it's empty
}

template<typename T>
bool DynamicQueue<T> :: isFull(){
  return (tail == N);   //when tail is at the end of array it's full
}

template<typename T>
unsigned int DynamicQueue<T> :: size(){
  return tail;          //head is always 0 as we shift everytime, so size is tail
}

template<typename T>
void DynamicQueue<T> :: grow(){
  int new_sz = nextSize();       //nextsize of the array
  T *nA = new T[new_sz];         //new array with new size
  for(int i=0; i<tail; i++)
    nA[i] = A[i];                //copy A to nA
  N = new_sz;                    //update N with new size
  delete A;                      //remove A and replace A with nA
  A = nA;
}

template<typename T>
void DynamicQueue<T> :: QInsert(T x){
  if(tail == N)
    grow();                      //grow the array if it is full
    
  A[tail] = x;                   //add next element of queue to the array
  tail++;                        //increment tail
}


template<typename T>
bool DynamicQueue<T> :: QDelete(T *x){
  if(tail == 0)                 //cannot delete if the array is empty
    return false;
    
  x = &A[0];                    //save head pointer of element to be removed
  for(int i=1; i<tail; i++){
    A[i-1] = A[i];              //shift all elements after head one index to the left as A[0] is empty
  }
  tail = tail-1;                //decrement tail to add new element to A[n] which is no longer required
  return true;
}