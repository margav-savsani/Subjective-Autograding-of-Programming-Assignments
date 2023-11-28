#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(tail-head == 0) return true;
    else return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
    if(tail == N && head == 0) return true;
    else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
    T *temp, *del; //temp shall be the new array whereas del shall be used to delete the previous memory
    temp = new T[nextSize()];
    for(int i = 0; i<N; i++){
        temp[i] = A[i];
    }
    del = A;
    A = temp;
    delete del;
    N = nextSize();
    return;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(tail == N){
        if(head == 0) grow();
        else{ //shift elements so that the head becomes 0
            for(int i = 0; i < tail-head; i++){
                A[i] = A[i+head];
            }
            int s = size();
            head = 0;
            tail = s;
        }
    }
    A[tail] = x;
    tail++;
    return;    
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false; 
    *x = A[head];
    head++;
    return true;
}


