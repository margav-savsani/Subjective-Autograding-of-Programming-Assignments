#include <iostream>
#include "queue.h"

template <typename T> bool DynamicQueue<T>:: isEmpty(){
    if(head == (tail)){   //after all the elements are deleted head will be equal to tail.
        return true;
    }
    return false;
}

template <typename T> bool DynamicQueue<T>:: isFull(){
    if((tail-head) == N){
        return true;
    }
    return false;
}

template <typename T> void DynamicQueue<T>:: grow(){
    T *B;
    B = new T[nextSize()];  // creating a new array with larger size and transfering the value of previous array to the new array.
    for(int i = 0; i<N; i++){
        B[i] = A[i];
    }
    A = B;
    N = nextSize();   // Since N stores the size of array so increasing it when the size of array is increased.
}

template <typename T> unsigned int DynamicQueue<T>:: size(){
    return (tail-head);
}

template <typename T> void DynamicQueue<T>:: QInsert(T x){
    else if(this->isFull()){ // If it is full the first growing it the inserting the element.
        this->grow();
        A[tail%N] = x;  // using % so that the index remains in range.
        tail++;
    }
    else{
        A[tail%N]=x;
        tail++;
    }
}

template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
    if(!(this->isEmpty())){
        *x = A[head%N];
          // for deleting element increasing head by 1.
        head++;
        return true;
    }
    return false;
    
}
