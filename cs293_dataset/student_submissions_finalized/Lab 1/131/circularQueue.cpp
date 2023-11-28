#include <iostream>
#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty() {
   return(head==tail);  // the queue is empty when the head coincides with the tail
}

template <typename T> bool DynamicQueue<T> :: isFull(){
   unsigned int current = size();  //get the current number of elements in the queue
   if (current==N-1) { // this is to avoid ambiguity which arises when head = tail
    return true;}   //if the number of elements is one less than the size of the queue then the queue is full
    else return false;
}

template <typename T> unsigned int  DynamicQueue<T> :: size(){   //the number of elements stored in the queue
  return((N-head+tail)%N); // the mod is for the wrap around 
}                          

template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if (isFull()){
        grow();  //increase the size of the queueif its full
    }
        A[tail]=x; //insert a new element  at the tail 
        tail=(tail+1)%N; //increment the value of tail
    
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()) return false; // if the queue is empty, element cannot be deleted
    else {
        *x=A[head];  //remove the element at the head 
        head =(head+1)%N;   // increment the value of head
        return true;}
}

template <typename T> void DynamicQueue<T> :: grow(){
    T * Q ;
    int length =nextSize();// get the new length of the queue
    Q=new T[length];  // make a new queue with the increased length
    int j=0;
    for (int i=head;i!=tail;i++){
        i=i %N;
        Q[j]=A[i]; //copy the elements from the filled queue to the new queue
        j++;
    }
    A=Q;
    Q=NULL;
    delete Q;  // prevent memeory wastage 
    head=0;    //reset the values for haed and tail
    tail=N-1;
    N=length;}  // change the value of the current size of the queue
   
