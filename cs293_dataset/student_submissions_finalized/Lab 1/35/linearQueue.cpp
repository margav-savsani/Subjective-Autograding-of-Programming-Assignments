#include<iostream>
#include "queue.h"
using namespace std;

template<typename T> bool DynamicQueue<T>::isEmpty(){
//for the queue to be empty we need the head to coincide with tail.
    if(head == tail) return true;
    else return false;
}

template<typename T> bool DynamicQueue<T>::isFull(){
//for queue to be full the size must be N
    if(this->size() == N ) return true;
    else return false;
}

template<typename T> void DynamicQueue<T>::grow(){
//since we cannot increase the size of an array once it was defined,
//we just need to define a new array and copy paste the elements
    T *B;
    B = new T[this->nextSize()];
    for(int i=head;i<N;i++){
        B[i] = A[i];
    }
    A = B;   
    N = this->nextSize();
    return;
}

template<typename T> unsigned int DynamicQueue<T>::size(){
//size is simply the difference of tail and head modulus N
    return (tail-head);
}

template<typename T> void DynamicQueue<T>::QInsert(T x){
// First if the queue is not full then we can directly insert the element at the tail
    if(!this->isFull()){
        A[tail] = x;
        tail++;
    }
// otherwise we need to use grow function first and do the usual    
    else{
        this->grow();
        A[tail] = x;
        tail++;
    }
    if((tail==N)&&(this->size()!=N)){
        T *B;
        B = new T[N];
        for(int i=0;i< this->size();i++){
            B[i]=A[head+i];
        }
        tail = this->size();
        head = 0;        
        A = B;
    }
    return;
}

template<typename T> bool DynamicQueue<T>::QDelete(T *x){
//if the queue isn't empty we can simply change the head
    if(!this->isEmpty()){
        //A[head]=NULL;
        head++;
        return true;
    }
    else return false;
}