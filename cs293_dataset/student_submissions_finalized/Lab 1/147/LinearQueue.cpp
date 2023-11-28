// implementation of a Linear Queue
// code developed by Krishna Narasimhan Agaram, CSE.

#include "queue.h"
// #include <iostream>

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return size() == 0; // self-explanatory
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return tail == N;
    // in a linear Queue, we say that the queue is full if we have reached the end of the array, that is, if the tail is exactly N(the index just after the end of the array)
}

template <typename T>
void DynamicQueue<T>::grow(){
    N = nextSize(); // increase array size.
    T *new_arr = new T[N]; // create a new array of this larger size
    
    // copy in the existing queue from the original array
    for (int i = head; i < tail; i++)
        new_arr[i - head] = A[i];
    
    delete[] A; // free original memory
    
    // assign A, head, tail values to the new array.
    A = new_arr;
    tail = tail-head; // tail of the new array = old size = old tail - old head
    head = 0; // start index = 0. Note that we update head after tail since tail requires old head.
    
    //std::cout << "After grow, Tail: " << tail << std::endl;
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    //std::cout << "For size: Head: " << head << " Tail: " << tail << std::endl;
    return tail - head; // clearly, since the queue is contiguous.
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if (isFull()) grow(); // we must ensure the array can accomodate the new element.
    
    // add the new element and update the tail index
    A[tail] = x;
    tail++;
    
    //std::cout << "Head: " << head << " Tail: " << tail << std::endl;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    // nothing to delete here, the specification requires us to return false in this case.
    if (isEmpty()) return false;

    // copy in the element to delete to the address in x
    *x = A[head];
    head++; // update the head variable.
    
    //std::cout << "Head: " << head << " Tail: " << tail << std::endl;
    return true; // succesful deletion
}
