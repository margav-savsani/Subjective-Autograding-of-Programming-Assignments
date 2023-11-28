#include"queue.h"
#include<iostream>

//Note in this implementation the max number of elements is N-1 for an array of size N as head=tail should mean empty stack only.
template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head == tail); //This is the condition for empty queue
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    bool x = ((head-tail+1)%N == 0);
    return x; //It is full when head is just one behind tail (or head at end and tail at start)
}

template <typename T>
void DynamicQueue<T>::grow(){
    unsigned int M ;
    M = nextSize();
    T *B; // new larger array
    B = new T[M];
    for(int i = 0 ; i< (N-1) ; i++){
        B[i] = A [(tail+i)%N]; //Inserting elements of A into B from start of B
    }
    tail = 0;
    head = N-1; 
    A = B;
    N = M;
    }

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (N+head-tail)%N; //if head> tail this is just head-tail and otherwise it is head+(N-tail) as required
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        grow(); //if full call grow
    }
    A[head] = x; //store in head
    head = (head+1)%N; //increase head 
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return 0;
    *x = A[tail];
    tail = (tail+1)%N; //note we need to do everything mod N
    return 1;
}


