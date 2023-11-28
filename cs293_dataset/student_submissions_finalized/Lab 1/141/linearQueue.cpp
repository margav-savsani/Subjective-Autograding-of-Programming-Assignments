#include "queue.h"
// cpp code for member functions of class Dynamic Queue -- Linear Queue implementation 

template <typename T>
bool DynamicQueue <T>::isEmpty(){
    return (tail == 0); // if empty, tail is at 0
}

template <typename T>
bool DynamicQueue <T>::isFull(){
    return (tail == N); // if full, elements are filled till N-1, so tail index at N
}

// grow shifts tail index automatically, so use it after inserting an element. 

template <typename T>
void DynamicQueue <T>::grow(){
    if (!isFull()) {
        tail++; // if not full, shift the tail index by 1
    }
    else {
        N  = nextSize(); // using the private member function
        T* new_arr = new T[N]; // create blank array
        for (int i=0; i < tail; i++) { // copy everything into the new array
            new_arr[i] = A[i];
        }
        A = new_arr; // set the new array as the data member
        tail++;
    }
}


template <typename T>
unsigned int DynamicQueue <T>::size() {
    return (tail - head); 
}


template <typename T>
void DynamicQueue <T>::QInsert(T x) {
    A[tail] = x; // first insert the element, then grow the array. If the array is full, grow function would have taken care of that in the previous call
    grow();
}


template <typename T>
bool DynamicQueue <T>::QDelete(T *x) {
    if (isEmpty()) {return false;}
    else {
        // shift each element of the queue back by 1
        x = &A[head]; // index of last element of x is unkown so put as the first element. 
        for (int i = 0; i < tail; i++) {
            A[i] = A[i+1]; // shifts each element back by 1. -- deletion is O(n) for the purpose of saving space in the array. 
        }
        tail--;
        return true;
    }
}