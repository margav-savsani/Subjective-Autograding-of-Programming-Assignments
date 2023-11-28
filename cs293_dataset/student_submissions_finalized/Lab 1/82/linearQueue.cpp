#include<iostream>
#include<cmath>
#include<string>
#include "queue.h"


template<typename T> bool DynamicQueue<T>::isEmpty(){
    if(tail == head) return true; // conditioon for the empty queue
    else return false;
};

template<typename T> bool DynamicQueue<T>::isFull(){
    if(tail == N && head ==0) return true; // consdition fo the queue to become full
    else return false;
}

template<typename T> void DynamicQueue<T>::grow(){
    if(isFull()){
        T* B = new T[nextSize()]; // new queue with larger size
        for(int i=0; i<N; i++){
            B[i] = A[i]; // copy the elements of the previous to the new queue
        }
        delete[] A; // freeing the memeory occupied by the smaller queue
        A = B;
        N = nextSize();
    }

}

template<typename T> unsigned int DynamicQueue<T>::size(){
    return (tail - head); 
}

template<typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()){ // inserting the new element when the queue is full
        grow();
        A[tail++] = x; 
    }
    else if(tail==N && head != 0){ // handling the case when the queue is not full and head !=0 and tail = N
        unsigned int shift = head;
        for(int i=0; i<size(); i++){
            A[i] = A[i + head]; // shifting the elements
        }
        unsigned int ini_size = size();
        head = 0;
        tail = ini_size;
        A[tail++] = x;
    }
    else{
        A[tail++] = x; //insert at the end
    }
}

template<typename T> bool DynamicQueue<T>::QDelete(T* x){
    if(head == tail) return false; // if queue is empty, then return false

    else{
        *x = A[head++]; // assigning the value of the deleted element at location x.
        return true;
    }
}