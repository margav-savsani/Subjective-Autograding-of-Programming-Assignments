#include "queue.h"

/*
If N elements are stored in array of size N then,
when array is full or empty in both cases head==tail.

In order to differentiate between these 2 cases, I put tail = -1 when the array is full.
Because when array is full, the index where next element is to be inserted doesn't make much sense, so tail does not store much useful info anyways.

Hence head == tail will occur only when array is empty
and when array is full tail == -1 will occur.
*/

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head==tail);    // Queue is empty if head equals tail
}

template <typename T>
bool DynamicQueue<T>::isFull(){     
    return (tail == -1);    // Full if tail is -1
}

template <typename T>
void DynamicQueue<T>::grow(){
    unsigned int sz = size();   // Store current size
    T* B = A;                   // Store a pointer to current array
    N = nextSize();             // Get next size
    A = new T[N];               // point A to a new bigger array

    for(unsigned int i=0; i<sz; i++){  // fill the elements in A using B
        A[i] = B[(head+i)%N];
    }
    delete[] B;                 // delete old array

    head = 0;
    tail = sz;
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    if(isFull()){
        return N;
    }
    else{
        return (N-head+tail)%N;
    }
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){   // If array is full then grow
        grow();
    }

    A[tail] = x;
    tail = (tail+1)%N;

    if(tail==head){ // if array gets full put tail = -1
        tail = -1;
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty())
        return false;
    else{
        if(tail == -1){
            tail = head;    // revert back tail from -1 if deleting from full array
        }

        *x = A[head];
        head = (head+1)%N;
        return true;
    }
}