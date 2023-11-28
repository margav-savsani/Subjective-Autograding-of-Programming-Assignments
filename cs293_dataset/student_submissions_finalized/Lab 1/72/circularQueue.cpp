#include <iostream>
#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
    return (head == tail);
}

template <typename T> bool DynamicQueue<T>::isFull(){
    return (size()==N-1);
}

template <typename T> void DynamicQueue<T>::grow(){
    T *B = new T[nextSize()];
    if(head==0){
    //growing if head is at the zeroth index.
        for(int i = head; i < tail; i++){
        B[i] = A[i];
        }
    }

    if(head!=0){
    //growing if head is not at the zeroth index.
        for(int i = 0; i < tail; i++){
            B[i] = A[i];
        }
        for(int i = head; i < N; i++){
            B[i+CONST_GROWTH] = A[i];
        }
        head = head + CONST_GROWTH;
    }
    N += CONST_GROWTH;
    A = B;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return (N + tail - head)%N ;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    //Checking whether the array is full before inserting a new element.
    if(isFull())grow();
    A[tail] = x;
    tail = (tail+1)%N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty())return false;
    //Storing the element to be deleted at the passed variable.
    *x = A[head];
    head = (head+1)%N;
    return true;
}