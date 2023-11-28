#include<iostream>
#include"queue.h"

template <typename T>
bool DynamicQueue<T>::isEmpty(){ // Queue is Empty when both head and tail point to same index in array
    return (tail == head);
}

template <typename T>
bool DynamicQueue<T>::isFull(){ // Queue is full when its size is N
    return (size() == N);
}

template <typename T> 
unsigned int DynamicQueue<T>::size(){ // Difference of head and tail gives the size
    return(tail - head);
}

template <typename T> 
void DynamicQueue<T>::grow(){ // When called, it creates new array of increased size and copies all elemetns to new array
    if (isFull()){
        unsigned int nSize = nextSize(); // get new array size

        T* temp = new T[nSize]; // dynamically create new array

        for(int i= 0; i < N - 1; i++){ // Shift elements to new array
            temp[i] = A[(i + head)%N];
        }

        tail = N - 1; // Update tail
        head = 0; // Update head
        N = nSize;
        delete [] A; // release old memory
        A = temp; // Update pointer
        return;
    }
}

template <typename T> 
bool DynamicQueue<T>::QDelete(T* x){ // If empty -> Return False. Else-> Store element at (head modulo N) to x and shift head by 1
    if(isEmpty()){ 
        return false;
    }

    else{
        *x = A[(head % N)];
        head++;
        return true;  
    }
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){ // If full -> Grow. Add element at (tail % N) and increase it by 1 
    if(isFull()){
        grow();
    }

    A[tail%N] = x; // Add element at tail
    tail++; // Increment tail modulo N
}