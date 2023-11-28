#include <iostream>
#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty(){
    bool var = (head == tail);
    if(var){
        head = tail = 0;
    }
    return var;
}

template <typename T> bool DynamicQueue<T>::isFull(){
    return (tail == N && head == 0);
}

template <typename T> void DynamicQueue<T>::grow(){
    T *B = new T[nextSize()];
    for(int i = head; i < tail; i++){
        B[i] = A[i];
    }
    N += CONST_GROWTH;
    A = B;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return (tail - head) ;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    //Checking whether the array is full before inserting a new element.
    if(isFull())grow();
    bool sd = isEmpty();
    if(tail==N){
    //Copying all the elements at the end of array to the beginning one by one.    
        unsigned int s = size();
        for(int i = 0; i < s; i++){
            A[i] = A[head + i];
        }
        head = 0;
        tail = s;
    }
    A[tail] = x;
    tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty())return false;
    //Storing the element to be deleted at the passed variable.
    *x = A[head];
    head++;
    return true;
}