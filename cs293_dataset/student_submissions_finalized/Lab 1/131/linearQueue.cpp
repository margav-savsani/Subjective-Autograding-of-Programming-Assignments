#include <iostream>
#include "queue.h"

template <typename T> bool DynamicQueue<T> :: isEmpty() { 
   return(head==tail);   // the queue is empty when the head coincides with the tail
}

template <typename T> bool DynamicQueue<T> :: isFull(){
   unsigned int current = size();  //get the current number of elements in the queue
   if (current==N) {
    return true;}   //if the number of elements matches the size of the queue then the queue is full
    else return false;
}

template <typename T> unsigned int  DynamicQueue<T> :: size(){
  return(tail-head);  //the number of elements stored in the queue is the difference between the head and tail
}

template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if (tail== N && head==0){  // if the head and tail are the starting and ending points in a queue respectively, then the queue is full
    grow();}  //increase the size of the queue
    else if(tail == N){ // if head is not at 0 then the queue is not filled
       int j=0;
       for( int i=head; i<N;i++)  //shift the elements to the start of the queue
           {
             A[j]=A[i];
             j++;
           }
       tail=j;
       head=0;
    }
    A[tail]=x; //insert a new element  at the end of the queue
    tail++;  //increment the value of the tail after the element is inserted 
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()) return false; // if the queue is empty, element cannot be deleted
    else {
       *x=A[head]; //remove the element at the head 
       head ++; // increment the value of head
       return true;}
}

template <typename T> void DynamicQueue<T> :: grow(){
    T * Q ; 
     int length =nextSize(); // get the new length of the queue
    Q=new T[length]; // make a new queue with the increased length
   
    for (int i=0;i<N;i++){
        Q[i]=A[i];//copy the elements from the filled queue to the new queue
    } 
    A=Q;
    Q=NULL;
    delete Q; // prevent memeory wastage 
    N=length;// change the value of the current size of the queue 
    return;
    
}


