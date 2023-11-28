// Shriyank Tatawat 
// 210050147 ...
// Lab 01

#include<iostream>
using namespace std;
#include"queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
    //if head and tail has same index , implies queue is still empty
    if(tail-head==0){
        return true;
    }
    else return false ;
    //returns true if completely empty .
}

template <typename T> bool DynamicQueue<T>::isFull(){
    // By filling queue , if tail reached N and head is still at 0; implies array full
    if(tail-head==N){
        return true;
    }
    else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
    // checks if queue is full , only grows queue size only if it's full.
    // creates new array of N+CONST_GROWTH , copies entire array A to new 
    // and points it to new one ...
    if (isFull()){
        //Below commented part C is to make it more space efficient .
        // T*C;
        T*B;
        B = new T[N+CONST_GROWTH];
        for(int i=0 ; i<N ; i++){
            B[i]=A[i];
        }
        //reassign head and tail ...
        tail=N;
        head=0;
        // C=A;
        A=B;//Now A has N spaces empty in a queue
        N=N+CONST_GROWTH;//changing current size of Array
        // delete C; 
    }
    else return;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    // tail always points where new element to be added , head starting elements.
    return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    // inserts elements , tails reaches more than N , 
    // modulus of N brings it less than N and assign.
    if(isFull()){
        grow();
    }
    int index_to_enter=tail%N;
    A[index_to_enter]=x;
    tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T*x){
    // assign *x to A[head]
    // increases value of head.
    if(!isEmpty()){
        *x=A[head];
        head++;
        return true;
    }
    else return false;
}