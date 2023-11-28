// cpp code for member functions of class Dynamic Queue -- Cicular Queue implementation 

#include "queue.h"

template <typename T>
bool DynamicQueue <T>::isEmpty(){
    // if head and tail pointer coincide, array is empty
    return (head == tail);
}

template <typename T>
bool DynamicQueue <T>::isFull(){
    // for consistency and head == tail representing empty queue and not full.
    //  I will fill only N-1 elements in a Queue of size N before declaring it full. 
    return (size() == N-1);
}

// grow shifts tail index automatically, so use it after inserting an element. 
template <typename T>
void DynamicQueue <T>::grow(){
    // if not full, tail index increments by modulo 1. If tail index was N-1, it will go to 0.
    if (!isFull()) {
        tail = (tail + 1) % N;
    }

    // if circular array is full -- 
    else {
        
        // size of new array increments by CONST_GROWTH
        T* new_arr = new T[nextSize()];

        // for indices from head to tail - 1 (wrapped around upon reaching N - 1) -- if tail = 0, considers stopping at N-1 (-1 mod N = N - 1)
        for (int i=head; i != (tail - 1)%N; i = (i+1)%N) {
            new_arr[(i-head)%N] = A[i]; // in the new array, indexing again starts from 0, all the way to the tail. 
        }
        head = 0; tail = N - 1; // in the new array the head is 0, tail is at old N - 1 (number of elements is N-1)
        N = nextSize();
        A = new_arr; // new array is set.
        
    }
}


template <typename T>
unsigned int DynamicQueue <T>::size() {
    if (tail >= head) return tail - head; 
    else { 
        return (N + tail - head); // to take wrapping around into account. If head = 2, tail = 1. then size has to be N-1
    }
}


template <typename T>
void DynamicQueue <T>::QInsert(T x) {
    A[tail] = x; // insert element at the tail index and grow the array. {i.e. shift if not full, insert a new section if full.}
    grow();
}


template <typename T>
bool DynamicQueue <T>::QDelete(T *x) {
    if (isEmpty()) {return false;}
    else {
        
        x = &A[head]; // putting head element as reference. 
        head++; // shift the head index forward -- previous element at head would still be in memory, but that's ok.
        // head and tail keep track of what's allowed. (which elements are valid).  
        return true; 
    }
}