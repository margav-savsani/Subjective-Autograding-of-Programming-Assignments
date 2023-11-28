#include<iostream>
#include"queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
    //if tail and head is zero , which means there are no element in 
    //queue , hence empty
    if(tail==head){
        return true;
    }
    else return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
    //if tail has index N , and head has 0 , means array is full
    if(tail-head==N){
        return true;
    }
    else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
    //increase size of array only when gets full
    if (isFull()){
        //Below commented part C is to make it more space efficient .
        // T*C;
        T*B;
        B = new T[N+CONST_GROWTH];
        for(int i=0 ; i<N ; i++){
            B[i]=A[i];
        }
        // C=A;
        A=B;//Now A has N spaces empty in a queue
        N=N+CONST_GROWTH;//changing current size of Array 
        // delete C;
    }
    else if(tail==N && head!=0){
        tail=tail-head;
        // head=0;
        for(int i=0 ; i<tail ; i++){
            A[i]=A[head+i];
        }
        head=0;
        return;
    }
    else return;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    //it will give , total number of elements 
    // tail never goes more than N , hence tail-head always give 
    // total size.
    return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    // inserts element at N , and grows only if full
    if(isFull()){
        grow();
        A[tail]=x;
        tail++;
    }
    else {
        grow();
        A[tail]=x;
        tail++;
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T*x){
    // increases head , and assigns *x ...
    if(!isEmpty()){
        *x=A[head];
        head++;
        return true;
    }
    else{
        return false;
    }
}

