#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(head == tail) return true;
    else return false; 
}

template <typename T> bool DynamicQueue<T>::isFull(){ 
    if(tail-head == N) return true;
    else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
    T *temp, *del; //temp shall be the new array whereas del shall be used to delete the previous memory
    temp = new T[nextSize()];
    for(int i = 0; i<N; i++){
        temp[i+head] = A[(i+head)%N];
    }
    del = A;
    A = temp;
    delete del;
    N = nextSize();
    if(tail <= head) tail += N;
    return;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    if(tail >= head) return tail-head;
    else return tail-head+N;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()) grow();
    A[tail] = x;
    tail++;
    if(tail-head != N && tail != head) tail = tail%N;
    else tail = head+N; //if queue is full, tail is set to head+N to check isFull() condition
    return;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    *x = A[head];
    head = (head+1)%N;
    return true;
}
