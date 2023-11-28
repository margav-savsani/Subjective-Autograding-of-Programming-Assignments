#include<iostream>
#include<cmath>
#include<string>
#include "queue.h"

template<typename T> bool DynamicQueue<T>::isEmpty(){
    if(tail == head) { // condition for the queue to be empty
        return true;
    }
    else return false;
}

template<typename T> bool DynamicQueue<T>::isFull(){
    if(tail == N) return true; //whether the queue is empty or not, this is checked by checking tail==N. where N is just a random value, it's just chosen to be N
    else return false;
}

template<typename T> void DynamicQueue<T>::grow(){
    if(isFull()){ // tail == N
        T* B = new T[nextSize()];
        for(int i=0; i<tail; i++){
            B[i] = A[(head + i)%N];  // copying the previous queue to the new queue, tail is already N and head wil become 0. 
        }
        head = 0;
        delete[] A;
        A = B;
        N = nextSize();
        
    }
    
}

template<typename T> unsigned int DynamicQueue<T>::size(){
    if(tail >= head) return tail - head;
    else if(tail == N) return N; // queue is full
    else  return (N - (head - tail)); // tail < head;
}

template<typename T> void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        grow();
        A[tail] = x; // tail already has become N, because the queue was full
        tail = (tail+1)%N;
    }
    else if((tail + 1)%N == head){ // if queue will be full after this insert then tail has to be assigned the value  N.
        A[tail] = x;
        tail = N;
    }
    else{
        A[tail] = x; // trivial case
        tail = (tail+1)%N;
    }
}

template<typename T> bool DynamicQueue<T>::QDelete(T* x){
    if(head == tail) return false; // if empty return false
    else if(tail == N){ // if queue is full, value of tail has to be N, but after deletion tail has to be equal to head, and head has to increment
        tail = head;
        *x = A[head];
        head = (head+1)%N;
        return true;
    }
    else {
        *x = A[head]; // triial case
        head = (head+1)%N;
        return true;
    }   
}