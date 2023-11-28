#include<iostream>
#include"queue.h"
using namespace std;
  
   template<typename T> bool DynamicQueue<T>::isEmpty(){ // is the queue empty?
    if(head==tail){ //if head and tail of the queue point to the same index..the queue is empty
        return true;
    }
    return false;
  } 
  template<typename T> bool DynamicQueue<T>::isFull(){// is the queue full?
      if(size()==N){ //checks if the size of the equal to the size of the array representing it
        return true;
    }
    return false;
  } 
  template<typename T> void DynamicQueue<T>::grow(){ 
     T* B;
     if(isFull()){
        B=new T[nextSize()]; //creates a new array with modified size
        for(int i=0;i<N;i++){
            B[i]=A[i];      //copies element of the pre-existing array into the new one
        }
     }
        tail=N;  //reassigns the value of "tail" in the newly created array
        head=0;  //reassigns the value of "head" in the newly created array
        N=nextSize();// The size of the array assumes the new value
        A=B;
  }
   // grow the queue to its next size 
  template<typename T> unsigned int DynamicQueue<T>::size(){ // return the current number of elements in the queue
    return tail-head; //size of the queue equals the difference between the index of head and tail
  } 
  template<typename T> void DynamicQueue<T>::QInsert(T x){ // insert given element at tail of the queue; grow array size as necessary
    if(isFull()){
        grow(); //If the queue is full then the size of the array is increased using the grow()
    }
    else if(tail==N){ //if the array is not full but the tail has reached the end of hte array, then the array undergoes
        for(int i=0;i<size();i++){// a reorganisation wherein all the elements are pushed towards the left. This creates
            A[i]=A[head+i];// empty indices for new elements to be inserted.
        }
        head=0;  //head is reassigned as the elements have been shifted
        tail=size();//tail is reassigned as the elements have been shifted
    }
    A[tail]=x;
  }
  template<typename T> bool DynamicQueue<T>::QDelete(T *x){// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if(isEmpty()){//checks if queue is empty
        return false; 
    }
    *x=A[head];
    head=(head+1); //inrements the position of head so that it shifts towards right
    return true;
  } 

