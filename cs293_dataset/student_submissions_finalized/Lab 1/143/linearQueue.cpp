#include<iostream>
using namespace std;
#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){  //queue is said to be empty if size() = 0 i.e; head = tail
  if (head==tail){
    return 1;
  }
  else{
    return 0;
  }
} 
template <typename T> bool DynamicQueue<T>::isFull(){   //queue is said to be full if array is completely filled with elements
  if(size()==N){
    return true;
  }
  else{
    return false;
  }
}
template <typename T> void DynamicQueue<T>::grow(){     //array size is updated and new queue is created 
  N = nextSize();  //size of array is updated
  T *B;            //new array is created
  B = A;           //copying elements of A to B
  A = new T[N];    //new array created with increased size          
  for(int i=0;i<size();i++){
   A[i] = B[i];     //copying previous elements
  }
  delete [] B;     
} 
template <typename T> unsigned int DynamicQueue<T>::size(){ //returns the number of current elements in the queue
  return tail - head ;
} 
template <typename T> void DynamicQueue<T>::QInsert(T x){ //inserts the element x to the queue
 if(isFull()){       //if array is full we will update the size of the array and then insert the element     
    int prev_size = N;
    grow();
    A[prev_size] = x;   //inserting value
    tail = prev_size + 1;
  }
  else if(tail == N){   //if the array is not full but have reached the end then shift the elements to the start of the array with the starting index of the queue as 0
    for(int i = head;i<tail ;i++){
        A[i - head] = A[i]; //shifting the elements
    }
    A[size()] = x;          //inserting the element
    tail = size()+ 1;       //updating tail
    head = 0;               //updating head
  } 
   else{
     A[tail] = x;       //inserting element
     tail++;            //updating tail
   }
   
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x){ //deletes the element at the front of the queue
  if(size()==0){
    return false; //if size = 0 delete function do not work hence returns false
  }
  *x = A[head];   //storing the front value of the queue
  head++;         //updating head
  return true;
  }

