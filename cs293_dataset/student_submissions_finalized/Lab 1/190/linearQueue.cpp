#include "queue.h"

//LinearQueue

template <typename T> bool DynamicQueue<T>::isEmpty(){
    if(size() == 0) return true;
    else return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
    //Queue is considered FULL when it has N elements.
    if(size() == N) return true;
    else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
    // grow() is called only when queue is full i.e. when head = 0 and tail = N
    unsigned int New_N = N + CONST_GROWTH;
    T *New_A = new T[New_N];

    //Copying elements from A to New_A
    for(int i=0; i<N; i++){
        New_A[i] = A[i];
    }

    head = 0;
    tail = N;
    N = New_N;
    delete[] A;
    A = New_A;
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    unsigned int queueSize = tail - head;
    return queueSize;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    // For user of this class, the queue is never full, as the queue grows
    // whenever it gets full.
    // Hence while calling QInsert(T x), queue is not full.
    // Even when queue is not full, tail may reach the end i.e. tail = N.
    // In that case I will shift the queue to the left so that there is 
    // space for new insertions.

    if(tail == N){
        for(int i=0; i < size(); i++){
            A[i] = A[head + i];
        }
    }
    tail = tail - head;
    head = 0;

    A[tail] = x;
    tail++;

    if(isFull()){
        grow();
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){
        return false;
    }

    *x = A[head];
    head++;
    return true;
}

