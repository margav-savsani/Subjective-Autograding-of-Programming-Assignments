#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty() {
    // If the head and the tail of the queue point to the same element, then the queue is empty
    return (head==tail);
}

template <class T> bool DynamicQueue<T>::isFull() {
    // Since my implementation does not confine head and tail to be less than N, (head and tail don't wrap around),
    // instead during insertion and deletion they simply perform operation at correct place by taking mod N
    // The following returns the correct condition
    return (tail==head+N);
}

template <class T> unsigned int DynamicQueue<T>::size(){
    // Since tail is always greater or equal to head in my implementation, the following works:
    return tail-head;
}

template <class T> void DynamicQueue<T>::grow(){
    // Make a new circular array, and copy the elements
    T* bigger;
    bigger = new T[nextSize()];
    for (int i=0; i<N; i++) {
        bigger[i] = A[(head+i)%N];
    }
    // Free the space allocated to the previous array
    delete[] A;
    // A should point to the address of this new bigger array
    A = bigger;
    // New positions of head and tail
    head=0; tail=N;
    N=nextSize();
}

template <class T> void DynamicQueue<T>::QInsert(T x){
    if (isFull()){
        // if the queue is full, grow
        grow();
    }
    // Add the element at the tail, increment tail pointer
    A[tail%N] = x;
    tail++;
}

template <class T> bool DynamicQueue<T>::QDelete(T *x){
    if (isEmpty()){
        return false;
    }
    // store the to-be deleted element in integer pointed to by x 
    *x=A[head%N];
    // increment head pointer
    head++;
    return true;
}

